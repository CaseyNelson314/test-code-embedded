#pragma once

// 1回の動作計画を表す
// 何の値を制御するかをこの構造体は関知しないため単位は不定
struct move_plan
{
    uint32_t start_ms;  // 実行開始時間

    // 台形制御速度プロファイル
    float target_pos;        // 目標値 (絶対位置)
    
    float max_speed;         // 最高速度
    float max_acc;           // 最高加速度

    uint32_t acc_time_ms;    // 加減速時間
    uint32_t const_time_ms;  // 等速時間
};
