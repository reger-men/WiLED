/* Functions:
      update the sw via http server
      upload new files via the SPIFFS library
      return the requested file from client through server.uri

*/

#pragma once
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WebSocketsServer.h>
#include <FS.h>                                                 // Include the SPIFFS library



using namespace std::placeholders;
class WebServer {
  public:
    WebServer(Controller &c) : controller(c), server(80)
    {
      startServer();                                            // Start a HTTP server with a file read handler and an upload handler
      startSPIFFS();                                            // Start the SPIFFS and list all contents
      startWebSocket();                                         // Start a WebSocket server
      
      httpUpdater.setup(&server, "/update");                    // Initialize http updater server
    }

    // Convert sizes in bytes to KB and MB
    String formatBytes(size_t bytes) {
      if (bytes < 1024) {
        return String(bytes) + "B";
      } else if (bytes < (1024 * 1024)) {
        return String(bytes / 1024.0) + "KB";
      } else if (bytes < (1024 * 1024 * 1024)) {
        return String(bytes / 1024.0 / 1024.0) + "MB";
      }
    }

    // Convert the file extension to the MIME type
    String getContentType(String filename) {
      if (server.hasArg("download")) return "application/octet-stream";
      else if (filename.endsWith(".htm")) return "text/html";
      else if (filename.endsWith(".html")) return "text/html";
      else if (filename.endsWith(".css")) return "text/css";
      else if (filename.endsWith(".js")) return "application/javascript";
      else if (filename.endsWith(".png")) return "image/png";
      else if (filename.endsWith(".gif")) return "image/gif";
      else if (filename.endsWith(".jpg")) return "image/jpeg";
      else if (filename.endsWith(".ico")) return "image/x-icon";
      else if (filename.endsWith(".xml")) return "text/xml";
      else if (filename.endsWith(".pdf")) return "application/x-pdf";
      else if (filename.endsWith(".zip")) return "application/x-zip";
      else if (filename.endsWith(".gz")) return "application/x-gzip";
      return "text/plain";
    }

    // Send the right file to the client (if it exists)
    bool handleFileRead(String path) {
      if (path.endsWith("/")) path += "index.htm";              // If a folder is requested, send the index file
      if (path == "/upload")  path = "/upload.htm";             // Send the upload file
      Serial.println("handleFileRead: " + path);

      String contentType = getContentType(path);                // Get the MIME type
      String pathWithGz = path + ".gz";
      if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {   // If the file exists, either as a compressed archive, or normal
        if (SPIFFS.exists(pathWithGz))                          // If there's a compressed version available
          path += ".gz";                                        // Use the compressed verion
        File file = SPIFFS.open(path, "r");                     // Open the file
        size_t sent = server.streamFile(file, contentType);     // Send it to the client
        file.close();                                           // Close the file again
        Serial.println(String("\tSent file: ") + path);
        return true;
      }
      Serial.println(String("\tFile Not Found: ") + path);      // If the file doesn't exist, return false
      return false;
    }


    // Upload file to flash
    void handleFileUpload() {
      HTTPUpload& upload = server.upload();
      String path;
      if (upload.status == UPLOAD_FILE_START) {
        path = upload.filename;
        if (!path.startsWith("/")) path = "/" + path;
        if (!path.endsWith(".gz")) {                            // The file server always prefers a compressed version of a file
          String pathWithGz = path + ".gz";                     // So if an uploaded file is not compressed, the existing compressed
          if (SPIFFS.exists(pathWithGz))                        // version of that file must be deleted (if it exists)
            SPIFFS.remove(pathWithGz);
        }
        Serial.println("handleFileUpload Name: " + path);
        fsUploadFile = SPIFFS.open(path, "w");                  // Open the file for writing in SPIFFS (create if it doesn't exist)
        path = String();
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (fsUploadFile)
          fsUploadFile.write(upload.buf, upload.currentSize);   // Write the received bytes to the file
      } else if (upload.status == UPLOAD_FILE_END) {
        if (fsUploadFile) {                                     // If the file was successfully created
          fsUploadFile.close();                                 // Close the file again
          printf("handleFileUpload Size: %d\n", upload.totalSize);
          server.sendHeader("Location", "/success.htm");       // Redirect the client to the success page
          server.send(303);
        } else {
          Update.printError(Serial);
          server.send(500, "text/plain", "500: couldn't create file");
        }
      }
    }

    // Start the SPIFFS and list all contents
    void startSPIFFS() {
      
      printf("SPIFFS starting...\n");
      SPIFFS.begin();                                           // Start the SPI Flash File System (SPIFFS)
      printf("SPIFFS started. Contents:\n");
      {
        Dir dir = SPIFFS.openDir("/");
        while (dir.next()) {                                    // List the file system contents
          String fileName = dir.fileName();
          size_t fileSize = dir.fileSize();
          printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
        }
      }
    }

    void uploadData()
    {
      printf("upload data...");
      server.send(200, "text/html", this->upload_html); 
    }
    
    // Start a HTTP server with a file read handler and an upload handler
    void startServer() {
      //Initialize Webserver
      printf("Server starting...\n");
      
      server.on("/update", HTTP_GET, std::bind(&WebServer::uploadData, this)); // if the client requests the upload page
      server.on("/update", HTTP_POST, [this]() {                  // if the client posts to the upload page
        server.send(200);                                         // Send status 200 (OK) to tell the client we are ready to receive
        }, std::bind(&WebServer::handleFileUpload, this)          // Receive and save the file
      );
      
      
      server.onNotFound([this]() {                                // If the client requests any URI
        if (!espalexa.handleAlexaApiCall(server.uri(),server.arg(0))){                      // Check if is an Alexa control request
          if (!handleFileRead(server.uri())){ 
            server.send(404, "text/plain", "404: Not Found");     // otherwise, respond with a 404 (Not Found) error
          }
        }
      });

      server.begin();                                             // start the HTTP server
      printf("HTTP server started.\n");
    }

    // Start a WebSocket server
    void startWebSocket() {
      printf("WebSocket starting...\n");
      webSocket.begin();                                        // Start the websocket server
      webSocket.onEvent(std::bind(&WebServer::webSocketEvent, this, _1, _2, _3, _4));          // Call webSocketEvent if there's an incomming websocket message
      printf("WebSocket server started.\n");
    }

    // Start handleClient
    void serverListener()                                       // Omit this line since it will be called in espalexa.loop()
    {
      server.handleClient();
    }

    // Start webSocket listener
    void webSocketListener()
    {
      webSocket.loop();
    }

    // Event handler
    void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
      switch (type) {
        case WStype_DISCONNECTED:                               // If the websocket is disconnected
          printf("[%u] Disconnected!\n", num);
          break;
        case WStype_CONNECTED: {                                // if a new websocket connection is established
            IPAddress ip = webSocket.remoteIP(num);
            printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
          }
          break;
        case WStype_TEXT:                                       // If new text data is received
          printf("[%u] get Text: %s\n", num, payload);

          if (payload[0] == '#') {                              // # Set LED Colors
            payload++;
            char delimiter[] = ",";
            char *rgb_str = strtok((char *)payload, delimiter);
            uint8_t rgbs[15]; uint8_t i = 0;

            while (rgb_str != NULL) {
              rgbs[i] = atoi(rgb_str);
              i++;
              rgb_str = strtok(NULL, delimiter);
            }
            this->controller.updateColors(rgbs, i);
          } else if (payload[0] == '$') {                       // $ Set Strip Mode
            payload++;
            int m = atoi((const char *)payload);
            printf("m: %i\n", m);
            this->controller.updateMode(m);
          } else if (payload[0] == '~') {                       // ~ Set Speed
            payload++;
            int s = atoi((const char *)payload) * 100;
            this->controller.setSpeed(s);
          } else if (payload[0] == '&') {                       // & Set Brightness
            payload++;
            uint8_t b = atoi((const char *)payload);
            this->controller.setBrightness(b);
          } else if (payload[0] == 'N') {                       // N Turn LED On
            this->controller.on();
          } else if (payload[0] == 'F') {                       // F Turn LED Off
            this->controller.off();
          }
          break;
      }
    }

    
  private:
    Controller &controller;
    File fsUploadFile;                                          // A File object to temporarily store the received file
    WebSocketsServer webSocket = WebSocketsServer(81);          // Create a websocket server on port 81
    ESP8266HTTPUpdateServer httpUpdater;
    String upload_html = "<form method=\"post\" enctype=\"multipart/form-data\"> <input type=\"file\" name=\"name\"> <input class=\"button\" type=\"submit\" value=\"Upload\"> </form>\n";
  public:
    ESP8266WebServer server;
};
