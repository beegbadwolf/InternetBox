
//https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts


//Load Libraries

// add password.h to the end of the .git ignore file (this makes sure it is not checked into git)
// Create a file called password.h in the same directory as the .ino file.
// add the line 'extern const char wifiPass[12]="PASSWORD HERE";
#include "password.h"

#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Adafruit_NeoPixel.h>
#include "RemoteDebug.h"

//set static / default Global variables.
char HOST_NAME[12]="internetbox";
uint64_t chipid;  
int batteryLevel=0;
int ledBuiltin=13;
#define PIN 34
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_RGB + NEO_KHZ800);
RemoteDebug Debug;

//setup is run once when powered on.
void setup() {
  // put your setup code here, to run once:
  // Initailize Serial
  Serial.begin(115200);
  // And print something so we know where we are.
  Serial.println("- Start setup");

  chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
  Serial.printf("ESP32 Chip ID = %04X\n",(uint16_t)(chipid>>32));//print High 2 bytes
  Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.

  // 1. setup LED
  // https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation
  // Note that these are "RGB"
  
  // 2. Start Wifi
  // https://github.com/zhouhan0126/WIFIMANAGER-ESP32
  Serial.println("- Starting Wifi");
  WiFi.begin("actdev", wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  Serial.println("Setup Remote Debug");
  Debug.begin(HOST_NAME);
  
  Serial.println("- Starting OTA");
  // 3. Setup OTA
  // https://github.com/espressif/arduino-esp32/blob/master/libraries/ArduinoOTA/examples/BasicOTA/BasicOTA.ino
  ArduinoOTA.setHostname(HOST_NAME);
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
  
  // 4. Setup webserver
  // https://github.com/zhouhan0126/WebServer-esp32
  // https://github.com/zhouhan0126/WebServer-esp32/blob/master/examples/AdvancedWebServer/AdvancedWebServer.ino
  
  // 5. Setup API

  // For debug setup the Built in LED
  pinMode (ledBuiltin, OUTPUT);
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Debug.begin("Telnet_HostName");
  
  Serial.println("- Setup Complete");
}


// Main loop repeats ....

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("# Start Loop");
  rdebugI("# Start Loop\n");
  
  // 3. OTA Do this early in the loop.
  ArduinoOTA.handle();
  
  //blink the built in LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

  
  // Set Variables only used in the loop.
  
  // Read Battery Level from Pin A13(35)
   batteryLevel= analogRead( 35 ) *2;
   Serial.print("# Battery Level: " );
   Serial.println(batteryLevel);
  
  // 2. Do wifi stuff
  
  // 4. Do web stuff
  // Add battery level to outputs

  // 1. Set LED

  
  // For inital setup and debug
  // Sleep for one second (don't do this with wifi starts)
//  Serial.println("# Sleep 5 seconds");
//  delay(5000);

  Debug.handle();
  Serial.println("# End Loop");
}
