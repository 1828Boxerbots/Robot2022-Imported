// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveTrainSubsystem.h"
#include "subsystems/LoaderSubsystem.h"
#include "subsystems/ShooterSubsystem.h"

#include "Util.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class UtahCompetitionCMD
    : public frc2::CommandHelper<frc2::CommandBase, UtahCompetitionCMD> {
 public:
  UtahCompetitionCMD(DriveTrainSubsystem* pDrive, LoaderSubsystem* pLoader, ShooterSubsystem* pShoot, double driveSpeed, double shootSpeed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 protected:
  DriveTrainSubsystem* m_pDrive;
  LoaderSubsystem* m_pLoader;
  ShooterSubsystem* m_pShoot;

  double m_driveSpeed;
  double m_shootSpeed;

  bool m_isFinished = false;
};
