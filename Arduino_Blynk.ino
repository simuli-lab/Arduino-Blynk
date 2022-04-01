
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID           "<Template>"
#define BLYNK_DEVICE_NAME           "<Device name>"
#define BLYNK_AUTH_TOKEN            "<Auth Token>"


#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#include <Wire.h>
#include <Sodaq_SHT2x.h>

char auth[] = BLYNK_AUTH_TOKEN;


IPAddress server_ip (10, 0, 0, 10);

// Mac address should be different for each device in your LAN
byte arduino_mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress arduino_ip ( 10,   0,   0,  20);
IPAddress dns_ip     (  8,   8,   8,   8);
IPAddress gateway_ip ( 10,   0,   0,   1);
IPAddress subnet_mask(255, 255, 255,   0);

#define W5500_CS  10
#define SDCARD_CS 4

//BlynkTimer timer;
void sendSensor()
{
  int h = SHT2x.GetHumidity();
  int t = SHT2x.GetTemperature();
  Serial.print("Temp: ");
  Serial.println(t+1);
  Serial.print("Humidity: ");
  Serial.println(h+1);
  Serial.println("");
  Blynk.virtualWrite(V5, h+1);
  Blynk.virtualWrite(V6, t+1);
  }
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V0 to a variable

  // process received value
  if(pinValue==1){
    digitalWrite(5,HIGH);  
  }
  else{
    digitalWrite(5,LOW);
  }
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(5, OUTPUT);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  Blynk.begin(auth, "blynk.cloud", 8080, arduino_ip, dns_ip, gateway_ip, subnet_mask, arduino_mac);
  // Or like this:
  //Blynk.begin(auth, "blynk-cloud.com", 80, arduino_ip, dns_ip, gateway_ip, subnet_mask, arduino_mac);
}

void loop()
{
  Blynk.run();
  sendSensor();
  delay(2000);
}
