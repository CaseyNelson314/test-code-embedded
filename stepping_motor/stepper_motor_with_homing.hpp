#pragma once

#include "hw_stepper_motor.hpp"
#include "hw_switch.hpp"

class stepper_motor_with_homing
{
    hw_stepper_motor stepper_motor;
    hw_switch limit_switch;

    int homing_step{};

public:
    stepper_motor_with_homing(
        hw_stepper_motor&& stepper_motor,
        hw_switch&&        limit_switch
    )
        : stepper_motor{ std::move(stepper_motor) }
        , limit_switch { std::move(limit_switch ) }
    {}

    bool homing()
    {
        if (homing_step == 0)
        {
            homing_step = 1;
            return false;
        }
        return true;
    }

    void begin()
    {
        limit_switch.begin();
    }

    void update_high_rate()
    {
        stepper_motor.update_high_rate();
    }
};
