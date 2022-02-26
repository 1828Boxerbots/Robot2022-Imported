// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriveTrainSubsystem.h"
#include "subsystems/LoaderSubsystem.h"
#include "subsystems/ShooterSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>


/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class Pos1AutoCommand
    : public frc2::CommandHelper<frc2::CommandBase, Pos1AutoCommand> {
 public:
  Pos1AutoCommand(DriveTrainSubsystem *pdrive, LoaderSubsystem *pload, ShooterSubsystem *pshoot, double turnAngle);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  
  DriveTrainSubsystem *m_pdrive = nullptr;
  LoaderSubsystem *m_ploader = nullptr;
  ShooterSubsystem *m_pshooter = nullptr;

  bool m_IsFinished = false;
  double m_turnAngle = 0.0;
};
