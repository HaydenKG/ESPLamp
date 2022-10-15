# ESPLamp
Source code for a LED-stripe-lamp I built myself. Based on an ESP8266 and WS2812 LEDs

### Includes:
A HTML / CSS / JS Frontend that is served by the server that runs on the ESP. It has a section to select the colors the LED strip should display as well as it's brihtness and it has a section for choosing animations and their speed.
The communication between the client and server was first done using AJAX but was changed to fetch during the devlopment phase since it needs less code.
For the light logic the FASTLed library is used to control the color, animations, speed of them and brightness. 

### Learnings:
Scan the API documentation thoroughly before you implement functions or detours to your goal even though there are solutions provided with a directer way. 

<img src="https://user-images.githubusercontent.com/67265528/195983068-b6a76432-4743-4952-ba34-f4dbd81aeb2c.png" style="height: 720px; width: auto;" />
![Controller](https://user-images.githubusercontent.com/67265528/195983072-73ac85ff-12d0-49bd-bbd0-dd02a20372b9.jpg)
