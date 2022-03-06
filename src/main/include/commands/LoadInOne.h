// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include "subsystems/LoaderSubsystem.h"
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/XboxController.h>
class LoadInOne : public frc2::CommandHelper<frc2::CommandBase, LoadInOne> {
 public:

  LoadInOne( LoaderSubsystem* pLoader,double speed, frc::XboxController *pController);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private: 

  frc::XboxController *m_pController =nullptr; 
  LoaderSubsystem* m_pLoader=nullptr;
  bool m_isFinished=false;
  double m_speed;
};