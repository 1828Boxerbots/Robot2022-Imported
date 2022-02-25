// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include "RobotContainer.h"

RobotContainer::RobotContainer() 
{
  // Initialize all of your commands and subsystems here
  m_pdriveCmd = new DriveCommand(&m_driveTrainSub, &m_controllerOne, DriveTrainSubsystem::TANK_STYLE);

  m_pswitchTop = new SwitchCaseTop(&m_driveTrainSub);
  m_pswitchMid = new SwitchCaseMid(&m_driveTrainSub);
  m_pswitchBottom = new SwitchCaseBottom(&m_driveTrainSub );
  m_ploader = new LoadInOne(&m_loaderSub,1);
  m_pnumberOneCallAFullStop= new LoadInOne(&m_loaderSub,0);
  m_peject = new LoadInOne(&m_loaderSub,1);
  m_ploadInnerCmd = new LoadInnerCommand(&m_loaderSub, -1.0);
  m_ploadIntakeCmd = new LoadIntakeCommand(&m_loaderSub, 1.0);
  m_ploadToPhotoCmd = new LoadToPhotoCommand(&m_loaderSub, 1.0);
  m_pstopIntakeCmd = new LoadIntakeCommand(&m_loaderSub, 0.0);
  m_pstopInnerCmd = new LoadInnerCommand(&m_loaderSub, 0.0);

  
  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::Init()
{
  m_driveTrainSub.Init();
}

void RobotContainer::TestPhoto()
{
  m_loaderSub.IsPhotoActive();
  m_shootSub.GetEncoderRaw();
}

void RobotContainer::ConfigureButtonBindings() 
{
  // Configure your button bindings here
  SetButtonY();
  SetButtonA();
  SetButtonX();
  SetButtonB();
  SetLeftBumper();
  SetRightTrigger();
}

void RobotContainer::SetButtonB()
{
  m_bButton.WhenHeld(m_ploadIntakeCmd);
  m_bButton.WhenReleased(m_pstopIntakeCmd);
}

void RobotContainer::SetButtonX()
{
  m_xButton.WhenHeld(m_ploadInnerCmd);
  m_xButton.WhenReleased(m_pstopInnerCmd);
}
void RobotContainer::SetRightTrigger()
{
}
void RobotContainer::SetLeftBumper()
{
    m_leftBumper.WhenHeld(m_ploadToPhotoCmd);
}


void RobotContainer::SetButtonY()
{
//Shoot, because the shooter is at the peak of the robot.
m_yButton.WhenHeld(m_peject);
m_yButton.WhenReleased(m_pnumberOneCallAFullStop);
}

void RobotContainer::SetButtonA()
{
  //Load, Because the loader is near the drive train on the bottom.
  m_aButton.WhenHeld(m_ploader);
  m_aButton.WhenReleased(m_pnumberOneCallAFullStop);
}

void RobotContainer::RunDrive()
{
  // RUN DRIVE
  m_driveTrainSub .SetDefaultCommand(*m_pdriveCmd);
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
  m_driveTrainSub .GetEncoderDistance(&disLeft, &disRight);
  m_driveTrainSub .GetEncoderRaw(&rawLeft, &rawRight);
  units::degree_t angle = m_driveTrainSub .GetADIAngle();

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
    cmd = m_pswitchTop;
    break;
    
  case 2:
    cmd = m_pswitchBottom;
    break;

  case 3:
    cmd = m_pswitchMid;
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
