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
  double GetFrontDistance();
  double GetBackDistance();
  int GetFrontRaw();
  int GetBackRaw();

  // MOTOR FUNCTIONS
  void FrontClimb(double speed);
  void BackClimb(double speed);

 private:
 #ifndef NOHW
  frc::Spark m_front{PWM_CLIMB_FRONT};
  frc::Spark m_back{PWM_CLIMB_BACK};

  frc::Encoder m_encoderFront{DIO_CLIMBFRONT_ENCODER_A, DIO_CLIMBFRONT_ENCODER_B};
  frc::Encoder m_encoderBack{DIO_CLIMBBACK_ENCODER_A, DIO_CLIMBBACK_ENCODER_B};
 #endif

  double m_pulseDisFront = 0.1;
  double m_pulseDisBack = 0.1;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
