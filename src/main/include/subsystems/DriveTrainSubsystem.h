// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/Encoder.h>
#include <frc/ADIS16448_IMU.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "../Constants.h"

#include <frc/DigitalInput.h>

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

  void Init();

  // Motors
  void SetMotorL(double speed);
  void SetMotorR(double speed);

  //Encoders
  void ResetEncoders();
  void GetEncoderDistance(double* pLeft = nullptr, double* pRight = nullptr);
  void GetEncoderRaw(int* pLeft, int* pRight);

  // Drive functions
  void MoveTank(double left, double right);
  void MoveArcade(double X, double Y);

  // Drive styles
  void SetDrive(DriveStyles style);
  DriveStyles GetDrive();

  // IMU Functions
  units::degree_t GetADIAngle();
  units::degree_t GetAngleX();
  units::degree_t GetAngleY();
  units::degree_t GetAngleZ();

  // IMU and Drive Functions
  void TurnAngleRelative(units::degree_t angle, double speed = 0.5, units::degree_t deadZone = 1_deg);
  void TurnAngleAbsolute(units::degree_t angle, double speed = 0.5, units::degree_t deadZone = 1_deg);

  // Encoder and Drive Functions
  void ForwardInInch(double inch, double speed = 0.5);
  void ForwardInInchIMU(double inch, double correctionSpeed = 0.1, units::degree_t deadZoneAngle = 1.0_deg, double speed = 0.5);

 private:
 #ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFT};
  frc::Spark m_rightMotor{PWM_RIGHT};

  frc::Encoder m_leftEncoder{DIO_DRIVE_LEFT_A, DIO_DRIVE_LEFT_B};
  frc::Encoder m_rightEncoder{DIO_DRIVE_RIGHT_A, DIO_DRIVE_RIGHT_B};

  frc::ADIS16448_IMU m_adi;

 #endif
  DriveStyles m_currentStyle;

  //ROCKY - (3.14 * 8) / -2485
  //Equation: circumfrence (pi*d) / pulses_per_revolution (have to test)
  double m_pulseDisLeft = (3.14 * 8) / 2485;
  double m_pulseDisRight = (3.14 * 8) / 2485;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
