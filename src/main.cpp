#ifndef UNIT_TEST

#include <Arduino.h>

#endif

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ArduinoJson.h>

/*********************************************************************/

// TV IR CODE
#define TV_ON  0x20DF10EF
#define TV_INPUT 0x20DFD02F
#define TV_VOL_UP 0x20DF40BF
#define TV_VOL_DOWN 0x20DFC03F
#define TV_VOL_MUTE 0x20DF906F
#define TV_PROG_UP 0x20DF00FF
#define TV_PROG_DOWN 0x20DF807F
#define TV_ARROW_UP 0x20DF02FD
#define TV_ARROW_DOWN 0x20DF827D
#define TV_ARROW_LEFT 0x20DFE01F
#define TV_ARROW_RIGHT 0x20DF609F
#define TV_OK 0x20DF22DD
#define TV_SETTINGS 0x20DFC23D
#define TV_BACK 0x20DF14EB

// SOUNDBAR IR CODE
#define SOUNDBAR_ON 0x40BF12ED
#define SOUNDBAR_AUX 0x40BFB04F
#define SOUNDBAR_HDMI 0x40BF629D
#define SOUNDBAR_USB 0x40BF9867
#define SOUNDBAR_OPTICAL 0x40BF906F
#define SOUNDBAR_BLUETOOTH 0x40BFF20D
#define SOUNDBAR_DISPLAY 0x40BFA25D
#define SOUNDBAR_VOL_UP 0x40BFA05F
#define SOUNDBAR_VOL_DOWN 0x40BFF00F
#define SOUNDBAR_VOL_MUTE 0x40BF926D
#define SOUNDBAR_NEXT_TRACK 0x40BF02FD
#define SOUNDBAR_PREVIOUS_TRACK 0x40BF22DD
#define SOUNDBAR_PLAY_PAUSE 0x40BFC23D
#define SOUNDBAR_STOP 0x40BF30CF
#define SOUNDBAR_LOOP 0x40BF6897
#define SOUNDBAR_TREBLE_UP 0x40BF7A85
#define SOUNDBAR_TREBLE_DOWN 0x40BF18E7
#define SOUNDBAR_BASS_UP 0x40BF38C7
#define SOUNDBAR_BASS_DOWN 0x40BF10EF
#define SOUNDBAR_EQ_MUSIC 0x40BF5AA5
#define SOUNDBAR_EQ_MOVIE 0x40BF42BD
#define SOUNDBAR_EQ_DIALOG 0x40BF4AB5
#define SOUNDBAR_EQ_3D 0x40BF52AD

/*********************************************************************/

const char *ssid = "ALBANESE";
const char *password = "0101010101";
ESP8266WebServer server(80);

IRsend irsend(14);  // IR LED is controlled by GPIO 14 (D5)

String last_input_selected = "aux";
String last_eq_selected = "music";

/*********************************************************************/

/**
 * The last input selected
 * @return Last input selected
 */
String get_last_input_selected() {
    return last_input_selected;
}

/**
 * The last eq selected
 * @return Last eq selected
 */
String get_last_eq_selected() {
    return last_eq_selected;
}

/*********************************************************************/

/**
 * Send the command to the TV
 * @param arg is the command received
 */
void tvAction(String arg) {
    if (arg == "on") {
        irsend.sendNEC(TV_ON, 32);
    } else if (arg == "input") {
        irsend.sendNEC(TV_INPUT, 32);
    } else if (arg == "vol_up") {
        irsend.sendNEC(TV_VOL_UP, 32);
    } else if (arg == "vol_down") {
        irsend.sendNEC(TV_VOL_DOWN, 32);
    } else if (arg == "vol_mute") {
        irsend.sendNEC(TV_VOL_MUTE, 32);
    } else if (arg == "prog_up") {
        irsend.sendNEC(TV_PROG_UP, 32);
    } else if (arg == "prog_down") {
        irsend.sendNEC(TV_PROG_DOWN, 32);
    } else if (arg == "arrow_up") {
        irsend.sendNEC(TV_ARROW_UP, 32);
    } else if (arg == "arrow_down") {
        irsend.sendNEC(TV_ARROW_DOWN, 32);
    } else if (arg == "arrow_left") {
        irsend.sendNEC(TV_ARROW_LEFT, 32);
    } else if (arg == "arrow_right") {
        irsend.sendNEC(TV_ARROW_RIGHT, 32);
    } else if (arg == "ok") {
        irsend.sendNEC(TV_OK, 32);
    } else if (arg == "settings") {
        irsend.sendNEC(TV_SETTINGS, 32);
    } else if (arg == "back") {
        irsend.sendNEC(TV_BACK, 32);
    }
}

/**
 * Check the command received for the TV
 */
void tvArg() {
    String message = "";

    if (server.arg("action") == "") {
        message = "TV argument not found";

        server.send(400, "text/plain", message);
    } else {
        message = "TV  = ";
        message += server.arg("action");

        tvAction(server.arg("action"));

        server.send(200, "text/plain", message);
    }
}

/*********************************************************************/

/**
 * Send the command to the Soundbar
 * @param arg is the command received
 */
void soundbarAction(String arg) {
    if (arg == "on") {
        irsend.sendNEC(SOUNDBAR_ON, 32);
    } else if (arg == "aux") {
        irsend.sendNEC(SOUNDBAR_AUX, 32);
        last_input_selected = "aux";
    } else if (arg == "hdmi") {
        irsend.sendNEC(SOUNDBAR_HDMI, 32);
        last_input_selected = "hdmi";
    } else if (arg == "usb") {
        irsend.sendNEC(SOUNDBAR_USB, 32);
        last_input_selected = "usb";
    } else if (arg == "optical") {
        irsend.sendNEC(SOUNDBAR_OPTICAL, 32);
        last_input_selected = "optical";
    } else if (arg == "bluetooth") {
        irsend.sendNEC(SOUNDBAR_BLUETOOTH, 32);
        last_input_selected = "bluetooth";
    } else if (arg == "display") {
        irsend.sendNEC(SOUNDBAR_DISPLAY, 32);
    } else if (arg == "vol_up") {
        irsend.sendNEC(SOUNDBAR_VOL_UP, 32);
    } else if (arg == "vol_down") {
        irsend.sendNEC(SOUNDBAR_VOL_DOWN, 32);
    } else if (arg == "vol_mute") {
        irsend.sendNEC(SOUNDBAR_VOL_MUTE, 32);
    } else if (arg == "next_track") {
        irsend.sendNEC(SOUNDBAR_NEXT_TRACK, 32);
    } else if (arg == "previous_track") {
        irsend.sendNEC(SOUNDBAR_PREVIOUS_TRACK, 32);
    } else if (arg == "play_pause") {
        irsend.sendNEC(SOUNDBAR_PLAY_PAUSE, 32);
    } else if (arg == "stop") {
        irsend.sendNEC(SOUNDBAR_STOP, 32);
    } else if (arg == "loop") {
        irsend.sendNEC(SOUNDBAR_LOOP, 32);
    } else if (arg == "treble_up") {
        irsend.sendNEC(SOUNDBAR_TREBLE_UP, 32);
    } else if (arg == "treble_down") {
        irsend.sendNEC(SOUNDBAR_TREBLE_DOWN, 32);
    } else if (arg == "bass_up") {
        irsend.sendNEC(SOUNDBAR_BASS_UP, 32);
    } else if (arg == "bass_down") {
        irsend.sendNEC(SOUNDBAR_BASS_DOWN, 32);
    } else if (arg == "eq_music") {
        irsend.sendNEC(SOUNDBAR_EQ_MUSIC, 32);
        last_eq_selected = "music";
    } else if (arg == "eq_movie") {
        irsend.sendNEC(SOUNDBAR_EQ_MOVIE, 32);
        last_eq_selected = "movie";
    } else if (arg == "eq_dialog") {
        irsend.sendNEC(SOUNDBAR_EQ_DIALOG, 32);
        last_eq_selected = "dialog";
    } else if (arg == "eq_3d") {
        irsend.sendNEC(SOUNDBAR_EQ_3D, 32);
        last_eq_selected = "3d";
    }
}

/**
 * Check the command received for the Soundbar
 */
void soundBarArg() {
    String message = "";

    if (server.arg("action") == "") {
        message = "Soundbar argument not found";

        server.send(400, "text/plain", message);
    } else {
        message = "Soundbar  = ";
        message += server.arg("action");

        soundbarAction(server.arg("action"));

        server.send(200, "text/plain", message);
    }
}

/*********************************************************************/

/**
 * Send the last input and eq selected
 */
void last_selections() {
    String selections;
    DynamicJsonDocument doc(1024);

    doc["input"] = get_last_input_selected();
    doc["eq"] = get_last_eq_selected();
    serializeJson(doc, selections);

    server.send(200, "text/json", selections);
}

/*********************************************************************/

void setup() {
    irsend.begin();

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    WiFi.hostname("NodeMCU-Controller");

    server.on("/tv", tvArg);
    server.on("/soundbar", soundBarArg);
    server.on("/soundbar/last_selections", last_selections);

    server.begin();
}

void loop() {
    server.handleClient();
}
