// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

//#define NOHW

//PWM
constexpr int PWM_LEFT                  = 0;
constexpr int PWM_RIGHT                 = 1;
constexpr int PWM_ARM_SERVO             = 2; // May be a motor
constexpr int PWM_LOADER_INTAKE         = 3;
constexpr int PWM_LOADER_INNER          = 4; 
constexpr int PWM_SHOOTER               = 5;
constexpr int PWM_CLIMB_BACK            = 6;
constexpr int PWM_CLIMB_FRONT           = 7;
constexpr int PWM_TURRET                = 8;

//DIO
constexpr int DIO_DRIVE_LEFT_A          = 0;
constexpr int DIO_DRIVE_LEFT_B          = 1;
constexpr int DIO_DRIVE_RIGHT_A         = 2;
constexpr int DIO_DRIVE_RIGHT_B         = 3;
constexpr int DIO_SHOOTER_ENCODER_A     = 4;
constexpr int DIO_SHOOTER_ENCODER_B     = 5;
constexpr int DIO_CLIMBFRONT_ENCODER_A  = 6;
constexpr int DIO_CLIMBFRONT_ENCODER_B  = 7;
constexpr int DIO_CLIMBBACK_ENCODER_A   = 8;
constexpr int DIO_CLIMBBACK_ENCODER_B   = 9;

constexpr int USB_CONTROLLER_ONE        = 0;
constexpr int USB_CONTROLLER_TWO        = 1;

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */
