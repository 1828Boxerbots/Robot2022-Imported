// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionAllignCommand.h"

VisionAllignCommand::VisionAllignCommand(DriveTrainSubsystem *pDrive, double speed, units::degree_t deadZone)
{
  m_pDrive = pDrive;
  m_speed = speed;
  m_deadZone = deadZone;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void VisionAllignCommand::Initialize()
{
  //Get the default instance of NetworkTables that was created automatically
  auto inst = nt::NetworkTableInstance::GetDefault();

  //Get the table within that instance that contains the data. There can
  //be as many tables as you like and exist to make it easier to organize
  //your data. In this case, it's a table called datatable.
  m_table = inst.GetTable("datatable");

  //Get the entries within that table that correspond Angle from the PI
  m_piAngle = m_table->GetEntry("Angle");
}

// Called repeatedly when this Command is scheduled to run
void VisionAllignCommand::Execute()
{
  m_turnAngle = -m_piAngle.GetDouble(-666);
  frc::SmartDashboard::PutNumber("PiAngle", m_turnAngle);
  if(m_turnAngle != -666)
  {
    m_pDrive->TurnAngleRelative((units::degree_t)m_turnAngle, m_speed, m_deadZone);
  }
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void VisionAllignCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionAllignCommand::IsFinished()
{
  return m_isFinished;
}
