#include "hw_switch.hpp"
#include "ws_server.hpp"

#include <Adafruit_NeoPixel.h>

#define PIN 2          // NeoPixel を接続した Arduino のピン
#define NUMPIXELS 1    // 接続している NeoPixel の数（例: 8個）

static Adafruit_NeoPixel pixels{ NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800 };

static hw_switch switches[]{
    hw_switch{ 3 },
    hw_switch{ 4 },
};

static websocket_server server{ 8000 };

uint32_t colorFromHex(const char* hex)
{
    long number = strtol(&hex[1], NULL, 16);    // "#"を飛ばして16進数に変換
    byte r = (number >> 16) & 0xFF;
    byte g = (number >> 8) & 0xFF;
    byte b = number & 0xFF;
    return pixels.Color(r, g, b);
}

void setup()
{
    Serial.begin(115200);
    for (auto& sw : switches)
    {
        sw.begin();
    }

    begin_wifi("dokinchan", "kokokoko");
    begin_mdns("m5");

    auto h_receive = [](const std::string& message)
    {
        Serial.println(message.c_str());
        pixels.setPixelColor(0, colorFromHex(message.c_str()));
        pixels.show();
    };

    server.begin();
    server.set_receive_handler(h_receive);

    pixels.begin();
}

void loop()
{
    char buffer[256];
    sprintf(buffer, R"({ "sw0": %d, "sw1": %d })", (int)switches[0].is_pressed(), (int)switches[1].is_pressed());
    server.send(buffer);

    server.update();

    delay(10);
}
