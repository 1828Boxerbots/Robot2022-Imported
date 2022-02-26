               //                         |                           \\  
              //                                                       \\  
             //                           |                             \\  
            //                                                           \\  
           //                             |                               \\  
          //                                                               \\  
         //                               |                                 \\  
        //                                                                   \\  
       //                                 |                                   \\  
      //                                                                       \\  
     // Copyright (c) FIRST and other WPILib contributors.                      \\  
    //                                    |                                      \\  
   //  Open Source Software; you can modify and/or share it under the terms of    \\  
  //                                      |                                        \\  
 //   the WPILib BSD license file in the root directory of this project.            \\  
//                                        |                                          \\  

#include "subsystems/ShooterSubsystem.h"

ShooterSubsystem::ShooterSubsystem(){}

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {}

void ShooterSubsystem::Init()
{
#ifndef NOHW
    m_shooterEncoder.SetDistancePerPulse(m_DISPULSE_SHOOT);
#endif
    ResetEncoder();
}

// ENCODER FUNCTIONS
void ShooterSubsystem::ResetEncoder()
{
#ifndef NOHW
    m_shooterEncoder.Reset();
#endif
}

double ShooterSubsystem::GetShooterSpeed()
{
#ifndef NOHW
    //Units are distance PER SECOND as scaled by SetDistancePerPulse()
    frc::SmartDashboard::PutNumber("ShooterSpeed", m_shooterEncoder.GetRate());
    return m_shooterEncoder.GetRate();
#endif
}

double ShooterSubsystem::GetShootDistance()
{
#ifndef NOHW
    frc::SmartDashboard::PutNumber("ShooterDistance", m_shooterEncoder.GetDistance());
    return m_shooterEncoder.GetDistance();
#endif
}

void ShooterSubsystem::SetShooterSpeed(double targetSpeed)
{
    //Using a linear function speed= (78)power + 0 (found testing different powers and graphing their speeds)
    // y=mx+b -> x= (y+b)/m
    double power = targetSpeed / 78;

    ShootMotor(-power);
    while(GetShooterSpeed() < targetSpeed)
    {
        GetShooterSpeed();
    }
}

int ShooterSubsystem::GetEncoderRaw()
{
#ifndef NOHW
    frc::SmartDashboard::PutNumber("ShooterRaw", m_shooterEncoder.GetRaw());
    return m_shooterEncoder.GetRaw();
#endif
}

// SHOOTER FUNCTIONS
void ShooterSubsystem::ShootMotor(double speed)
{
#ifndef NOHW
    m_shooterMotor.Set(speed);
#endif
}