// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionShootCommand.h"

VisionShootCommand::VisionShootCommand(DriveTrainSubsystem* pDrive, ShooterSubsystem* pShooter, LoaderSubsystem* pLoader, double driveSpeed, double loadSpeed, units::degree_t deadZone)
{
  m_pDrive = pDrive;
  m_pShooter = pShooter;
  m_pLoader = pLoader;
  m_driveSpeed = driveSpeed;
  m_loadSpeed = loadSpeed;
  m_deadZone = deadZone;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
  AddRequirements(m_pShooter);
  AddRequirements(m_pLoader);
}

// Called when the command is initially scheduled.
void VisionShootCommand::Initialize()
{
  auto inst = nt::NetworkTableInstance::GetDefault();

  m_table = inst.GetTable("datatable");

  m_piAngle = m_table->GetEntry("Angle");
}

// Called repeatedly when this Command is scheduled to run
void VisionShootCommand::Execute()
{
  // LoadToPhoto
  LoadToPhoto();
  // Vision Allign
  VisionAllign();

  //Calculate the speed of the shooter needed

  // ShootSpeed
  ShootSpeed(1000);

  m_isFinished = true;
}

void VisionShootCommand::LoadToPhoto()
{
  m_pLoader->IntakeLoader(m_loadSpeed);
  m_pLoader->InnerLoader(-m_loadSpeed);

  do 
  {
    bool photo = m_pLoader->IsPhotoActive();

    frc::SmartDashboard::PutBoolean("VisionShootCMD-Photo", photo);
  } while (m_pLoader->IsPhotoActive() == true);

  m_pLoader->IntakeLoader(0.0);
  m_pLoader->InnerLoader(0.0);
}

void VisionShootCommand::VisionAllign()
{
  m_turnAngle = -m_piAngle.GetDouble(-666);
  frc::SmartDashboard::PutNumber("PiAngle-VisionShootCMD", m_turnAngle);
  if(m_turnAngle != -666)
  {
    m_pDrive->TurnAngleRelative((units::degree_t)m_turnAngle, m_driveSpeed, m_deadZone);
  }
}

void VisionShootCommand::ShootSpeed(double targetSpeed)
{
  //Using a linear function speed= (1565)power + 0 (found testing different powers and graphing their speeds)
  // y=mx+b -> x= (y+b)/m
  //1565 is C418 shooter
  double power = targetSpeed / 1565;

  m_pShooter->ShootMotor(-power);
  while(m_pShooter->GetShooterSpeed() < targetSpeed)
  {
    m_pShooter->GetShooterSpeed();
  }
  
  while(!m_pLoader->IsPhotoActive())
  {
    m_pLoader->InnerLoader(-1.0);
  }

  m_pShooter->ShootMotor(0.0);
  m_pLoader->InnerLoader(0.0);  
}

// Called once the command ends or is interrupted.
void VisionShootCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionShootCommand::IsFinished() {
  return m_isFinished;
}
