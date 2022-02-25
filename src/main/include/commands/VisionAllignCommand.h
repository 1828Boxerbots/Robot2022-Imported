// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include "subsystems/DriveTrainSubsystem.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class VisionAllignCommand
    : public frc2::CommandHelper<frc2::CommandBase, VisionAllignCommand> {
 public:
  VisionAllignCommand(DriveTrainSubsystem *pDrive, double speed = 0.5, units::degree_t deadZone = 1.0_deg);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
 protected:
  DriveTrainSubsystem *m_pDrive;
  double m_speed;
  units::degree_t m_deadZone;

  //Networktable table
  std::shared_ptr<nt::NetworkTable> m_table;

  //Networktable Entries
  nt::NetworkTableEntry m_piAngle;

  double m_turnAngle;

  bool m_isFinished = false;
};
