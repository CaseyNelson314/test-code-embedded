#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 14, 15 );

void setup() {
  stepper.setMaxSpeed(8000);
  stepper.setAcceleration(8000);
  stepper.moveTo(1000);  // 目的地ステップ数
}

void loop() {
  if (Serial.available())
  {
    int new_pos = Serial.parseInt();
    stepper.moveTo(new_pos);  // 目的地ステップ数
    while (Serial.available())
    {
      Serial.read();
    }
  }
  stepper.run();  // これを頻繁に呼び出すことで非ブロッキング動作
}
