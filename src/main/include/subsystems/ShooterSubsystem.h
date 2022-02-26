// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Encoder.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Constants.h"

class ShooterSubsystem : public frc2::SubsystemBase {
 public:
  ShooterSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  void Init();

  // Encocder Functions
  void ResetEncoder();
  double GetShooterSpeed();
  double GetShootDistance();
  int GetEncoderRaw();
  void SetShooterSpeed(double targetSpeed);

  // Shooter Functions
  void ShootMotor(double speed);

 private:
 #ifndef NOHW
  frc::Encoder m_shooterEncoder{DIO_SHOOTER_ENCODER_A, DIO_SHOOTER_ENCODER_B};
  frc::Spark m_shooterMotor{9};

  #endif
  // Halleffect
  //Equation: 1 / # of pulses per revolution (have to test)
  const double m_DISPULSE_SHOOT = 1.0/20.0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
