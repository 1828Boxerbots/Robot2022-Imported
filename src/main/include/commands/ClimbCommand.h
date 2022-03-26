// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/ClimbSubsystem.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ClimbCommand
    : public frc2::CommandHelper<frc2::CommandBase, ClimbCommand> 
  {
 public:
  ClimbCommand(ClimbSubsystem *pClimb,double distance, double speed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  ClimbSubsystem *m_pClimb = nullptr;
  double m_dist  = 0.0;
  double m_speed = 0.0;
  bool m_IsFinished = false;
};
