// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>

#include "subsystems/DriveTrainSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/LoaderSubsystem.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class VisionShootCommand
    : public frc2::CommandHelper<frc2::CommandBase, VisionShootCommand> {
 public:
  VisionShootCommand(DriveTrainSubsystem* pDrive, ShooterSubsystem* pShooter, LoaderSubsystem* pLoader, double driveSpeed, double loadSpeed, units::degree_t deadZone);

  void Initialize() override;

  void Execute() override;

  void LoadToPhoto();
  void VisionAllign();
  void ShootSpeed(double targetSpeed);

  void End(bool interrupted) override;

  bool IsFinished() override;
 protected:
  DriveTrainSubsystem* m_pDrive;
  ShooterSubsystem* m_pShooter;
  LoaderSubsystem* m_pLoader;
  double m_driveSpeed;
  double m_loadSpeed;
  units::degree_t m_deadZone;

  //Networktable table
  std::shared_ptr<nt::NetworkTable> m_table;

  //Networktable Entries
  nt::NetworkTableEntry m_piAngle;

  double m_turnAngle;

  bool m_isFinished = false;
};
