// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

RobotContainer::RobotContainer() 
{
  // Initialize all of your commands and subsystems here
  m_pDriveCommand = new DriveCommand(&m_driveTrain, &m_controllerOne, DriveTrainSubsystem::RC_STYLE);

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
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

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
