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
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class LoadIntakeCommand
    : public frc2::CommandHelper<frc2::CommandBase, LoadIntakeCommand> {
 public:
  LoadIntakeCommand(LoaderSubsystem* pLoader, frc::XboxController *pControll, double speed =0.5);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  LoaderSubsystem* m_pLoader;
  frc::XboxController *m_pControll=nullptr;
  double m_speed = 0.5;

  bool m_isFinished = false;
};
