// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <frc/motorcontrol/Spark.h>

#include "Constants.h"

class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  // Encocder Functions
  void ResetEncoder();
  double GetEncoderSpeed();
  int GetEncoderRaw();

  // Shooter Functions
  void ShootMotor(double speed);

 private:
 #ifndef NOHW
  frc::Encoder m_shooterEncoder{DIO_SHOOTER_ENCODER_A, DIO_SHOOTER_ENCODER_B};
  frc::Spark m_shooterMotor{PWM_SHOOTER};

  #endif
  // Halleffect

  double m_pulseDisShoot = 2;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
