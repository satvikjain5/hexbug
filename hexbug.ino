/* include library */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
WiFiClient client;
/* defining server port */
ESP8266WebServer server(80);

/* Define WiFi Credentials */
const char* ssid = ""; /* Your SSID */
const char* password = ""; /* Your Password */

String  data = "";
int robospeed = 1023;

/* Defining right and left motor pins */
#define IN1 D1/* Right Motor GPIO0(D3) */
#define IN2 D2
#define IN3 D3/* Left Motor GPIO13(D7) */
#define IN4 D4/* Left Motor GPIO15(D8) */

/* Defining L298N enable pins */
int REnable = 14;/* Right Motor Enable Pin GPIO14(D5) */
int LEnable = 12;/* Right Motor Enable Pin GPIO12(D6)  */

void setup() {
  Serial.begin(115200);
  Serial.println("GPIO test!");
  /* Initialize Motor Control Pins as Output */
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  /* Initialize Motor Enable Pins as Output */
  pinMode(REnable, OUTPUT);
  pinMode(LEnable, OUTPUT);

  /* Connectinf to WiFi */
  connectingToWiFi();

  server.on("/", handleRequest);
  server.onNotFound(handleRequest);

  /* Starting Server */
  server.begin();
  Serial.println("Server started");
}
void loop() {

  analogWrite(REnable, robospeed);
  analogWrite(LEnable, robospeed);

  /* Handling Request */
  server.handleClient();
  String data = server.arg("Key");
  Serial.println(data);

  /* Setting Speed */
  if ( server.hasArg("Speed") ) {
    int _speed = (server.arg("Speed").toInt());
    robospeed = _speed;
    Serial.println(robospeed);
  }

  if (data == "F") {
    move_forward(); /* If data F moves Forward */
  }
  else if (data == "B") {
    move_backward(); /* If data B moves Backward */
  }
  else if (data == "R") {
    turn_right(); /* If data R moves Turn Right */
  }
  else if (data == "L") {
    turn_left(); /* If data L moves Turn Left */
  }
  else if (data == "S") {
    move_stop(); /* If data S moves Stop Moving */
  }
}

void handleRequest() {
  if ( server.hasArg("Key") ) {
    Serial.println(server.arg("Key"));
  }
  if ( server.hasArg("Speed") ) {
    Serial.println(server.arg("Speed"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}


void connectingToWiFi() {
  delay(3000);
  WiFi.disconnect();
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(1000);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.print((WiFi.localIP().toString()));
  delay(5000);
}

/* Move Forward */
void move_forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

/* Move Backward */
void move_backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

/* Turn Right */
void turn_right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

/* Turn Left */
void turn_left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

/* Stop Move */
void move_stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
