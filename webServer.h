/* Functions:
 *    update the sw via http server
 *    upload new files via the SPIFFS library
 *    return the requested file from client through server.uri
 * 
*/
 
#pragma once
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <FS.h>                                                 //Include the SPIFFS library
File fsUploadFile;                                              // a File object to temporarily store the received file

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

const int led = 2;//delete me
class WebServer {
    public:   
      WebServer()
      {
        SPIFFS.begin();                                         // Start the SPI Flash Files System
        pinMode(led, OUTPUT); //delete me
         
        //Initialize http updater server
        httpUpdater.setup(&server, "/update");

        server.on("/LED", HTTP_POST, std::bind(&WebServer::handleLED, this));                // Call the 'handleLED' function when a POST request is made to URI "/LED"
         
        //Initialize Webserver
        server.on("/upload", HTTP_POST, [this](){               // if the client posts to the upload page
          server.send(200);                                     // Send status 200 (OK) to tell the client we are ready to receive
        }, std::bind(&WebServer::handleFileUpload, this)        // Receive and save the file
        );
      
        server.onNotFound([this]() {                            // If the client requests any URI
          if (!handleFileRead(server.uri()))                    // send it if it exists
            server.send(404, "text/plain", "404: Not Found");   // otherwise, respond with a 404 (Not Found) error
        });
      
        server.begin();                                         // Actually start the server
        Serial.println("HTTP server started");
      }

      void handleLED() {                          // If a POST request is made to URI /LED
        digitalWrite(led,!digitalRead(led));      // Change the state of the LED
        server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
        //server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
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

      /*bool handleFileRead(String path) {                        // send the right file to the client (if it exists)
        if (path.endsWith("/")) path += "index.htm";            // If a folder is requested, send the index file
        if (path == "/upload")  path = "/upload.htm";           // Send the upload file
        Serial.println("handleFileRead: " + path);
        
        String contentType = getContentType(path);              // Get the MIME type
        if (SPIFFS.exists(path)) {                              // If the file exists
          File file = SPIFFS.open(path, "r");                   // Open it
          size_t sent = server.streamFile(file, contentType);   // And send it to the client
          file.close();                                         // Then close the file again
          return true;
        }
        Serial.println("\tFile Not Found");
        return false;                                           // If the file doesn't exist, return false
      }*/

      bool handleFileRead(String path) {
        if (path.endsWith("/")) path += "index.htm";
        if (path == "/upload")  path = "/upload.htm";           // Send the upload file
        Serial.println("handleFileRead: " + path);
        
        String contentType = getContentType(path);
        String pathWithGz = path + ".gz";
        if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
          if (SPIFFS.exists(pathWithGz))
            path += ".gz";
          File file = SPIFFS.open(path, "r");
          server.sendHeader("Access-Control-Allow-Origin", "*");
          size_t sent = server.streamFile(file, contentType);
          file.close();
          return true;
        }
        return false;
      }


      // Upload file to flash
      void handleFileUpload(){ // upload a new file to the SPIFFS
        HTTPUpload& upload = server.upload();
        if(upload.status == UPLOAD_FILE_START){
          String filename = upload.filename;
          if(!filename.startsWith("/")) filename = "/"+filename;
          Serial.print("handleFileUpload Name: "); Serial.println(filename);
          fsUploadFile = SPIFFS.open(filename, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
          filename = String();
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
    

    private:
      
};
