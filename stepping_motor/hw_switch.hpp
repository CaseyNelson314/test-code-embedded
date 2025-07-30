#pragma once

class hw_switch
{
    uint8_t pin;
    
public:
    hw_switch(uint8_t pin)
        : pin { pin }
    {}

    void begin()
    {
        pinMode(pin, INPUT_PULLUP);
    }

    bool is_pressed() const
    {
        return digitalRead(pin) == LOW;
    }
};
