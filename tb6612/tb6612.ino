class tb6612
{
    int pin_in1;
    int pin_in2;
    int pin_pwm;

public:
    tb6612(int pin_in1, int pin_in2, int pin_pwm)
        : pin_in1{ pin_in1 }
        , pin_in2{ pin_in2 }
        , pin_pwm{ pin_pwm }
    {}

    void begin()
    {
        pinMode(pin_in1, OUTPUT);
        pinMode(pin_in2, OUTPUT);
    }

    void move(int duty)
    {
        int absed_duty = abs(duty);
        if (absed_duty > 255)
            return;

        if (duty >= 0)
            cw(absed_duty);
        else
            ccw(absed_duty);
    }

private:
    /// @brief 正転
    void cw(uint8_t duty)
    {
        digitalWrite(pin_in1, HIGH);
        digitalWrite(pin_in2, LOW);
        analogWrite(pin_pwm, duty);
    }

    /// @brief 逆転
    void ccw(uint8_t duty)
    {
        digitalWrite(pin_in1, LOW);
        digitalWrite(pin_in2, HIGH);
        analogWrite(pin_pwm, duty);
    }
};

tb6612 motor{ 15, 14, 16 };

void setup()
{
    motor.begin();
}

void loop()
{
    motor.move(-50);
}
