#pragma once

class hw_switch
{
    int pin;

public:
    hw_switch(int pin)
        : pin{ pin }
    {
    }

    void begin()
    {
        pinMode(pin, INPUT_PULLUP);
    }

    bool is_pressed() const
    {
        return not digitalRead(pin);
    }
};
