#pragma once

//
//   wifi client
//
//   copyright (c) 2024 okawa yusuke
//

#pragma once

// #include <string>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebSocketsServer.h>


inline void begin_wifi(const char* ssid, const char* password)
{
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println(" connected");
}

inline void begin_mdns(const char* hostname)
{
    if (!MDNS.begin(hostname))
    {
        Serial.println("Error starting mDNS");
        return;
    }
    Serial.printf("mDNS responder started: ws://%s.local\n", hostname);
}

class websocket_server
{
    int sockid = 0;
public:
    using request_handler_t = void (*)(const std::string&);

    websocket_server(uint16_t port)
        : websocket(port)
    {
    }

    void begin()
    {
        websocket.begin();
    }

    void set_receive_handler(request_handler_t handler)
    {
        request_handler = handler;

        auto f = [this](uint8_t socket_id, WStype_t type, uint8_t* payload, size_t length)
        {
            if (type == WStype_TEXT)
            {
                this->request_handler(std::string{ (char*)payload, length });
            }
            this->sockid = socket_id;
        };

        websocket.onEvent(f);
    }

    void send(const std::string& message)
    {
        websocket.sendTXT(sockid, message.c_str());
    }

    void update()
    {
        websocket.loop();
    }

private:
    WebSocketsServer websocket;
    request_handler_t request_handler;
};