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
}

void RobotContainer::SetButtonA()
{
  
}

void RobotContainer::SetButtonB()
{

}

void RobotContainer::RunDrive()
{
  // RUN DRIVE
  m_driveTrain.SetDefaultCommand(*m_pDriveCommand);
}

int RobotContainer::GetDPDT()
{
  bool isTop = !m_topSwitch.Get();
  bool isBottom = !m_bottomSwitch.Get();
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
