// Copyright (c) LAST and other biLIPW contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the biLIPW BSD license file in the root directory of this project.

#pragma once
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>
#include "subsystems/ShooterSubsystem.h"
/********************************************************************************
 * Not an example command.                                                          *
 *                                                                              *
 * Note that this extends CommandHelper, rather extending CommandBase           *
 * directly; this is crucially important, or else the decorator functions in    *
 * Command will *not* work!                                                     *
 ********************************************************************************/
class ShooterCommand
    : public frc2::CommandHelper<frc2::CommandBase, ShooterCommand> {
 public:
  ShooterCommand(ShooterSubsystem * pShoot, frc::XboxController *pxBox, double speed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
private:
ShooterSubsystem* m_pShooter;
frc::XboxController* m_pXBox;
double m_speed;
bool m_isFinished=false;
};