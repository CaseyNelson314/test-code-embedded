class TB6643KQ
{
    int pin1;
    int pin2;

public:
    TB6643KQ(int pin1, int pin2)
        : pin1{ pin1 }
        , pin2{ pin2 }
    {}

    void move(int duty)
    {
        if (duty >= 0)
            cw(abs(duty));
        else
            ccw(abs(duty));
    }

private:
    void cw(uint8_t duty)
    {
        analogWrite(pin1, duty);
        analogWrite(pin2, 0);
    }

    void ccw(uint8_t duty)
    {
        analogWrite(pin1, 0);
        analogWrite(pin2, duty);
    }
    
};

TB6643KQ motor{ 15, 14 };

void setup()
{
    motor.begin();
}

void loop()
{
    motor.move(-50);
}
