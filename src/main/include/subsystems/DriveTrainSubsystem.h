// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/Encoder.h>
#include <frc/ADIS16448_IMU.h>

#include "../Constants.h"

class DriveTrainSubsystem : public frc2::SubsystemBase {
 public:
  DriveTrainSubsystem();

  enum DriveStyles
  {
    TANK_STYLE, 
    ARCADE_STYLE, 
    RC_STYLE
  };

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  // Motors
  void SetMotorL(double speed);
  void SetMotorR(double speed);
  //Encoders
  // void ResetEncoders();
  // void GetEncoderDistance(double* pLeft, double* pRight);
  // void GetEncoderRaw(int* pLeft, int* pRight);

  // Drive functions
  void MoveTank(double left, double right);
  void MoveArcade(double X, double Y);

  // Drive styles
  void SetDrive(DriveStyles style);
  DriveStyles GetDrive();

 private:
 #ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFT};
  frc::Spark m_rightMotor{PWM_RIGHT};

  // frc::Encoder m_leftEncoder{DIO_DRIVE_LEFT_A, DIO_DRIVE_LEFT_B};
  // frc::Encoder m_rightEncoder{DIO_DRIVE_RIGHT_A, DIO_DRIVE_RIGHT_B};

  //frc::ADIS16448_IMU m_imu;
 #endif
  DriveStyles m_currentStyle;

  double m_pulseDisLeft = 5;
  double m_pulseDisRight = 5;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
