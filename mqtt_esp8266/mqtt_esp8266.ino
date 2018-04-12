/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

Servo servo1;
int Index;

# define EN D8 // stepper motor enable , active low
# define X_DIR D5 // X -axis stepper motor direction control
# define Y_DIR D6 // y -axis stepper motor direction control
# define Z_DIR D7 // z axis stepper motor direction control
# define X_STP D2 // x -axis stepper control
# define Y_STP D3 // y -axis stepper control
# define Z_STP D4 // z -axis stepper control
# define s1 D0 // z -axis stepper control
# define hiz 600 // z -axis stepper control
// Update these with values suitable for your network.

//const char* ssid = "G4_9351";
//const char* password = "omer1234";
const char* ssid = "YbsEem2014";
const char* password = "15963214789bmo";
//const char* ssid = "ZyXEL_61CC";
//const char* password = "Yusuf326";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


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
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  servo1.attach(s1);
  servo1.write(180);
 // for(int i=0; i<180; i+=15)
//{
  //servo2.write(i);
//}
}
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Gelen Mesaj [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // x
  if ((char)payload[0] == '1') {

    step(HIGH,X_DIR,X_STP,100);

 
  } 
   if ((char)payload[0] == '2') {

    step(LOW,X_DIR,X_STP,100);

 
  } 


  if ((char)payload[0] == '3') {

    step(HIGH,Y_DIR,Y_STP,100);

 
  } 
   if ((char)payload[0] == '4') {

    step(LOW,Y_DIR,Y_STP,100);

 
  } 

  
  if ((char)payload[0] == '5') {

    step(HIGH,Z_DIR,Z_STP,100);

 
  } 
   if ((char)payload[0] == '6') {

    step(LOW,Z_DIR,Z_STP,100);

 
  } 


   if ((char)payload[0] == '7') {

  servo1.write(180);

      
    } 

    if ((char)payload[0] == '8') {

  servo1.write(0);

      
    } 
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("mesajCikis", "test mesaj");
      // ... and resubscribe
      client.subscribe("mesajGiris");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "iot publish test #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("mesajCikis", msg);
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
