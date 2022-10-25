#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Arduino.h>
#include <DNSServer.h>
#include <ESPUI.h>
#include <EEPROM.h>
#include <math.h>


String tobesend;

#define sensorPin A0


const char* mqtt_server = "broker.mqttdashboard.com";


#define WIFI_CRED_LENGTH 21                     

IPAddress lanIP;
IPAddress UI_apIP(192, 168, 4, 2);
char UI_ssid_ca[WIFI_CRED_LENGTH] = "sensorConfig";
char WN_ssid_ca[WIFI_CRED_LENGTH] = {};         //   -setup SSID for the local Wifi network. leave empty for web interface setup!
char WN_password_ca[WIFI_CRED_LENGTH] = {};     //   -setup password
const char * charPtr;
const char *UI_password = "ChangeMe1";
const char *WN_ssid = WN_ssid_ca;
const char *UI_ssid = UI_ssid_ca;
const char *WN_password = WN_password_ca;
const byte wifiTimeout = 30;                    // @EB-custom timeout in seconds
const byte UI_DNS_PORT = 53;
const byte UI_sw_length = WIFI_CRED_LENGTH;    
const int eepromBufSize = 1024;   
const int maxNumOfSSIDs = 20;   
const unsigned int wifiSetupTimeout = 300;
uint16_t UI_ID_sw_ssid;
uint16_t UI_ID_sw_password;
uint16_t UI_ID_sw_saveButton;
uint16_t UI_ID_sw_restartButton;
uint16_t UI_ID_sw_sen_id;
uint16_t UI_ID_sw_phone;
uint16_t UI_ID_sw_sen_key;









unsigned long UI_sw_startTime;
bool wifiConnected = false;
bool UI_sw_eepromset;
String ssids[maxNumOfSSIDs];
int numOfssids;
DNSServer UI_dnsServer;

    String clientId = "ESP8266Client-landslide";

struct UI_sw_settings_ST {
  char idStart = ' ';
  char ssid[UI_sw_length];
  char password[UI_sw_length];
  char senid[UI_sw_length];
  char phone[UI_sw_length];
  char apiKey[UI_sw_length];


  

  char idEnd = ' ';
};
struct UI_sw_settings_ST UI_sw_EEPROM;

void UI_sw_writeEEPROM() {  
  EEPROM.begin(eepromBufSize);
  EEPROM.put(0, UI_sw_EEPROM);
  EEPROM.commit();

  Serial.println("EEPROM written:, SSID: " + (String) UI_sw_EEPROM.ssid);
  Serial.println(" password: " + (String) UI_sw_EEPROM.password);
  Serial.println(" Topic: " + (String) UI_sw_EEPROM.senid);
  Serial.println(" Phone: " + (String) UI_sw_EEPROM.phone);
  Serial.println(" API key: " + (String) UI_sw_EEPROM.apiKey);

  

}


String UI_sw_fillAsterisk(String value, byte valLength) {
  String tmpStr = "";
  while (tmpStr.length() < value.length())
    tmpStr += "*"; 
  return String(tmpStr);
}

void UI_sw_updatePassword() {
  UI_sw_startTime = millis();
  ESPUI.updateText(UI_ID_sw_password, UI_sw_fillAsterisk(UI_sw_EEPROM.password, (UI_sw_length) - 1));
}

void UI_sw_scanSSIDs() {
  Serial.println("Scanning for networks...");
  numOfssids = 0;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  int foundSSIDs = WiFi.scanNetworks();
  Serial.println("found " + (String) foundSSIDs + " networks");

  if (foundSSIDs) {
    for (int i = 0; i < foundSSIDs; ++i) {

//      if ((i < maxNumOfSSIDs) && (WiFi.SSID(i).length() < WIFI_CRED_LENGTH)) { //   -todo. NOTE: if skipping ssids, ssids[i] won't match anymore!!

      if ((i < maxNumOfSSIDs)) {
        numOfssids++;
        ssids[numOfssids - 1] = WiFi.SSID(i);
      
//      Serial.print(WiFi.RSSI(i));
//      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      }
    }
  }
}







void UI_sw_callSelect(Control *sender, int type) {
  UI_sw_startTime = millis();
  if (sender->id == UI_ID_sw_ssid) {
    int value = sender->value.toInt();
    ssids[value].toCharArray(UI_sw_EEPROM.ssid, UI_sw_length);
  }
}

void UI_sw_callText(Control *sender, int type) {
  UI_sw_startTime = millis();
  if (sender->id == UI_ID_sw_password) {
    sender->value.toCharArray(UI_sw_EEPROM.password, UI_sw_length);
    UI_sw_updatePassword();
  }
    else if (sender->id == UI_ID_sw_sen_id) {
    sender->value.toCharArray(UI_sw_EEPROM.senid, UI_sw_length);
// /   UI_sw_updatePassword();
  }
  else if (sender->id == UI_ID_sw_phone) {
    sender->value.toCharArray(UI_sw_EEPROM.phone, UI_sw_length);
//   / UI_sw_updatePassword();
  }
    else if (sender->id == UI_ID_sw_sen_key) {
    sender->value.toCharArray(UI_sw_EEPROM.apiKey, UI_sw_length);
// /   UI_sw_updatePassword();
  }
  
   

}

void UI_sw_callButton(Control *sender, int type) {
  UI_sw_startTime = millis();
  if (type == B_UP) {
    if (sender->id == UI_ID_sw_saveButton) {
      UI_sw_EEPROM.idStart = '$';
      UI_sw_EEPROM.idEnd = '*';
      UI_sw_writeEEPROM();

//        ESPUI.print(UI_ID_sw_info, UI_sw_msgRestarting);
//        UI_dnsServer.processNextRequest();    
//        displayMessageOutLoop(0, UI_sw_msgRestarting, false);  //   -todo
      ESP.restart();
    } else if (sender->id == UI_ID_sw_restartButton) {
      ESP.restart();
    }
  }
}

void UI_sw_setupWifi(char * UI_title) {
  UI_sw_scanSSIDs();
  
  WiFi.mode(WIFI_AP);                     //   -todo
  WiFi.softAPConfig(UI_apIP, UI_apIP, IPAddress(255, 255, 255, 0));

    WiFi.hostname(UI_ssid_ca);

  

  WiFi.softAP(UI_ssid, UI_password);
  Serial.print("Access point started");
  
  UI_dnsServer.start (UI_DNS_PORT, "*", UI_apIP);
 Serial.println("DNS server started");

  /// setup elements

  // String UI_lb_sw_info = UI_sw_msgInfo0 + (String) (UI_sw_length - 1) + UI_sw_msgInfo1;  
  // UI_ID_sw_info = ESPUI.addControl(ControlType::Label, UI_msg_sw_info, UI_lb_sw_info, ControlColor::Wetasphalt, Control::noParent);

  UI_ID_sw_ssid = ESPUI.addControl(ControlType::Select, "SSID", "", ControlColor::Peterriver, Control::noParent, &UI_sw_callSelect);
  for (int i = 0; i < numOfssids; i++) {
    charPtr = ssids[i].c_str();
    ESPUI.addControl(ControlType::Option, charPtr, (String) i, ControlColor::Peterriver, UI_ID_sw_ssid);
  }

  if (numOfssids)   // set ssid to first selection
    ssids[0].toCharArray(UI_sw_EEPROM.ssid, UI_sw_length);
  UI_ID_sw_password = ESPUI.addControl(ControlType::Text, "Password", UI_sw_EEPROM.password, ControlColor::Peterriver, Control::noParent, &UI_sw_callText);
  UI_ID_sw_sen_id = ESPUI.addControl(ControlType::Text, "Sensor ID", UI_sw_EEPROM.senid, ControlColor::Peterriver, Control::noParent, &UI_sw_callText);
  UI_ID_sw_phone = ESPUI.addControl(ControlType::Text, "Phone", UI_sw_EEPROM.senid, ControlColor::Peterriver, Control::noParent, &UI_sw_callText);
  UI_ID_sw_sen_key = ESPUI.addControl(ControlType::Text, "API key", UI_sw_EEPROM.senid, ControlColor::Peterriver, Control::noParent, &UI_sw_callText);
  UI_ID_sw_saveButton = ESPUI.addControl(ControlType::Button, "Save", "Save", ControlColor::Alizarin, Control::noParent, &UI_sw_callButton);
  UI_ID_sw_restartButton = ESPUI.addControl(ControlType::Button, "Restart", "Restart", ControlColor::Alizarin, Control::noParent, &UI_sw_callButton);

  ///

  UI_dnsServer.start(UI_DNS_PORT, "*", UI_apIP);
  ESPUI.begin(UI_title);
  UI_sw_updatePassword();   // mark with asterisks
  UI_sw_startTime = millis();

  while(1) {                // stay in loop until save is clicked or after a timeout
    UI_dnsServer.processNextRequest();

    if (wifiSetupTimeout) {
      if (((millis() - UI_sw_startTime) / 1000) >= wifiSetupTimeout) {
      Serial.println("Wifi setup timeout, restarting");
        ESP.restart();
      }
    }
    
    delay(40);                        // a little delay
  }
}

void UI_sw_resetEEPROM() {
  UI_sw_EEPROM.idStart = ' ';
  for (int i = 0; i < UI_sw_length; i++) {
    UI_sw_EEPROM.ssid[i] = 0;
    UI_sw_EEPROM.password[i] = 0;
    UI_sw_EEPROM.senid[i] = 0;
    UI_sw_EEPROM.phone[i] = 0;
    UI_sw_EEPROM.apiKey[i] = 0;
    
  }
  UI_sw_EEPROM.idEnd = ' ';
  UI_sw_writeEEPROM();
}

bool UI_sw_readEEPROM() {
  EEPROM.begin(sizeof(UI_sw_EEPROM));
  EEPROM.get(0, UI_sw_EEPROM);

  if (UI_sw_EEPROM.idStart == '$' && UI_sw_EEPROM.idEnd == '*') {
    return true;
  } else {
    Serial.println("Wifi setup EEPROM identifiers failed " + (String) UI_sw_EEPROM.idStart + " " + (String) UI_sw_EEPROM.idEnd + ", initializing");
    UI_sw_resetEEPROM();
    return false;
  }
}

void setupWifiConnection() {
  unsigned long wifiStartTime = millis();
  bool connectStat = true;
 
    Serial.println("Connecting to Wifi ");

  #ifndef NO_WIFI
    WiFi.mode(WIFI_AP_STA);                 

    #ifdef ESP32
      WiFi.setHostname(UI_ssid_ca);
    #else
      WiFi.hostname(UI_ssid_ca);
    #endif
      Serial.println("Hostname set to ");
      Serial.println(UI_ssid);

    WiFi.begin(WN_ssid, WN_password);
  
    while (WiFi.status() != WL_CONNECTED && ((millis() - wifiStartTime) < (wifiTimeout * 1000))) {
      connectStat = !connectStat;
      Serial.print(">");
      delay(500);
    }
  
    if (WiFi.status() == WL_CONNECTED) {  
      wifiConnected = true;
      lanIP = WiFi.localIP();
        Serial.print("connected to Wifi at ");
        Serial.println(lanIP);

      
    
      
    } else {    
        Serial.println("Failed to connect to wifi");
    }
  #endif
}












// 
//WiFiClient client;
//HTTPClient httpClient;

WiFiClient espClient;
PubSubClient client1(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
//  if ((char)payload[0] == '1') {
////    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//    // but actually the LED is on; this is because
//    // it is active low on the ESP-01)
//  } else {
//    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client1.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID

    // Attempt to connect
    if (client1.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client1.publish("outTopic", "hello world");
      // ... and resubscribe
      client1.subscribe("landslideWatch/kesses");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client1.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  client1.setServer(mqtt_server, 1883);
  client1.setCallback(callback);


    

if (WN_ssid_ca[0] != 0)  {           // if ssid is set, try to connect
        setupWifiConnection();}
        else{
        if (!wifiConnected) {             // wifi not connected so read the eeprom for ssid and password settings
          UI_sw_eepromset = UI_sw_readEEPROM();
    
          if (UI_sw_eepromset) {          // data read so try to connect
              Serial.print("SSID and password read from EEPROM. SSID: ");
              Serial.print(UI_sw_EEPROM.ssid);
              Serial.print(" password: ");
              Serial.print(UI_sw_EEPROM.password);
              Serial.println("");
              Serial.println("Sensor Id");
              Serial.print(UI_sw_EEPROM.senid);
              Serial.println("");
    
            strcpy(WN_ssid_ca, UI_sw_EEPROM.ssid);
            strcpy(WN_password_ca, UI_sw_EEPROM.password);
            setupWifiConnection();
          } else {
              Serial.println("SSID and password not read from EEPROM");
          }
        }
    
        if (!wifiConnected) {             // wifi not connected so start the wifi setup web interface
          String tmpMsg = (String) UI_ssid +  UI_apIP.toString();
          
    
          if (!UI_sw_eepromset) {
            UI_sw_EEPROM.ssid[0] = 0;
            UI_sw_EEPROM.password[0] = 0;
            UI_sw_EEPROM.senid[0] = 0;
          }
          UI_sw_setupWifi((char *) "UI_title");
        }
      }
    

   


  ESPUI.begin("Sesor configuration panel");





    pinMode(sensorPin, INPUT);

  
}

void loop() {

  if (!client1.connected()) {
    reconnect();
  }
  client1.loop();


 int msg = analogRead(sensorPin);
 Serial.println(msg);
  unsigned int outputValue = map(msg, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data

    static char sensorPinValue[7];
    dtostrf(outputValue, 6, 2, sensorPinValue);


 if (msg > 500) {
     


      WiFiClient clients;
      HTTPClient http; //Declare an object of class HTTPClient
      //Specify request destination
      tobesend = "http://api.callmebot.com/whatsapp.php?";
      tobesend = tobesend + "phone="+ UI_sw_EEPROM.phone;    // your phone number without ' + ' eg for +254-712-345-678 write 254712345678
      tobesend = tobesend + "&text=Critical+CO+level+at+:" + sensorPinValue;
      tobesend = tobesend + "&apikey="+ UI_sw_EEPROM.apiKey ;  
      Serial.println(tobesend);
      http.begin(clients,tobesend); 
      int httpCode = http.GET(); //Send the request
      if (httpCode > 0) 
          { 
           //Check the returning code
           String payload = http.getString(); //Get the request response payload
           Serial.println(payload); //Print the response payload
          }
      http.end(); //Close connection



 }



  if (client1.connect(clientId.c_str())) {
     Serial.println("connected");
      client1.publish(UI_sw_EEPROM.senid, sensorPinValue);
          } else {
      Serial.print("failed, rc=");
      Serial.print(client1.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
      
    delay(5000);  









}
