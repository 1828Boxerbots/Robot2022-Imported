// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/LoaderSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include "subsystems/DriveTrainSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class PosWallAutoCommand
    : public frc2::CommandHelper<frc2::CommandBase, PosWallAutoCommand> {
 public:
  PosWallAutoCommand
  (LoaderSubsystem *pLoader, ShooterSubsystem *pShoot, DriveTrainSubsystem *pDrive,
  double turnAngle, double distanceBack, double turnAngleToLeave);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  
  bool m_isFinished = false;
  double m_turnAngleToShoot = 0.0;
  double m_turnAngleToLeave = 0.0;
  double m_distanceBack = 0.0;
  LoaderSubsystem *m_pLoaderSub;
  DriveTrainSubsystem *m_pDriveSub;
  ShooterSubsystem *m_pShooterSub;

};
