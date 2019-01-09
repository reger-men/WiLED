/* Functions:
 *    update the sw via http server
 *    upload new files via the SPIFFS library
 *    return the requested file from client through server.uri
 * 
*/
 
#pragma once
#include "controller.h"

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <WebSocketsServer.h>
#include <FS.h>                                                 //Include the SPIFFS library
File fsUploadFile;                                              // a File object to temporarily store the received file

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);                                 // create a websocket server on port 81
ESP8266HTTPUpdateServer httpUpdater;


bool rainbow = false;             // The rainbow effect is turned off on startup //delete me

using namespace std::placeholders;
class WebServer {
    public:   
      WebServer(Controller controller)
      { 
        this->controller = controller;       
        startSPIFFS();                                          // Start the SPIFFS and list all contents                        
        startWebSocket();                                       // Start a WebSocket server
        startServer();                                          // Start a HTTP server with a file read handler and an upload handler
         
        //Initialize http updater server
        httpUpdater.setup(&server, "/update");
    
        server.begin();                                         // Actually start the server
        Serial.println("HTTP server started");
      }

      String formatBytes(size_t bytes) { // convert sizes in bytes to KB and MB
        if (bytes < 1024) {
          return String(bytes) + "B";
        } else if (bytes < (1024 * 1024)) {
          return String(bytes / 1024.0) + "KB";
        } else if (bytes < (1024 * 1024 * 1024)) {
          return String(bytes / 1024.0 / 1024.0) + "MB";
        }
      }

      // convert the file extension to the MIME type
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

      bool handleFileRead(String path) { // send the right file to the client (if it exists)
        if (path.endsWith("/")) path += "index.htm";          // If a folder is requested, send the index file
        if (path == "/upload")  path = "/upload.htm";           // Send the upload file
        Serial.println("handleFileRead: " + path);
        
        String contentType = getContentType(path);             // Get the MIME type
        String pathWithGz = path + ".gz";
        if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) { // If the file exists, either as a compressed archive, or normal
          if (SPIFFS.exists(pathWithGz))                         // If there's a compressed version available
            path += ".gz";                                         // Use the compressed verion
          File file = SPIFFS.open(path, "r");                    // Open the file
          size_t sent = server.streamFile(file, contentType);    // Send it to the client
          file.close();                                          // Close the file again
          Serial.println(String("\tSent file: ") + path);
          return true;
        }
        Serial.println(String("\tFile Not Found: ") + path);   // If the file doesn't exist, return false
        return false;
      }


      // Upload file to flash
      void handleFileUpload(){ // upload a new file to the SPIFFS
        HTTPUpload& upload = server.upload();
        String path;
        if(upload.status == UPLOAD_FILE_START){
          path = upload.filename;
          if(!path.startsWith("/")) path = "/"+path;
          if(!path.endsWith(".gz")) {                          // The file server always prefers a compressed version of a file 
            String pathWithGz = path+".gz";                    // So if an uploaded file is not compressed, the existing compressed
            if(SPIFFS.exists(pathWithGz))                      // version of that file must be deleted (if it exists)
               SPIFFS.remove(pathWithGz);
          }
          Serial.print("handleFileUpload Name: "); Serial.println(path);
          fsUploadFile = SPIFFS.open(path, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
          path = String();
        } else if(upload.status == UPLOAD_FILE_WRITE){
          if(fsUploadFile)
            fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
        } else if(upload.status == UPLOAD_FILE_END){
          if(fsUploadFile) {                                    // If the file was successfully created
            fsUploadFile.close();                               // Close the file again
            Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
            server.sendHeader("Location","/success.html");      // Redirect the client to the success page
            server.send(303);
          } else {
            server.send(500, "text/plain", "500: couldn't create file");
          }
        }
      }
    
      void startSPIFFS() { // Start the SPIFFS and list all contents
        SPIFFS.begin();                             // Start the SPI Flash File System (SPIFFS)
        Serial.println("SPIFFS started. Contents:");
        {
          Dir dir = SPIFFS.openDir("/");
          while (dir.next()) {                      // List the file system contents
            String fileName = dir.fileName();
            size_t fileSize = dir.fileSize();
            Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
          }
          Serial.printf("\n");
        }
      }

      void startServer() { // Start a HTTP server with a file read handler and an upload handler
        //Initialize Webserver
        server.on("/upload", HTTP_POST, [this](){               // if the client posts to the upload page
          server.send(200);                                     // Send status 200 (OK) to tell the client we are ready to receive
        }, std::bind(&WebServer::handleFileUpload, this)        // Receive and save the file
        );
      
        server.onNotFound([this]() {                            // If the client requests any URI
          if (!handleFileRead(server.uri()))                    // send it if it exists
            server.send(404, "text/plain", "404: Not Found");   // otherwise, respond with a 404 (Not Found) error
        });
      
        server.begin();                                         // start the HTTP server
        Serial.println("HTTP server started.");
      }

      void startWebSocket() { // Start a WebSocket server
        webSocket.begin();                          // start the websocket server
        webSocket.onEvent(std::bind(&WebServer::webSocketEvent, this, _1, _2, _3, _4));          // if there's an incomming websocket message, go to function 'webSocketEvent'
        Serial.println("WebSocket server started.");
      }
    
      void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
         switch (type) {
          case WStype_DISCONNECTED:             // if the websocket is disconnected
            Serial.printf("[%u] Disconnected!\n", num);
            break;
          case WStype_CONNECTED: {              // if a new websocket connection is established
              IPAddress ip = webSocket.remoteIP(num);
              Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
              rainbow = false;                  // Turn rainbow off when a new connection is established
            }
            break;
          case WStype_TEXT:                     // if new text data is received
            Serial.printf("[%u] get Text: %s\n", num, payload);

            if (payload[0] == '#') {            // Get RGB data
              payload++;
              char delimiter[] = ",";
              char *rgb_str = strtok((char *)payload, delimiter);
              int rgbs[15]; int i = 0;
              
              while(rgb_str != NULL) {
                rgbs[i] = atoi(rgb_str);
                i++;
                printf("RGB Value: %s\n", rgb_str);
                rgb_str = strtok(NULL, delimiter);
              }                      
              this->controller.insertRGBArray(rgbs, i);
              
            } else if (payload[0] == 'R') {                      // the browser sends an R when the rainbow effect is enabled
              rainbow = true;
            } else if (payload[0] == 'N') {                      // the browser sends an N when the rainbow effect is disabled
              rainbow = false;
            }
            break;
        }
      }
    private:
      Controller controller;
};
