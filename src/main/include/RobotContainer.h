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
#include "commands/LoadToPhotoCommand.h"
#include "commands/DriveCommand.h"
#include "commands/LoadInnerCommand.h"
#include "commands/LoadIntakeCommand.h"
#include "subsystems/LoaderSubsystem.h"
#include "commands/AutoTestCMD/SwitchCaseTop.h"
#include "commands/AutoTestCMD/SwitchCaseMid.h"
#include "commands/AutoTestCMD/SwitchCaseBottom.h"
#include "subsystems/ShooterSubsystem.h"
#include "commands/AutoArmCommand.h"
#include "subsystems/ClimbSubsystem.h"
#include "commands/ClimbCommand.h"
#include "commands/Pos1AutoCommand.h"
#include "commands/LoadToShooterCommand.h"

#include "commands/VisionAllignCommand.h"
#include "commands/ShootSpeedCommand.h"

#include <frc/DigitalInput.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer 
{
 public:
  RobotContainer();

  void Init();

  void TestPhoto();

  void ClimbEncoder();

  frc2::Command* GetAutonomousCommand(); 
  void RunDrive();
  int GetDPDT();
  void EncoderValues();

 private:
    // The robot's subsystems and commands are defined here...
    DriveTrainSubsystem m_driveTrainSub;
    LoaderSubsystem m_loaderSub;
    ShooterSubsystem m_shootSub;
    ClimbSubsystem m_ClimbSub;

    LoadToPhotoCommand *m_ploadToPhotoCmd = nullptr;
    LoadToShooterCommand *m_ploadToShooterCmd = nullptr;
    DriveCommand* m_pdriveCmd = nullptr;
    LoadInnerCommand* m_ploadInnerCmd = nullptr;
    LoadInnerCommand* m_pstopInnerCmd = nullptr;
    LoadIntakeCommand* m_ploadIntakeCmd = nullptr;
    LoadIntakeCommand* m_pstopIntakeCmd = nullptr;
    AutoArmCommand *m_pupAutoArmCmd = nullptr;
    AutoArmCommand *m_pdownAutoArmCmd = nullptr;
    ClimbCommand *m_pupClimbCmd = nullptr;
    ClimbCommand *m_pdownClimbCmd = nullptr;
    

    VisionAllignCommand* m_pVisionAllignCmd = nullptr;

    // AUTO TEST CMD
    Pos1AutoCommand *m_pwallAutoCmd = nullptr;
    Pos1AutoCommand *m_pmiddleAutoCmd = nullptr;
    Pos1AutoCommand *m_paloneAutoCmd = nullptr;

    frc::XboxController m_controllerOne{USB_CONTROLLER_ONE};
    frc::XboxController m_controllerTwo{USB_CONTROLLER_TWO};

    // frc::DigitalInput m_topSwitch{DIO_DPDT_TOP};
    // frc::DigitalInput m_bottomSwitch{DIO_DPDT_BOTTOM};

    void ConfigureButtonBindings();
    //Buttons
    void SetButtonA();
    void SetButtonB();
    void SetButtonX();
    void SetButtonY();
    void SetRightBumper();
    void SetLeftBumper();
    void SetRightTrigger();
    void SetLeftTrigger();

    frc2::Button m_aButton {[this] {return m_controllerOne.GetAButton();}};
    frc2::Button m_bButton {[this] {return m_controllerOne.GetBButton();}};
    frc2::Button m_xButton {[this] {return m_controllerOne.GetXButton();}};
    frc2::Button m_yButton {[this] {return m_controllerOne.GetYButton();}};
    frc2::Button m_rightBumper {[this] {return m_controllerOne.GetRightBumper();}};
    frc2::Button m_leftBumper {[this] {return m_controllerOne.GetLeftBumper();}};
    frc2::Button m_rightTrigger {[this] {return m_controllerOne.GetRightTriggerAxis();}};
    frc2::Button m_leftTrigger {[this] {return m_controllerOne.GetLeftTriggerAxis();}};
    
    LoadInOne *m_ploader                = nullptr;
    LoadInOne *m_peject                 = nullptr;
    LoadInOne *m_pnumberOneCallAFullStop= nullptr;

    ShootSpeedCommand *m_pShootSpeed = nullptr;
    ShooterCommand *m_pShoot = nullptr;
    ShooterCommand *m_pStopShoot = nullptr;
};