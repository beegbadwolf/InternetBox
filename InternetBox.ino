
//https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts


//Load Libraries

//set static / default Global variables.
uint64_t chipid;  
int batteryLevel=0;
int ledBuiltin=13;

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

  // 3. Setup OTA
  // https://github.com/espressif/arduino-esp32/blob/master/libraries/ArduinoOTA/examples/BasicOTA/BasicOTA.ino
  
  // 4. Setup webserver
  // https://github.com/zhouhan0126/WebServer-esp32
  // https://github.com/zhouhan0126/WebServer-esp32/blob/master/examples/AdvancedWebServer/AdvancedWebServer.ino
  
  // 5. Setup API

  // For debug setup the Built in LED
  pinMode (ledBuiltin, OUTPUT);
  
 Serial.println("- Setup Complete");
}


// Main loop repeats ....

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("# Start Loop");
  //blink the built in LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

  
  // Set Variables only used in the loop.

  // For testing

  
  // Read Battery Level from Pin A13(35)
   batteryLevel= analogRead( 35 ) *2;
   Serial.print("# Battery Level: " );
   Serial.println(batteryLevel);
  
  // 2. Do wifi stuff

  // 3. OTA
  
  // 4. Do web stuff
  // Add battery level to outputs

  // 1. Set LED

  
  // For inital setup and debug
  // Sleep for one second (don't do this with wifi starts)
  Serial.println("# Sleep 5 seconds");
  delay(5000);

  Serial.println("# End Loop");
}
