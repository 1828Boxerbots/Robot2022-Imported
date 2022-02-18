// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <frc/motorcontrol/Spark.h>

#include "Constants.h"

class ClimbSubsystem : public frc2::SubsystemBase {
 public:
  ClimbSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  // ENCODER FUNCTIONS
  void ResetEncoder();
  double GetDistance();
  int GetRaw();

  // MOTOR FUNCTIONS
  void ClimbMotor(double speed);

 private:
 #ifndef NOHW
  frc::Spark m_climb{PWM_CLIMB};

  frc::Encoder m_encoderFront{DIO_CLIMB_ENCODER_A, DIO_CLIMB_ENCODER_B};
 #endif

  double m_pulseDisFront = 0.1;
  double m_pulseDisBack = 0.1;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
