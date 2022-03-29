// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <frc/Servo.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/motorcontrol/Victor.h>

#include "Constants.h"
#include "Util.h"

class ClimbSubsystem : public frc2::SubsystemBase {
 public:
  ClimbSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void Init();

  // ENCODER FUNCTIONS
  void ResetEncoder();
  double GetDistance();
  int GetRaw();
  void EncoderTest();

  // MOTOR FUNCTIONS
  void ClimbMotor(double speed);
  void ClimbUpInInch(double inch, double speed);
  void ClimbDownInInch(double inch, double speed);

  //Servo
  void PeriodicRatchet();
  void SetRatchet(bool isEngaged = true);
  void ClimbDistance(double dist, double controllerValueY, double controllerValueX, double speed);

 private:
 #ifndef NOHW_CLIMB
  frc::Victor m_climb{PWM_CLIMB};
  frc::Encoder m_climbEncoder{DIO_CLIMB_ENCODER_A, DIO_CLIMB_ENCODER_B};
#ifndef NOHW_SERVO
  frc::Servo m_servo{PWM_CLIMB_SERVO};
 #endif
 #endif
  bool m_isTop = false;
  bool m_isEngaged = false;
  int m_heartbeat = 0;
  //Equation: circumfrence (pi*d) / pulses_per_revolution (have to test)
  const double m_DISPULSE_CLIMB = (6*3.14159)/360;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
