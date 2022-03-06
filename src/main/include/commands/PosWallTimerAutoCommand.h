// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/DriveTrainSubsystem.h"
#include "subsystems/LoaderSubsystem.h"
#include "subsystems/ShooterSubsystem.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class PosWallTimerAutoCommand
    : public frc2::CommandHelper<frc2::CommandBase, PosWallTimerAutoCommand> {
 public:
  PosWallTimerAutoCommand(LoaderSubsystem *pLoader, ShooterSubsystem *pShoot, DriveTrainSubsystem *pDrive, 
  double turnAngleToShoot, double turnAngleToLeave);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  LoaderSubsystem *m_pLoaderSub;
  ShooterSubsystem *m_pShootSub;
  DriveTrainSubsystem *m_pDriveSub;
  
  double m_turnAngleToLeave = 0.0;
  double m_turnAngleToShoot = 0.0;
  bool m_isFinished = false;
};
