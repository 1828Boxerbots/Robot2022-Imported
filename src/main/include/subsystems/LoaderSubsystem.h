// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/Victor.h>
#include <frc/Servo.h>

#include "Constants.h"

class LoaderSubsystem : public frc2::SubsystemBase {
 public:
  LoaderSubsystem();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  // Arm Functions
  double GetServo();
  void SetServoAngle(double angle);
  // Motor Intake Functions
  void IntakeLoader(double speed);
  void InnerLoader(double speed);
  // Photogate Functions
  bool IsPhotoActive();

 private:
 #ifndef NOHW
  frc::Servo m_armServo{PWM_ARM_SERVO};
  frc::Victor m_intake{PWM_LOADER_INTAKE};
  frc::Victor m_inner{PWM_LOADER_INNER};
 #endif
  // Photogate

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
