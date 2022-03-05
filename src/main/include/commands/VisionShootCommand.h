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
  VisionShootCommand(DriveTrainSubsystem* pDrive, ShooterSubsystem* pShooter, LoaderSubsystem* pLoader, double targetSpeed, double driveSpeed = 0.2, 
                      double loadSpeed = 1.0, double loadTime = 1, units::degree_t deadZone = 1_deg);

  void Initialize() override;

  void Execute() override;

  void LoadToPhoto();

  void End(bool interrupted) override;

  bool IsFinished() override;
 protected:
  DriveTrainSubsystem* m_pDrive;
  ShooterSubsystem* m_pShooter;
  LoaderSubsystem* m_pLoader;
  double m_targetSpeed;
  double m_driveSpeed;
  double m_loadSpeed;
  double m_loadTime;
  units::degree_t m_deadZone;

  bool m_isFinished = false;
};
