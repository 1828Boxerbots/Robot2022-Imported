// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/XboxController.h>
#include "subsystems/LoaderSubsystem.h"

/**
 * An example command.
 *
 * Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ArmCommand
    : public frc2::CommandHelper<frc2::CommandBase, ArmCommand> {
 public:
  ArmCommand(LoaderSubsystem *pLoader, double speed, frc::XboxController*pbox);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  protected:
  LoaderSubsystem *m_pLoader;

  double m_speed = 0;
  frc::XboxController *m_pBox;
  bool m_isFinished = false;
};
