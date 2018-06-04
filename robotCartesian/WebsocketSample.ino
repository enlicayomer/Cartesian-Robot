//http://www.devglan.com/spring-boot/spring-websocket-integration-example-without-stomp
#include <ESP8266WiFi.h>
#include <WebSocketClient.h>



# define EN D8 // stepper motor enable , active low
# define X_DIR D5 // X -axis stepper motor direction control
# define Y_DIR D6 // y -axis stepper motor direction control
# define Z_DIR D7 // z axis stepper motor direction control
# define X_STP D2 // x -axis stepper control
# define Y_STP D3 // y -axis stepper control
# define Z_STP D4 // z -axis stepper control
# define s1 D0 // z -axis stepper control
# define s2 D1 // z -axis stepper control
# define hiz 600 // z -axis stepper control


const char* ssid     = "G4_9351";
const char* password = "omer1234";

char path[] = "/ws";
char host[] = "192.168.43.12";
int a=1,m1=HIGH,m2=HIGH;

WebSocketClient webSocketClient;
WiFiClient client;


void setup() {

   pinMode(EN, OUTPUT); //Enable
  pinMode(Y_STP, OUTPUT); //Step
  pinMode(Y_DIR, OUTPUT); //Direction

  pinMode(Z_STP, OUTPUT); //Step
  pinMode(Z_DIR, OUTPUT); //Direction

   pinMode(X_STP, OUTPUT); //Step
  pinMode(X_DIR, OUTPUT); //Direction

  digitalWrite(EN,LOW);    // Initialize the BUILTIN_LED pin as an output

  Serial.begin(115200);

connectWifi();
  delay(500);
connectWebSocket();



  pinMode(D5,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);// put your setup code here, to run once:
}

void loop() {

  getWebSocketData();
  delay(50);

   analogWrite(D5,200);
  analogWrite(D2,200);
  digitalWrite(D3,m1);
  digitalWrite(D4,m2);// put your main code here, to run repeatedly:
}


void getWebSocketData()
{
  
  String data;

  if (client.connected()) {
  if(a==1)
  {
    webSocketClient.sendData("a");
  a++;
  }
    //
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Gelen data: ");
      Serial.println(data);
      servosAttach(data);
    }

  } else {
    Serial.println("Client disconnected.");
    connectWebSocket();
  }

}

void servosAttach(String data)
{
   
    // x
  if (data == "1") {

    step(HIGH,X_DIR,X_STP,100);

 
  } 
   if (data == "2") {

    step(LOW,X_DIR,X_STP,100);

 
  } 


  if (data == "3") {

    step(HIGH,Y_DIR,Y_STP,100);

 
  } 
   if (data == "4") {

    step(LOW,Y_DIR,Y_STP,100);

 
  } 

  
  if (data == "5") {

    step(HIGH,Z_DIR,Z_STP,100);

 
  } 
   if (data == "6") {

    step(LOW,Z_DIR,Z_STP,100);

 
  } 

   if (data == "7") {

    m1=LOW;
    m2=LOW;

 
  } 
   if (data == "8") {

    m1=HIGH;
    m2=HIGH;

 
  } 

}


void step (int dir, byte dirPin, byte stepperPin, int steps)
{
    digitalWrite (dirPin, dir);
    delay (50);
    for (int i = 0; i <steps; i++) 
    {
        digitalWrite (stepperPin, HIGH);
        delayMicroseconds (hiz);
        digitalWrite (stepperPin, LOW);
        delayMicroseconds (hiz);
    }
}



void connectWifi()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectWebSocket()
{
    if (client.connect(host, 8080)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }

  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }

}

