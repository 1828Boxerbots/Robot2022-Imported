// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include "RobotContainer.h"

RobotContainer::RobotContainer() 
{
  // Initialize all of your commands and subsystems here
  m_pDriveCommand = new DriveCommand(&m_driveTrain, &m_controllerOne, DriveTrainSubsystem::TANK_STYLE);

  m_pSwitchTop = new SwitchCaseTop(&m_driveTrain);
  m_pSwitchMid = new SwitchCaseMid(&m_driveTrain);
  m_pSwitchBottom = new SwitchCaseBottom(&m_driveTrain);
  m_ploader = new LoadInOne(&m_pLoadItUp,1);
  m_pNumberOneCallAFullStop= new LoadInOne(&m_pLoadItUp,0);
  m_pEject = new LoadInOne(&m_pLoadItUp,-1);
  m_pLoadInner = new LoadInnerCommand(&m_pLoadItUp, 1.0);
  m_pLoadIntake = new LoadIntakeCommand(&m_pLoadItUp, 1.0);
  m_ploadToPhoto = new LoadToPhotoCommand(&m_pLoadItUp, 1.0);
  m_pStopIntale = new LoadIntakeCommand(&m_pLoadItUp, 0.0);
  m_pStopInnter = new LoadInnerCommand(&m_pLoadItUp, 0.0);
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::Init()
{
  m_driveTrain.Init();
}

void RobotContainer::ConfigureButtonBindings() 
{
  // Configure your button bindings here
  SetButtonY();
  SetButtonA();
  SetButtonX();
  SetButtonB();
  SetLeftBumper();
}

void RobotContainer::SetButtonB()
{
   m_bButton.WhenHeld(m_pLoadIntake);
  m_bButton.WhenReleased(m_pStopIntale);
}

void RobotContainer::SetButtonX()
{
    m_xButton.WhenHeld(m_pLoadInner);
    m_xButton.WhenReleased(m_pStopInnter);
}

void RobotContainer::SetLeftBumper()
{
  m_leftBumper.WhenHeld(m_ploadToPhoto);
}


void RobotContainer::SetButtonY()
{
//Shoot, because the shooter is at the peak of the robot.
  m_yButton.WhenHeld(m_pEject);
  m_yButton.WhenReleased(m_pNumberOneCallAFullStop);
}

void RobotContainer::SetButtonA()
{
  //Load, Because the loader is near the drive train on the bottom.
  m_aButton.WhenHeld(m_ploader);
  m_aButton.WhenReleased(m_pNumberOneCallAFullStop);
}

void RobotContainer::RunDrive()
{
  // RUN DRIVE
  m_driveTrain.SetDefaultCommand(*m_pDriveCommand);
}

int RobotContainer::GetDPDT()
{
  // bool isTop = !m_topSwitch.Get();
  // bool isBottom = !m_bottomSwitch.Get();
  bool isTop = false;
  bool isBottom = false;
  frc::SmartDashboard::PutBoolean("TopSwitch", isTop);
  frc::SmartDashboard::PutBoolean("BottomSwitch", isBottom);
  
  int value = -1;
  if(isTop)
  {
    value = 1;
  }
  else if(isBottom)
  {
    value = 2;
  }
  else
  {
    value = 3;
  }

  frc::SmartDashboard::PutNumber("DPDT Value", value);
  return value;
}

void RobotContainer::EncoderValues()
{
  double disLeft, disRight;
  int rawLeft, rawRight;
  m_driveTrain.GetEncoderDistance(&disLeft, &disRight);
  m_driveTrain.GetEncoderRaw(&rawLeft, &rawRight);
  units::degree_t angle = m_driveTrain.GetADIAngle();

  frc::SmartDashboard::PutNumber("Left E Dis", disLeft);
  frc::SmartDashboard::PutNumber("Right E Dis", disRight);
  frc::SmartDashboard::PutNumber("Left E Raw", rawLeft);
  frc::SmartDashboard::PutNumber("Right E Raw", rawRight);

  frc::SmartDashboard::PutNumber("ADI Angle", (double)angle);
}

frc2::Command* RobotContainer::GetAutonomousCommand() 
{
  frc2::Command* cmd = nullptr;
  frc::SmartDashboard::PutBoolean("Auto Status", true);
  switch (GetDPDT())
  {
  case 1:
    cmd = m_pSwitchTop;
    break;
    
  case 2:
    cmd = m_pSwitchBottom;
    break;

  case 3:
    cmd = m_pSwitchMid;
    break;

  default:
    cmd = nullptr;
    break;
  }
  
  if(cmd == nullptr)
  {
    frc::SmartDashboard::PutBoolean("Auto Status", false);
  }
  return cmd;
}
