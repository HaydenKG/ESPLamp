#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <String.h>

#include <FastLED.h>
#import "index.h"
#import "animations.h"

#define LED_PIN 12 
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

//SSID and Password of your WiFi router
const char* ssid = "FRITZ!Box 7530 EH"; //Enter SSID
const char* password = "16667275830538943450"; //Enter Password

int primaryColor = 13440000;
int secondaryColor = 0;

int brightness = 124;
int frames_per_second = 30;

unsigned long startMillis;
unsigned long currentMillis;
unsigned long period = 500;

String animations[] = {"Solid", "Confetti", "Rainbow", "Fire", "Wave", "Fairy", "Lava", "Sparkle" };
String currentAnimation = "Solid";
boolean alreadySolid = true;
boolean breakAnimation = false;

ESP8266WebServer server(80); //Server on port 80

// This routine is executed when you open its IP in browser
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void setColor(int color){
  FastLED.clear();
  for(int i=0; i<NUM_LEDS; i++){
      leds[i] = color; 
      FastLED.show();
      delay(20);
    }
}

void setColors() {
  String message = "Args received:\n";
  int colorValue[2];
  for (int i = 0; i < server.args(); i++) {

    message += "Arg no" + (String)i + " –> ";
    message += server.argName(i) + ": ";
    message += server.arg(i) + "\n";
    colorValue[i] = server.arg(i).toInt();
  } 
  
  Serial.println(colorValue[0]);
  Serial.println(colorValue[1]);

  if(primaryColor != colorValue[0]){
    primaryColor = colorValue[0];
    if(currentAnimation.equals("Solid")){
      setColor(primaryColor);
    }
  }
  secondaryColor = colorValue[1];
  
  server.send(200, "text/plane", message);
}

//lerp over 2 seconds?
void setBrightness(){
  String brightnessValue = server.arg("value");
  brightness = brightnessValue.toInt();
  FastLED.setBrightness(brightnessValue.toInt());
  brightnessValue += " received by the server";
  server.send(200, "text/plane", brightnessValue);
}

void setAnimation(){
  FastLED.clear();
  String animationTypeValue = server.arg("value");
  Serial.println(animationTypeValue);
  bool matchesAny = false;
  for(int i = 0; i < sizeof animations/sizeof animations[0]; i++){
    if(animations[i].equals(animationTypeValue)){
      matchesAny = true;
      break;
    }
  }
  currentAnimation = animationTypeValue;
  String match = "Matches " + String(matchesAny);
  server.send(200, "text/plane", match);
}

void setAnimationSpeed(){
  String animationSpeedValue = server.arg("value");
  int animationSpeedInt = animationSpeedValue.toInt();
  if(animationSpeedInt == 10){
    period = 10;
  } else if(animationSpeedInt == 9) {
    period = 100;
  } else {
    period = 200 * (10 - animationSpeedValue.toInt());
  }
  animationSpeedValue += " received by the server. Delay is: ";
  animationSpeedValue += period;
  Serial.println(period);
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
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.setBrightness(brightness);
  FastLED.clear();
  
  setColor(13440000);

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  //Event handler for the web requests
  server.on("/", handleRoot);      
  server.on("/getAnimation", sendAnimations);
  server.on("/brightness", setBrightness);
  server.on("/changeColor", setColors);
  server.on("/animationType", setAnimation);
  server.on("/animationSpeed", setAnimationSpeed);

  server.begin();               
  Serial.println("HTTP server started");
  
  startMillis = millis();

  digitalWrite(LED_BUILTIN, LOW);
  delay(2000); 
  digitalWrite(LED_BUILTIN, HIGH); 
}

void loop(void){
  server.handleClient();          //Handle client requests
  currentMillis = millis();

  if(currentAnimation.equals("Solid")){
    if(!alreadySolid){
      setColor(primaryColor);
      alreadySolid = true;
    }
  } else {
    alreadySolid = false;
  }
  if(currentMillis - startMillis >= period){
    if(currentAnimation.equals("Confetti")) {
      confetti(leds, NUM_LEDS);
    } else if(currentAnimation.equals("Rainbow")) {
      rainbow(leds, NUM_LEDS);
    } else if(currentAnimation.equals("Fire")) {
      fire(leds, NUM_LEDS);
    } else if(currentAnimation.equals("Wave")) {
      wave(leds, NUM_LEDS, primaryColor, secondaryColor);
    } else if(currentAnimation.equals("Fairy")) {
      fairy(leds, NUM_LEDS);
    } else if(currentAnimation.equals("Lava")){
      lava(leds, NUM_LEDS);
    } else if(currentAnimation.equals("Sparkle")){
      sparkle(leds, NUM_LEDS, primaryColor, secondaryColor);
    }
    startMillis = currentMillis;
  }

  FastLED.show();
  FastLED.delay(1000 / frames_per_second);
}
