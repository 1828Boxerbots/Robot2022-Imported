// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionShootCommand.h"

VisionShootCommand::VisionShootCommand(DriveTrainSubsystem* pDrive,/* ShooterSubsystem* pShooter, LoaderSubsystem* pLoader,*/ double distance, double driveSpeed, 
                      double loadSpeed, double loadTime, units::degree_t deadZone)
{
  m_pDrive = pDrive;
  //m_pShooter = pShooter;
  //m_pLoader = pLoader;
  m_distance = distance;
  m_driveSpeed = driveSpeed;
  m_loadSpeed = loadSpeed;
  m_loadTime = loadTime;
  m_deadZone = deadZone;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
  //AddRequirements(m_pShooter);
  //AddRequirements(m_pLoader);

  
}

// Called when the command is initially scheduled.
void VisionShootCommand::Initialize()
{
  m_isFinished = false;
  m_haveTurnAngle = false;
  m_heart = 0;
  m_turnAngle = -666.0;
}

// Called repeatedly when this Command is scheduled to run
void VisionShootCommand::Execute()
{
  if(m_pDrive->GetPIAngle() <= -665 && m_pDrive->GetPIAngle() >= -667)
  {
    m_pDrive->MoveTank(0.000, 0.000);
    m_isFinished = true;
    return;
  }

  Util::Log("HaveTurnAngle", m_haveTurnAngle);
  //Util::Log("VisionFinished", m_isFinished);
  Util::Log("Vision Current", (double)currentAngle);
  Util::Log("Vision Turn", m_turnAngle);
  Util::Log("Vision Heart", m_heart++);
  if(!m_haveTurnAngle)
  {
    m_turnAngle = m_pDrive->GetPIAngle();
    currentAngle = m_pDrive->GetADIAngle();//Use GetAngleX for C418.
    if(m_turnAngle <= -665 && m_turnAngle >= -667)
    {
      m_pDrive->MoveTank(0.000, 0.000);
      Util::Log("VisionFinished", true);
      m_isFinished = true;
    }
    targetAngle = currentAngle + (units::degree_t)m_turnAngle;
    lowAngle = targetAngle - m_deadZone;
    highAngle = targetAngle + m_deadZone;

    m_haveTurnAngle = true;
  }

  if(m_turnAngle <= -665 && m_turnAngle >= -667)
  {
    m_pDrive->MoveTank(0.000,0.000);
    Util::Log("VisionFinished", true);
    m_isFinished = true;
  }

  currentAngle = m_pDrive->GetADIAngle();

  if(currentAngle > highAngle)
  {
    // Turning Left
    m_pDrive->MoveTank(-m_driveSpeed, m_driveSpeed);
    Util::Log("Vision Turn Dir", "Trun Left");
  }
  else if(currentAngle < lowAngle)
  {
    //Turning Right
    m_pDrive->MoveTank(m_driveSpeed, -m_driveSpeed);
    Util::Log("Vision Turn Dir", "Trun Right");
  }
  else
  {
    m_pDrive->MoveTank(0, 0);
    Util::Log("VisionFinished", true);
    m_haveTurnAngle = false;
    m_isFinished = true;
  }

  // Vision Allign
  // if(m_pDrive->VisionAllign(m_driveSpeed, m_deadZone))
  // {

  //   //Calculate the speed of the shooter needed
  //   // rev/s = 0.74*distance + 20.1
  //   // y = 0.74x + 20.1
  //   double targetSpeed = (0.74*m_distance) + 20.1;

  //   // ShootSpeed
  //   m_pShooter->SetShooterSpeed(targetSpeed);

  //   m_pLoader->LoadToTimer(m_loadTime, m_loadSpeed);

  //   m_pShooter->ShootMotor(0.0);
  // }

  // m_isFinished = true;
}

// Called once the command ends or is interrupted.
void VisionShootCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionShootCommand::IsFinished() {
  return m_isFinished;
}
