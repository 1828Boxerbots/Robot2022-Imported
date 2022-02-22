// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/button/Button.h>
#include <frc2/command/Command.h>
#include <frc/XboxController.h>

#include "commands/ShooterCommand.h"
#include "commands/LoadInOne.h"

#include "subsystems/DriveTrainSubsystem.h"
#include "commands/DriveCommand.h"
#include "commands/LoadInnerCommand.h"
#include "commands/LoadIntakeCommand.h"
#include "subsystems/LoaderSubsystem.h"
#include "commands/AutoTestCMD/SwitchCaseTop.h"
#include "commands/AutoTestCMD/SwitchCaseMid.h"
#include "commands/AutoTestCMD/SwitchCaseBottom.h"

#include <frc/DigitalInput.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  void Init();

  frc2::Command* GetAutonomousCommand(); 
  void RunDrive();
  int GetDPDT();
  void EncoderValues();

 private:
  // The robot's subsystems and commands are defined here...
  DriveTrainSubsystem m_driveTrain;
  DriveCommand* m_pDriveCommand = nullptr;
  LoadInnerCommand* m_pLoadInner = nullptr;
  LoadInnerCommand* m_pStopInnter = nullptr;
  LoadIntakeCommand* m_pLoadIntake = nullptr;
  LoadIntakeCommand* m_pStopIntale = nullptr;

  // AUTO TEST CMD
  SwitchCaseTop* m_pSwitchTop = nullptr;
  SwitchCaseMid* m_pSwitchMid = nullptr;
  SwitchCaseBottom* m_pSwitchBottom = nullptr;

  frc::XboxController m_controllerOne{USB_CONTROLLER_ONE};
  frc::XboxController m_controllerTwo{USB_CONTROLLER_TWO};

  frc::DigitalInput m_topSwitch{DIO_DPDT_TOP};
  frc::DigitalInput m_bottomSwitch{DIO_DPDT_BOTTOM};

  void ConfigureButtonBindings();
  //Buttons
  void SetButtonA();
  void SetButtonB();
  void SetButtonX();
  void SetButtonY();
  LoaderSubsystem* m_pLoadItUp=nullptr;
  frc2::Button m_yButton {[this] {return m_controllerOne.GetYButton();}};
  frc2::Button m_aButton {[this] {return m_controllerOne.GetAButton();}};
  frc2::Button m_xButton {[this] {return m_controllerOne.GetXButton();}};
 LoadInOne *m_ploader                = nullptr;
 LoadInOne *m_pEject                 = nullptr;
 LoadInOne *m_pNumberOneCallAFullStop= nullptr;
};