// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include "RobotContainer.h"

RobotContainer::RobotContainer() 
{
  // Initialize all of your commands and subsystems here
  m_pdriveCmd = new DriveCommand(&m_driveTrainSub, &m_controllerOne, DriveTrainSubsystem::RC_STYLE);
  m_ploader = new LoadInOne(&m_loaderSub,0.5,&m_controllerTwo);
  m_pLoadStop= new LoadInOne(&m_loaderSub,0,&m_controllerTwo);
  m_peject = new LoadInOne(&m_loaderSub,1,&m_controllerTwo);
  m_ploadInnerCmd = new LoadInnerCommand(&m_loaderSub, &m_controllerTwo,-.5);
  m_ploadIntakeCmd = new LoadIntakeCommand(&m_loaderSub, &m_controllerTwo, 1.0);
  m_ploadToPhotoCmd = new LoadToPhotoCommand(&m_loaderSub, 0.2);
  m_ploadToShooterCmd = new LoadToShooterCommand(&m_loaderSub, 0.2);
  m_pstopIntakeCmd = new LoadIntakeCommand(&m_loaderSub, &m_controllerTwo, 0.0);
  m_pstopInnerCmd = new LoadInnerCommand(&m_loaderSub, &m_controllerTwo, 0.0);
  m_pLonelyTimer = new TheLoneTimerAutonomus(&m_driveTrainSub,&m_loaderSub,&m_shootSub, 0.6,170.0);
  m_pMiddleTimer = new TheLoneTimerAutonomus(&m_driveTrainSub, &m_loaderSub, &m_shootSub, 0.6,-135.0);
  m_pupAutoArmCmd = new AutoArmCommand(&m_loaderSub, 0.25);
  m_pdownAutoArmCmd = new AutoArmCommand(&m_loaderSub, -0.25);
  m_pUpClimbCmd = new ClimbCommand(&m_ClimbSub,25,0.4);
  m_pDownClimbCmd = new ClimbCommand (&m_ClimbSub,-25,0.4);
  m_pShootSpeed = new ShootSpeedCommand(&m_shootSub, &m_loaderSub, 1600);
  m_pShoot = new ShooterCommand(&m_shootSub, &m_controllerTwo, 0.39);
  m_pLowShoot = new ShooterCommand(&m_shootSub, &m_controllerTwo, 0.2);
  m_pShootStop = new ShooterCommand(&m_shootSub, &m_controllerTwo, 0.0);
  m_pShootTrigger = new ShootTriggerController(&m_shootSub, &m_controllerTwo);
  m_pStopShoot = new ShooterCommand(&m_shootSub, &m_controllerTwo, 0.0);
  m_pVisionAllignCmd = new VisionAllignCommand(&m_driveTrainSub, &m_loaderSub, &m_shootSub);
  m_pArmDown = new ArmCommand(&m_loaderSub,0.65,&m_controllerTwo);
  m_pArmStop = new ArmCommand(&m_loaderSub,0,&m_controllerTwo);

  //Auto
  m_pAloneAutoCmd = new Pos1AutoCommand(&m_driveTrainSub, &m_loaderSub, &m_shootSub, 180.0);
  m_pMiddleAutoCmd = new Pos1AutoCommand(&m_driveTrainSub, &m_loaderSub, &m_shootSub, -135.0);
  m_pWallAutoCmd = new PosWallAutoCommand(&m_loaderSub, &m_shootSub, &m_driveTrainSub, 155.0, 70.0);
  m_plowHub = new CompetitionCMD(&m_driveTrainSub, &m_shootSub, &m_loaderSub, 0.3, 0.6, 1.2);

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

void RobotContainer::TeleopPeriodic()
{
  EncoderValues();
  m_ClimbSub.PeriodicRatchet();

  m_ClimbSub.ClimbDistance(25, -m_controllerTwo.GetLeftY(), m_controllerTwo.GetLeftX(), 0.5);
  //m_ClimbSub.ClimbMotor(m_controllerTwo.GetLeftX() * 0.5);
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

  SetDpadUp();
  SetDpadDown();
  SetDpadLeft();
  SetDpadRight();
}

void RobotContainer::SetButtonB()
{ 
  m_bButton.WhileHeld(m_ploadInnerCmd);
  m_bButton.WhenReleased(m_pLoadStop);
  m_bButton2.WhileHeld(m_ploadInnerCmd);
  m_bButton2.WhenReleased(m_pLoadStop);
}

void RobotContainer::SetButtonX()
{
  m_xButton.WhenPressed(m_pVisionAllignCmd);
  //m_xButton.WhenPressed(m_p8ftShoot);
  m_xButton2.WhileHeld(m_pArmDown);
  m_xButton2.WhenReleased(m_pArmStop);
}

void RobotContainer::SetButtonY()
{
  m_yButton.WhenHeld(m_ploader);
  m_yButton.WhenReleased(m_pLoadStop);
  m_yButton2.WhileHeld(m_ploader);      
  m_yButton2.WhenReleased(m_pLoadStop);
}

void RobotContainer::SetButtonA()
{
  m_aButton.WhenHeld(m_ploadIntakeCmd);
  m_aButton.WhenReleased(m_pLoadStop);
  m_aButton2.WhileHeld(m_ploadIntakeCmd);
  m_aButton2.WhenReleased(m_pLoadStop);
}

void RobotContainer::SetDpadUp()
{
  m_POVup.WhenHeld(m_ploader);
  m_POVup.WhenReleased(m_pLoadStop);
}
void RobotContainer::SetDpadDown()
{
  m_POVdown.WhenHeld(m_ploadIntakeCmd);
  m_POVdown.WhenReleased(m_pLoadStop);
}
void RobotContainer::SetDpadLeft()
{
  m_POVleft.WhenHeld(m_ploadInnerCmd);
  m_POVleft.WhenReleased(m_pLoadStop);
}
void RobotContainer::SetDpadRight()
{
  m_POVright.WhenHeld(m_pShoot);
  m_POVright.WhenReleased(m_pShootStop);
}

void RobotContainer::SetRightBumper()
{
  // m_rightBumper2.WhenHeld(m_pShoot);
  // m_rightBumper2.WhenReleased(m_pStopShoot);
}

void RobotContainer::SetLeftBumper()
{

}

void RobotContainer::SetRightTrigger()
{
  m_rightTrigger.WhenHeld(m_pShoot);
  m_rightTrigger.WhenReleased(m_pStopShoot);
  m_rightTrigger2.WhenHeld(m_pShoot);
  m_rightTrigger2.WhenReleased(m_pStopShoot);
}

void RobotContainer::SetLeftTrigger()
{
  m_leftTrigger2.WhenHeld(m_pLowShoot);
  m_leftTrigger2.WhenReleased(m_pStopShoot);
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
  bool isTop = !m_topSwitch.Get();
  bool isBottom = !m_bottomSwitch.Get();
  // bool isTop = false;
  // bool isBottom = false;
  frc::SmartDashboard::PutBoolean("TopSwitch", isTop);
  frc::SmartDashboard::PutBoolean("BottomSwitch", isBottom);
  
  int value = -1;
  if(isTop)
  {
    value = 3;
  }
  else if(isBottom)
  {
    value = 1;
  }
  else
  {
    value = 2;
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

  frc::SmartDashboard::PutNumber("EncoderValues-Left E Dis", disLeft);
  frc::SmartDashboard::PutNumber("EncoderValues-Right E Dis", disRight);
  frc::SmartDashboard::PutNumber("EncoderValues-Left E Raw", rawLeft);
  frc::SmartDashboard::PutNumber("EncoderValues-Right E Raw", rawRight);

  m_shootSub.GetShootDistance();
  m_shootSub.GetShooterSpeed();
  
  frc::SmartDashboard::PutNumber("ADI Angle", (double)angle);
  frc::SmartDashboard::PutNumber("ADI X", (double)m_driveTrainSub.GetAngleX());
  frc::SmartDashboard::PutNumber("ADI Y", (double)m_driveTrainSub.GetAngleY());
  frc::SmartDashboard::PutNumber("ADI Z", (double)m_driveTrainSub.GetAngleZ());
}

frc2::Command* RobotContainer::GetAutonomousCommand() 
{
  frc2::Command* cmd = nullptr;
  frc::SmartDashboard::PutBoolean("Auto Status", true);
  switch (GetDPDT())
  {
    case 1:
      //For Pos 1 AND 2
      cmd = m_pAloneAutoCmd;
      frc::SmartDashboard::PutString("AutoCMD String", "m_pAloneAutoCmd");
      break;
      
    case 2:
      //When facing toward wall
      cmd = m_pWallAutoCmd;
      frc::SmartDashboard::PutString("AutoCMD String", "m_pWallAutoCmd");
      break;

    case 3:
      //AZ North Auto
      cmd = m_plowHub;
      frc::SmartDashboard::PutString("AutoCMD String", "m_plowHub");
      break;

    default:
      cmd = nullptr;
  }


  if(cmd == nullptr)
  {
    frc::SmartDashboard::PutBoolean("Auto Status", false);
    frc::SmartDashboard::PutString("AutoCMD String", "nullptr");
  }

  return nullptr;
}
