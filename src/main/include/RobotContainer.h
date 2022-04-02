// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/button/Button.h>
#include <frc2/command/Command.h>
#include <frc/XboxController.h>

#include "commands/ArmCommand.h"
#include "commands/TheLoneTimerAutonomus.h"
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
#include "commands/PosWallAutoCommand.h"
#include "commands/VisionAllignCommand.h"
#include "commands/VisionShootCommand.h"
#include "commands/ShootSpeedCommand.h"
#include "commands/PosWallTimerAutoCommand.h"
#include "commands/ShootTriggerController.h"
#include "commands/CompetitionCMD.h"
#include "commands/ManualClimbCommand.h"

#include <frc2/command/button/POVButton.h>
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
  void TeleopPeriodic();
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
    ClimbCommand *m_pAutoUpClimbCmd = nullptr;
    ClimbCommand *m_pAutoDownClimbCmd = nullptr;
    ManualClimbCommand *m_pManualUpClimbCmd = nullptr;
    ManualClimbCommand *m_pManualDownClimbCmd = nullptr;
    ManualClimbCommand *m_pManualStopClimbCmd = nullptr;
    
    CompetitionCMD *m_plowHub = nullptr;

    VisionAllignCommand* m_pVisionAllignCmd = nullptr;
    VisionShootCommand* m_p15ftShoot        = nullptr;
    VisionShootCommand *m_p8ftShoot         = nullptr;
    VisionShootCommand *m_p13ftShoot        = nullptr;
    VisionShootCommand *m_p10ftShoot        = nullptr;

    // AUTO TEST CMD
    Pos1AutoCommand *m_pMiddleAutoCmd = nullptr;
    Pos1AutoCommand *m_pAloneAutoCmd = nullptr;
    PosWallAutoCommand *m_pWallAutoCmd = nullptr;
    PosWallTimerAutoCommand *m_pWallTimeAutoCmd = nullptr;
    TheLoneTimerAutonomus *m_pLonelyTimer = nullptr;
    TheLoneTimerAutonomus *m_pMiddleTimer = nullptr;
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
    void SetRightBumper();
    void SetLeftBumper();
    void SetRightTrigger();
    void SetLeftTrigger();
    void SetDpadUp();
    void SetDpadDown();
    void SetDpadLeft();
    void SetDpadRight();

    frc2::Button m_aButton {[this] {return m_controllerOne.GetAButton();}};
    frc2::Button m_bButton {[this] {return m_controllerOne.GetBButton();}};
    frc2::Button m_xButton {[this] {return m_controllerOne.GetXButton();}};
    frc2::Button m_yButton {[this] {return m_controllerOne.GetYButton();}};
    frc2::Button m_rightBumper {[this] {return m_controllerOne.GetRightBumper();}};
    frc2::Button m_leftBumper {[this] {return m_controllerOne.GetLeftBumper();}};
    frc2::Button m_rightTrigger {[this] {return m_controllerOne.GetRightTriggerAxis();}};
    frc2::Button m_leftTrigger {[this] {return m_controllerOne.GetLeftTriggerAxis();}};
    frc2::Button m_BackButton {[this]{return m_controllerOne.GetBackButton();}};
    frc2::Button m_StartButton {[this]{return m_controllerOne.GetStartButton();}};

    frc2::Button m_aButton2 {[this]{return m_controllerTwo.GetAButton();}};    
    frc2::Button m_bButton2 {[this]{return m_controllerTwo.GetBButton();}};    
    frc2::Button m_xButton2 {[this]{return m_controllerTwo.GetXButton();}};    
    frc2::Button m_yButton2 {[this]{return m_controllerTwo.GetYButton();}};    
    frc2::Button m_rightBumper2 {[this]{return m_controllerTwo.GetRightBumper();}};    
    frc2::Button m_leftBumper2 {[this]{return m_controllerTwo.GetLeftBumper();}};    
    frc2::Button m_leftTrigger2 {[this]{return m_controllerTwo.GetLeftTriggerAxis();}};    
    frc2::Button m_rightTrigger2 {[this]{return m_controllerTwo.GetRightTriggerAxis();}};
    frc2::Button m_BackButton2 {[this]{return m_controllerTwo.GetBackButton();}};
    frc2::Button m_StartButton2 {[this]{return m_controllerTwo.GetStartButton();}};
    frc2::POVButton m_POVup{&m_controllerTwo,0};
    frc2::POVButton m_POVdown{&m_controllerTwo,180};
    frc2::POVButton m_POVleft{&m_controllerTwo,270};
    frc2::POVButton m_POVright{&m_controllerTwo,90};

    LoadInOne *m_ploader                = nullptr;
    LoadInOne *m_peject                 = nullptr;
    LoadInOne *m_pLoadStop= nullptr;
    
    ArmCommand *m_pArmDown              = nullptr;
    ArmCommand *m_pArmStop              = nullptr;
    ShootSpeedCommand *m_pShootSpeed = nullptr;
    ShooterCommand *m_pShoot = nullptr;
    ShooterCommand *m_pShootStop = nullptr;
    ShooterCommand *m_pLowShoot = nullptr;
    ShooterCommand *m_pStopShoot = nullptr;
    ShooterCommand *m_pAdjSpeed = nullptr;
    ShootTriggerController *m_pShootTrigger = nullptr;
};