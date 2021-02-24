#include<WiFi.h>;
#include<HTTPClient.h>;
#include <ArduinoJson.h>;


const char* ssid ="Anonymous";
const char* password = "0987654321";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to wifi");

  while (WiFi.status() !=WL_CONNECTED){
    Serial.print("");
    Serial.println(WiFi.localIP());
  }
  Serial.println("Connected to the wifi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  

//Serial.println(payload["q5yU5TfQcO91puL6vTwX"]);
//Serial.println(payload["krsboT2lA2EYTKYTNFDl"]);  
 
}

void loop() {

  if((WiFi.status()==WL_CONNECTED))
{
  long rnd = random(1,10);
  HTTPClient client;

  client.begin("https://fastag-internal.parkzap.com/account/mockable_test/" + String(rnd));
  int httpCode= client.GET();
  if(httpCode >0){
  String payload = client.getString();

   Serial.println("\nStatuscode: " + String(httpCode));
   Serial.println(payload);
   
  
 char json[1000];

 payload.replace(" ", "");
  payload.replace("\n", "");
   payload.trim();
   payload.remove(0,1);
     payload.toCharArray(json, 1000);



Serial.println("Type the Key");
//Serial.println(payload);
delay(5000);
  String info=Serial.readString();
  
  StaticJsonDocument<1000> doc;  
 deserializeJson(doc,json);

Serial.println(info);
//Serial.println(info);

//const char * id=doc[info];
int id = doc[json];
Serial.println(String(id));
client.end();
}
else{
  Serial.println("Error on Http");
 }
 }
else
{
  Serial.println("Connection lost");
}

delay(20000);
}
