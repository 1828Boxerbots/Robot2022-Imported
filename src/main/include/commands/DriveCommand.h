// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/DriveTrainSubsystem.h"
#include <frc/XboxController.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class DriveCommand
    : public frc2::CommandHelper<frc2::CommandBase, DriveCommand> {
 public:
  DriveCommand(DriveTrainSubsystem* pDriveTrain, frc::XboxController* pController, DriveTrainSubsystem::DriveStyles style);

  void Initialize() override;

  void Execute() override;

  double CheckDeadZone(double stickInput);

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    DriveTrainSubsystem* m_pDriveTrain;
    frc::XboxController* m_pController;
    DriveTrainSubsystem::DriveStyles m_style;

    double m_scale = 1.0;
    float m_deadZoneRange = 0.1f;

    double m_left = 0.0;
    double m_right = 0.0;
};
