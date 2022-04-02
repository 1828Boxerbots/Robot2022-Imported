// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/ClimbSubsystem.h"
#include <frc/XboxController.h>


/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ManualClimbCommand
    : public frc2::CommandHelper<frc2::CommandBase, ManualClimbCommand> 
    {
 public:
  ManualClimbCommand(ClimbSubsystem *pClimbSub, frc::XboxController *pXbox, double speed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  
  double m_speed = 0.0;

  frc::XboxController *m_pXbox = nullptr;

  bool m_isFinished = false;

  ClimbSubsystem *m_pClimbSub = nullptr;


};
