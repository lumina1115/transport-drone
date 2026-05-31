/*
 * 运输无人机 - 收放机构舵机控制（模板）
 *
 * 硬件：Arduino Nano + 9g 舵机
 * 信号：接收机某通道 PWM → 引脚 2（需根据实际接线修改）
 * 舵机：引脚 9
 *
 * 逻辑：PWM 高电平 → 释放；低电平 → 夹紧
 * 角度值请根据实际机构在桌面测试后调整
 */

#include <Servo.h>

const int RC_PIN = 2;
const int SERVO_PIN = 9;

const int ANGLE_GRASP = 0;    // 夹紧角度（待调）
const int ANGLE_RELEASE = 90; // 释放角度（待调）

const int PWM_THRESHOLD = 1500; // us，大于此值视为「释放」

Servo releaseServo;

void setup() {
  pinMode(RC_PIN, INPUT);
  releaseServo.attach(SERVO_PIN);
  releaseServo.write(ANGLE_GRASP);
}

void loop() {
  int pulse = pulseIn(RC_PIN, HIGH, 25000);

  if (pulse == 0) {
    return; // 无信号，保持当前状态
  }

  if (pulse > PWM_THRESHOLD) {
    releaseServo.write(ANGLE_RELEASE);
  } else {
    releaseServo.write(ANGLE_GRASP);
  }

  delay(20);
}
