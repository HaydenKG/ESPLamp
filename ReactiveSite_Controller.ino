#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <String.h>

#include <FastLED.h>
#import "index.h"

#define LED_PIN 12 
#define NUM_LEDS 60
#define INBUILT_LED 2

CRGB leds[NUM_LEDS];

//SSID and Password of your WiFi router
const char* ssid = "FRITZ!Box 7530 EH"; //Enter SSID
const char* password = "16667275830538943450"; //Enter Password
int Red = 205;
int Green = 20;
int Blue = 0;
float Brightness = .5;
String animations[] = {"Solid", "Sparkle", "Fairytale", "Glow", "Fade"};

ESP8266WebServer server(80); //Server on port 80

void setColor(int red, int green, int blue){
  Red = red;
  Green = green;
  Blue = blue;

  FastLED.clear();
  for(int i=0; i<NUM_LEDS; i++){
      leds[i].setRGB(red * Brightness, green * Brightness, blue * Brightness); 
      FastLED.show();
      delay(20);
    }
}

// This routine is executed when you open its IP in browser
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void changeColor() {
  String message = "Args received:\n";
  int colorValue[3];
  for (int i = 0; i < server.args(); i++) {

    message += "Arg no" + (String)i + " –> ";
    message += server.argName(i) + ": ";
    message += server.arg(i) + "\n";
    colorValue[i] = server.arg(i).toInt();
  } 
  
  Serial.println(colorValue[0]);
  Serial.println(colorValue[1]);
  Serial.println(colorValue[2]);

  setColor(colorValue[0], colorValue[1], colorValue[2]);
  
  server.send(200, "text/plane", message);
}

void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(INBUILT_LED, LOW); //LED ON
  ledState = "ON"; //Feedback parameter
 }
 else
 {
  digitalWrite(INBUILT_LED, HIGH); //LED OFF
  ledState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", ledState); //Send web page
}


//lerp over 2 seconds
void adaptBrightness(){
  String brightnessValue = server.arg("value");
  float temporaryValue = brightnessValue.toInt();

  Brightness = temporaryValue / 255; 
  int redDimmed = (Red * Brightness);
  Serial.println(redDimmed);
  FastLED.clear();
  for(int i=0; i<NUM_LEDS; i++){
      leds[i].setRGB(Red * Brightness, Green * Brightness, Blue* Brightness); 
  }
  FastLED.show();
  brightnessValue += " received by the server";
  server.send(200, "text/plane", brightnessValue);
}

void adaptAnimationType(){
  String animationTypeValue = server.arg("value");
  Serial.println(animationTypeValue);
  bool matchesAny = false;
  for(int i = 0; i < sizeof animations/sizeof animations[0]; i++){
    if(animations[i].equals(animationTypeValue)){
      Serial.println(animations[i]);
      matchesAny = true;
    }
  }
  String match = "Matches " + String(matchesAny);
  server.send(200, "text/plane", match);
}

void adaptAnimationspeed(){
  String animationSpeedValue = server.arg("value");
  animationSpeedValue += " received by the server";
  server.send(200, "text/plane", animationSpeedValue);
}

void sendAnimations(){
  String animationsConcatinated = "";
  for(int i = 0; i < sizeof animations/sizeof animations[0]; i++){
    animationsConcatinated += animations[i];
    animationsConcatinated += ",";
  }
  server.send(200, "text/plane", animationsConcatinated);
}

void setup() {
 Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(INBUILT_LED, OUTPUT); 
  digitalWrite(INBUILT_LED, HIGH);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/getAnimation", sendAnimations);
  server.on("/setLED", handleLED);
  server.on("/brightness", adaptBrightness);
  server.on("/changeColor", changeColor);
  server.on("/animationType", adaptAnimationType);
  server.on("/animationSpeed", adaptAnimationspeed);

  server.begin();               
  Serial.println("HTTP server started");

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
  srand(time(NULL));

  setColor(205, 20, 0);
}

void loop(void){
  server.handleClient();          //Handle client requests
}
