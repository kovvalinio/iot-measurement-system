#include  <Adafruit_BMP280.h>
#include <ESP8266WiFi.h>

Adafruit_BMP280 bmp;

const char* ssid     = "wifi";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "password";



void setup()  {
  Serial.begin(9600);
  WiFi.begin(ssid, password);    
  delay(5000);
  Serial.print("Connecting to ");
  Serial.print(ssid); 
  Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  if  (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor,  check wiring!"));
    while (1);
  }

  // /* Default settings from datasheet.  */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500);  /* Standby time. */

}

void loop() {
    WiFiClient client;
    while(!client.connect("<ip_raspberry>",8080)){
      delay(500);
      Serial.println("Unable to connect to raspberry!");
    }
    client.print(bmp.readTemperature());
    client.stop();
  
    Serial.print(F("Temperature  = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    delay(1000);
}
