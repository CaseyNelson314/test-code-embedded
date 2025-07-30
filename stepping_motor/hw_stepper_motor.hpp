//
//  ステッピングモータードライバ
//
//  AccelStepperライブラリラッパー
//


#pragma once

#include <AccelStepper.h>


class stepper_motor
{
    AccelStepper driver;
    const float angle_to_step; // 角度[rad]からステップ[count]に変換する際の係数

    move_plan prev_move_plan{};

    bool is_homed{};  // 原点どりが完了しているか
    int homing_sequence{};

    uint8_t limit_switch_pin;

public:
    struct config {
        uint8_t step_pin;
        uint8_t dir_pin;
        uint8_t limit_switch_pin;
        int motor_resolution;
    };
    
    /// @brief constructor
    /// @param step_pin
    /// @param dir_pin
    /// @param motor_resolution 一回させるためのパルス数 [count/rev]
    stepper_motor(const config& conf)
        : driver{ AccelStepper::DRIVER, conf.step_pin, conf.dir_pin }
        , angle_to_step{ conf.motor_resolution / (2 * M_PI) }
        , limit_switch_pin{ conf.limit_switch_pin }
    {}

    void begin()
    {
        pinMode(limit_switch_pin, INPUT_PULLUP);
    }

    /// @brief 動作計画実行
    void execute_move_plan_polling(const move_plan& move_plan)
    {
        if (not is_homed)
            return;

        // 速度プロファイルの再計算重いから、目標値が変更されたときに再計算させる
        if (move_plan != prev_move_plan)
        {
            driver.setMaxSpeed(move_plan.max_speed);
            driver.setAcceleration(move_plan.max_acc);
            driver.moveTo(move_plan.target_pos * angle_to_step);
            prev_move_plan = move_plan;
        }

        driver.run();
    }

    /// @param back_distance 後退距離
    bool homing_polling(float back_distance, float approach_speed, bool limit_switch_dir, float limit_switch_angle)
    {
        switch (homing_sequence)
        {
        case 0:
            driver.setCurrentPosition(0);
            driver.moveTo(-back_distance);
            ++homing_sequence;

        case 1:
            if (driver.run())
            {
                ++homing_sequence;
            }
            break;

        case 2:
            driver.setSpeed(approach_speed * (limit_switch_dir ? 1 : -1));
            ++homing_sequence;
    
        case 1:
            if (digitalRead(limit_switch_pin) == LOW)
            {
                driver.setCurrentPosition(limit_switch_angle * angle_to_step);
                is_homed = true;
                homing_sequence = 0;
                return true;
            }
            driver.runSpeed();
            break;
        }

        return false;
    }

};
