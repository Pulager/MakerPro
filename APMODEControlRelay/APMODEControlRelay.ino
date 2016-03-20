#include <WiFi.h>
#define RelayPin 8
#define Turnon HIGH
#define Turnoff LOW

char ssid[] = "Ameba";  //Set the AP's SSID
char pass[] = "12345678";     //Set the AP's password
char channel[] = "1";         //Set the AP's channel
int status = WL_IDLE_STATUS;     // the Wifi radio's status

int keyIndex = 0;                 // your network key Index number (needed only for WEP)

WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
pinMode(RelayPin, OUTPUT);      // set the LED pin mode
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to start AP:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to start AP with SSID: ");
    Serial.println(ssid);
    status = WiFi.apbegin(ssid, pass, channel);
    delay(10000);
  }

  //AP MODE already started:
  Serial.println("AP mode already started");
  Serial.println();
    server.begin();    
  printWifiData();
  printCurrentNet();
}

void loop() {
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your subnet mask:
  IPAddress subnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(subnet);

  // print your gateway address:
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);
  Serial.println();
}

void printCurrentNet() {
  // print the SSID of the AP:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of AP:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[0], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.println(bssid[5], HEX);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

