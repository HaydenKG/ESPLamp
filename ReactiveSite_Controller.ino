#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <String.h>

#include <FastLED.h>
#import "index.h"

#define LED_PIN 12 
#define NUM_LEDS 60
#define INBUILT_LED 2
#define FRAMES_PER_SECOND 30

CRGB leds[NUM_LEDS];

//SSID and Password of your WiFi router
const char* ssid = "FRITZ!Box 7530 EH"; //Enter SSID
const char* password = "16667275830538943450"; //Enter Password

int Red = 205;
int Green = 20;
int Blue = 0;

String animations[] = {"Solid", "Confetti", "Rainbow", "Fire"};
String currentAnimation = "Solid";
boolean alreadySolid = true;
boolean breakAnimation = false;

ESP8266WebServer server(80); //Server on port 80

// This routine is executed when you open its IP in browser
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void setColor(int red, int green, int blue){
  Red = red;
  Green = green;
  Blue = blue;

  FastLED.clear();
  for(int i=0; i<NUM_LEDS; i++){
      leds[i].setRGB(red, green, blue); 
      FastLED.show();
      delay(20);
    }
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


//lerp over 2 seconds?
void adaptBrightness(){
  String brightnessValue = server.arg("value");
  FastLED.setBrightness(brightnessValue.toInt());
  brightnessValue += " received by the server";
  server.send(200, "text/plane", brightnessValue);
}

void solidAnim(){
  FastLED.clear();
  for(int i=0; i<NUM_LEDS; i++){
      leds[i].setRGB(Red, Green, Blue); 
  }
  FastLED.show();
}

void confetti(){
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(20 + random8(), 20 + random8(), 20 + random8());
}

void rainbow() {
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, 0, 7);
}

void fire() {
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(100 + random8(155), random8(30), 0);
}

void adaptAnimationType(){
  String animationTypeValue = server.arg("value");
  Serial.println(animationTypeValue);
  bool matchesAny = false;
  for(int i = 0; i < sizeof animations/sizeof animations[0]; i++){
    if(animationTypeValue.equals("Solid")){
      matchesAny = true;
      break;
    } else if(animationTypeValue.equals("Confetti")) {
      matchesAny = true;
      break;
    } else if(animationTypeValue.equals("Rainbow")) {
      matchesAny = true;
      break;
    } else if(animationTypeValue.equals("Fire")) {
      matchesAny = true;
      break;
    } 
  }
  currentAnimation = animationTypeValue;
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
  FastLED.setBrightness(124);
  FastLED.clear();
  FastLED.show();
  // srand(time(NULL));

  setColor(205, 20, 0);
}

void loop(void){
  server.handleClient();          //Handle client requests

  if(currentAnimation.equals("Solid")){
    if(!alreadySolid){
      alreadySolid = true;
      solidAnim();
    }
  } else if(currentAnimation.equals("Confetti")) {
    confetti();
  } else if(currentAnimation.equals("Rainbow")) {
    rainbow();
  } else if(currentAnimation.equals("Fire")) {
    fire();
  } else {
    alreadySolid = false;
  }

  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}
