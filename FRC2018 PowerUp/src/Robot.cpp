#include <iostream>
#include <string>
#include <WPIlib.h>
#include <ctre/Phoenix.h>

Joystick *stick;

WPI_TalonSRX *lFrontMotor;
WPI_TalonSRX *lBackMotor;
WPI_TalonSRX *rFrontMotor;
WPI_TalonSRX *rBackMotor;

TalonSRX *rElevator;
TalonSRX *lElevator;

//RobotDrive *drive;
DifferentialDrive *drive;


class Robot : public frc::IterativeRobot {
public:
	void RobotInit() {
		stick = new Joystick(0);

		lFrontMotor = new WPI_TalonSRX(4);
		//lFrontMotor->SetSafetyEnabled(false);
		//lFrontMotor->Set(ControlMode::PercentOutput, 0.0);
		//lFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
		//lFrontMotor->SetSensorPhase(true);

		lBackMotor = new WPI_TalonSRX(3);
		//lBackMotor->SetSafetyEnabled(false);
		//lBackMotor->Set(ControlMode::PercentOutput, 0.0);
		lBackMotor->Set(ControlMode::Follower, 4);
		//lBackMotor->SetInverted(true);

		rFrontMotor = new WPI_TalonSRX(2);
		//rFrontMotor->SetSafetyEnabled(false);
		//rFrontMotor->Set(ControlMode::PercentOutput, 0.0);
		//rFrontMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);

		rBackMotor = new WPI_TalonSRX(1);
		//rBackMotor->SetSafetyEnabled(false);
		//rBackMotor->Set(ControlMode::PercentOutput, 0.0);
		rBackMotor->Set(ControlMode::Follower, 2);
		//rBackMotor->SetInverted(true);

		//drive = new RobotDrive(lFrontMotor, lBackMotor, rFrontMotor, rBackMotor);
		//drive = new RobotDrive(lFrontMotor, rFrontMotor);
		drive = new DifferentialDrive(*lFrontMotor, *rFrontMotor);

		lElevator = new TalonSRX(5);
		//lElevator->Set(ControlMode::PercentOutput, 0.0);

		rElevator = new TalonSRX(6);
	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {}

	void TeleopPeriodic() {

		//drive->TankDrive(stick->GetRawAxis(1), stick->GetRawAxis(4));
		drive->ArcadeDrive(stick->GetRawAxis(4), -stick->GetRawAxis(1));

		if(stick->GetRawButton(4)){
			lElevator->Set(ControlMode::PercentOutput, 0.25);
			rElevator->Set(ControlMode::PercentOutput, -0.25);
		}
		else if(stick->GetRawButton(1)){
			lElevator->Set(ControlMode::PercentOutput, -0.25);
			rElevator->Set(ControlMode::PercentOutput, 0.25);
		}
		else{
			lElevator->Set(ControlMode::PercentOutput, 0.0);
			rElevator->Set(ControlMode::PercentOutput, 0.0);
		}
	}

	void TestPeriodic() {}

private:
};

START_ROBOT_CLASS(Robot)
