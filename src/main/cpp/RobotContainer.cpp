// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include "RobotContainer.h"

RobotContainer::RobotContainer() 
{
  // Initialize all of your commands and subsystems here
  m_pdriveCmd = new DriveCommand(&m_driveTrainSub, &m_controllerOne, DriveTrainSubsystem::TANK_STYLE);
  m_ploader = new LoadInOne(&m_loaderSub,1);
  m_pnumberOneCallAFullStop= new LoadInOne(&m_loaderSub,0);
  m_peject = new LoadInOne(&m_loaderSub,1);
  m_ploadInnerCmd = new LoadInnerCommand(&m_loaderSub, -1.0);
  m_ploadIntakeCmd = new LoadIntakeCommand(&m_loaderSub, 1.0);
  m_ploadToPhotoCmd = new LoadToPhotoCommand(&m_loaderSub, 0.2);
  m_ploadToShooterCmd = new LoadToShooterCommand(&m_loaderSub, 0.2);
  m_pstopIntakeCmd = new LoadIntakeCommand(&m_loaderSub, 0.0);
  m_pstopInnerCmd = new LoadInnerCommand(&m_loaderSub, 0.0);
  m_pLonely = new TheLoneTimerAutonomus(&m_driveTrainSub,&m_loaderSub,&m_shootSub,180.0);
  m_pupAutoArmCmd = new AutoArmCommand(&m_loaderSub, 0.25);
  m_pdownAutoArmCmd = new AutoArmCommand(&m_loaderSub, -0.25);
  m_pdownClimbCmd = new ClimbCommand(&m_ClimbSub, -0.2, 340);
  m_pmiddleAutoCmd = new Pos1AutoCommand(&m_driveTrainSub, &m_loaderSub, &m_shootSub, -135.0);
  m_paloneAutoCmd = new Pos1AutoCommand(&m_driveTrainSub, &m_loaderSub, &m_shootSub, 180.0);
  m_pwallAutoCmd = new Pos1AutoCommand(&m_driveTrainSub, &m_loaderSub, &m_shootSub, 170.0);

  m_pShootSpeed = new ShootSpeedCommand(&m_shootSub, &m_loaderSub, 1600);
  m_pShoot = new ShooterCommand(&m_shootSub, 1);
  m_pStopShoot = new ShooterCommand(&m_shootSub, 0.0);

  m_pVisionAllignCmd = new VisionAllignCommand(&m_driveTrainSub);
  m_pVisionShootCmd = new VisionShootCommand(&m_driveTrainSub, &m_shootSub, &m_loaderSub, 0.3, 0.7, 2_deg);

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::Init()
{
  m_driveTrainSub.Init();
  m_loaderSub.Init();
  m_ClimbSub.Init();
  m_shootSub.Init();
}

void RobotContainer::TestPhoto()
{
  m_loaderSub.IsPhotoActive();
  m_shootSub.GetEncoderRaw();
}

void RobotContainer::ConfigureButtonBindings() 
{
  // Configure your button bindings here
  SetButtonY();
  SetButtonA();
  SetButtonX();
  SetButtonB();
  SetRightBumper();
  SetLeftBumper();
  SetRightTrigger();
  SetLeftTrigger();
}

void RobotContainer::SetButtonB()
{
  m_bButton.WhenPressed(m_pdriveCmd);
 // m_bButton.WhenPressed(m_pupClimbCmd);
 // m_bButton.WhenHeld(m_ploadToPhotoCmd);
 // m_bButton.WhenReleased(m_pStopShoot);
}

void RobotContainer::SetButtonX()
{
  m_xButton.WhenPressed(m_pShoot);
//  m_xButton.WhenHeld(m_pdownAutoArmCmd);
 // m_xButton.WhenHeld(m_ploadToPhotoCmd);
 // m_xButton.WhenPressed(m_pdownClimbCmd);
 // m_xButton.WhenHeld(m_pShootSpeed);
  //m_xButton.WhenReleased(m_pStopShoot);
}

void RobotContainer::SetRightTrigger()
{
}

void RobotContainer::SetLeftTrigger()
{
}

void RobotContainer::SetRightBumper()
{

}

void RobotContainer::SetLeftBumper()
{
  m_leftBumper.WhenHeld(m_ploadToPhotoCmd);
}


void RobotContainer::SetButtonY()
{
m_yButton.WhenPressed(m_ploader);
}

void RobotContainer::SetButtonA()
{
  //Load, Because the loader is near the drive train on the bottom.
  // m_aButton.WhenHeld(m_pShoot);
  // m_aButton.WhenReleased(m_pStopShoot);
  m_aButton.WhenPressed(m_pVisionShootCmd);
}

void RobotContainer::ClimbEncoder()
{
  m_ClimbSub.EncoderTest();
}

void RobotContainer::RunDrive()
{
  // RUN DRIVE
  m_driveTrainSub .SetDefaultCommand(*m_pdriveCmd);
}

int RobotContainer::GetDPDT()
{
  // bool isTop = !m_topSwitch.Get();
  // bool isBottom = !m_bottomSwitch.Get();
  bool isTop = false;
  bool isBottom = false;
  frc::SmartDashboard::PutBoolean("TopSwitch", isTop);
  frc::SmartDashboard::PutBoolean("BottomSwitch", isBottom);
  
  int value = -1;
  if(isTop)
  {
    value = 1;
  }
  else if(isBottom)
  {
    value = 2;
  }
  else
  {
    value = 3;
  }

  frc::SmartDashboard::PutNumber("DPDT Value", value);
  return value;
}

void RobotContainer::EncoderValues()
{
  double disLeft, disRight;
  int rawLeft, rawRight;
  m_driveTrainSub .GetEncoderDistance(&disLeft, &disRight);
  m_driveTrainSub .GetEncoderRaw(&rawLeft, &rawRight);
  units::degree_t angle = m_driveTrainSub .GetADIAngle();

  frc::SmartDashboard::PutNumber("Left E Dis", disLeft);
  frc::SmartDashboard::PutNumber("Right E Dis", disRight);
  frc::SmartDashboard::PutNumber("Left E Raw", rawLeft);
  frc::SmartDashboard::PutNumber("Right E Raw", rawRight);

  m_shootSub.GetShootDistance();

  frc::SmartDashboard::PutNumber("ADI Angle", (double)angle);
}

frc2::Command* RobotContainer::GetAutonomousCommand() 
{
  frc2::Command* cmd = nullptr;
  frc::SmartDashboard::PutBoolean("Auto Status", true);
#pragma region
  switch (GetDPDT())
  {
  default:
    cmd = m_pLonely;
    break;
    
  //case 2:
   // cmd = m_pPos2AutoCmd;
   // break;

 // case 3:
  //  cmd = m_pPos3AutoCmd;
  //  break;

 // default:
  //  cmd = nullptr;
   // break;
  }
#pragma endregion
  if(cmd == nullptr)
  {
    frc::SmartDashboard::PutBoolean("Auto Status", false);
  }
  return cmd;
}
