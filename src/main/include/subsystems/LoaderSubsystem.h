// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/Victor.h>
#include "Constants.h"
#include <frc/DigitalInput.h>

class LoaderSubsystem : public frc2::SubsystemBase {
 public:
  LoaderSubsystem();

  void Init();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  // Motor Intake Functions
  void IntakeLoader(double speed);
  void InnerLoader(double speed);
  // Photogate Functions
  void LoadToPhoto(double speed);
  bool IsPhotoActive();

  // LimitSwitch Functions (For now, it is Halleffect)
  bool IsHighLimitSwitchActive();
  bool IsLowLimitSwitchActive();
  //Arm Functions
  void MoveArm(double speed);

 private:
 int m_heartBeat = 0;
 #ifndef NOHW
  frc::Victor m_intake{PWM_LOADER_INTAKE};
  frc::Victor m_inner{PWM_LOADER_INNER};
  frc::Victor m_innerUp{PWM_LOADER_INTAKE_UPPER};
  frc::Victor m_arm{PWM_ARM};

  frc::DigitalInput m_photogate{DIO_PHOTOGATE};
  frc::DigitalInput m_limitSwitchLow{DIO_HALLEFFECT_LOWER};
  frc::DigitalInput m_limitSwitchHigh{DIO_HALLEFFECT_HIGHER};

 #endif
  // Photogate

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
