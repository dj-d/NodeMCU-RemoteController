#ifndef UNIT_TEST

#include <Arduino.h>

#endif

#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";
WiFiServer server(80);

IRsend irsend(14);  // IR LED is controlled by GPIO14 (D5)

void setup(void) {
    irsend.begin();

    Serial.begin(9600);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    server.begin();
}

void loop(void) {
    WiFiClient client = server.available();

    if (!client) {
        return;
    }

    while (!client.available()) {
        delay(1);
    }

    String req = client.readStringUntil('\r');

    client.flush();

    /*****************************************/
    // TV
    if (req.indexOf("tv_on") != -1) {
        irsend.sendNEC(0x20DF10EF, 32);
    }

    if (req.indexOf("tv_input") != -1) {
        irsend.sendNEC(0x20DFD02F, 32);
    }

    if (req.indexOf("tv_vol_up") != -1) {
        irsend.sendNEC(0x20DF40BF, 32);
    }

    if (req.indexOf("tv_vol_down") != -1) {
        irsend.sendNEC(0x20DFC03F, 32);
    }

    if (req.indexOf("tv_program_up") != -1) {
        irsend.sendNEC(0x20DF00FF, 32);
    }

    if (req.indexOf("tv_program_down") != -1) {
        irsend.sendNEC(0x20DF807F, 32);
    }

    if (req.indexOf("tv_arrow_up") != -1) {
        irsend.sendNEC(0x20DF02FD, 32);
    }

    if (req.indexOf("tv_arrow_down") != -1) {
        irsend.sendNEC(0x20DF827D, 32);
    }

    if (req.indexOf("tv_arrow_left") != -1) {
        irsend.sendNEC(0x20DFE01F, 32);
    }

    if (req.indexOf("tv_arrow_right") != -1) {
        irsend.sendNEC(0x20DF609F, 32);
    }

    if (req.indexOf("tv_settings") != -1) {
        irsend.sendNEC(0x20DFC23D, 32);
    }

    if (req.indexOf("tv_back") != -1) {
        irsend.sendNEC(0x20DF14EB, 32);
    }

    // SOUNDBAR

    if (req.indexOf("sound_on") != -1) {
        irsend.sendNEC(0x40BF12ED, 32);
    }

    if (req.indexOf("sound_aux") != -1) {
        irsend.sendNEC(0x40BFB04F, 32);
    }

    if (req.indexOf("sound_hdmi") != -1) {
        irsend.sendNEC(0x40BF629D, 32);
    }

    if (req.indexOf("sound_usb") != -1) {
        irsend.sendNEC(0x40BF9867, 32);
    }

    if (req.indexOf("sound_optical") != -1) {
        irsend.sendNEC(0x40BF906F, 32);
    }

    if (req.indexOf("sound_bluetooth") != -1) {
        irsend.sendNEC(0x40BFF20D, 32);
    }

    if (req.indexOf("sound_display") != -1) {
        irsend.sendNEC(0x40BFA25D, 32);
    }

    if (req.indexOf("sound_vol_up") != -1) {
        irsend.sendNEC(0x40BFA05F, 32);
    }

    if (req.indexOf("sound_vol_down") != -1) {
        irsend.sendNEC(0x40BFF00F, 32);
    }

    if (req.indexOf("sound_mute") != -1) {
        irsend.sendNEC(0x40BF926D, 32);
    }

    if (req.indexOf("sound_next_track") != -1) {
        irsend.sendNEC(0x40BF02FD, 32);
    }

    if (req.indexOf("sound_previous_track") != -1) {
        irsend.sendNEC(0x40BF22DD, 32);
    }
    if (req.indexOf("sound_play_pause") != -1) {
        irsend.sendNEC(0x40BFC23D, 32);
    }

    if (req.indexOf("sound_stop") != -1) {
        irsend.sendNEC(0x40BF30CF, 32);
    }

    if (req.indexOf("sound_loop") != -1) {
        irsend.sendNEC(0x40BF6897, 32);
    }

    if (req.indexOf("sound_treble_up") != -1) {
        irsend.sendNEC(0x40BF7A85, 32);
    }

    if (req.indexOf("sound_treble_down") != -1) {
        irsend.sendNEC(0x40BF18E7, 32);
    }

    if (req.indexOf("sound_bass_up") != -1) {
        irsend.sendNEC(0x40BF38C7, 32);
    }

    if (req.indexOf("sound_bass_down") != -1) {
        irsend.sendNEC(0x40BF10EF, 32);
    }

    if (req.indexOf("sound_eq_music") != -1) {
        irsend.sendNEC(0x40BF5AA5, 32);
    }

    if (req.indexOf("sound_eq_movie") != -1) {
        irsend.sendNEC(0x40BF42BD, 32);
    }

    if (req.indexOf("sound_eq_dialog") != -1) {
        irsend.sendNEC(0x40BF4AB5, 32);
    }

    if (req.indexOf("sound_eq_3d") != -1) {
        irsend.sendNEC(0x40BF52AD, 32);
    }
}
