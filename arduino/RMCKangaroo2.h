#pragma once
#include <SoftwareSerial.h>
#include <Kangaroo.h>
#include <PID_v1.h>

#define DEFAULT_NUMBER_OF_CHANNEL 10
#define FRONT_LEFT 1  //channel 4
#define REAR_LEFT 2 //channel 5
#define FRONT_RIGHT 0 //channel 3
#define REAR_RIGHT 3 //channel 6

/*!
\class Actuator
\brief This parent class ensures Linear Actuator and motor class inherits the general functions.
*/
class Actuator
{
public:
	void begin();
	void loop();
	void setTargetVal(long val);
	void setTargetVal(long val1, long val2); //For controlling 2 Kangaroo Channels
	long *getCurrentVal();
private:

};

/*!
\class LinearActuator
\Inherits KangarooChannel and Actuator
\brief  This class controls a single Linear Actuator
*/
class LinearActuator : public KangarooChannel, public Actuator {
public:

	LinearActuator(KangarooSerial& K, char name);
	long min;
	long max;
	long maxSpeed;
	long speed;
	long lastSpeed;
	long targetVal;
	long lastVal;
	long getCurrentVal();
	bool done = false;
//	void setSpeed(long speed);
	void getExtremes();
	void setTargetPosDirect(long pos);
	void setTargetVal(long pos, long newSpeed);
	void setSpeed(long newSpeed);
	void setTargetPos(long pos );
	void loop();
	KangarooStatus status;
	void begin();
};

/*!
\class LinearActuatorPair
\brief  This class controls two Linear Actuator synchronously.
*/
class LinearActuatorPair{
public:
	LinearActuatorPair(KangarooSerial& K, char name);
	LinearActuator* channel[2];
	long targetVal;
	long lastVal;
	long lastSpeed;
	bool isSyncing;
	long *getCurrentVal();
	//void setTargetVal(long pos, long newSpeed);
	void setSpeed(long newSpeed);
	void setTargetPos(long pos);
	void loop();
	void begin();
	long speed;
	//Define Variables we'll be connecting to
	double Setpoint, Input, Output;

	//Specify the links and initial tuning parameters
	double Kp = 0.4, Ki = 0, Kd = 0;
	PID* syncPID;

};

class Motor : public KangarooChannel, public Actuator {
public:

	Motor(KangarooSerial& K, char name);
	long speedLimit;
	long lastSpeed = 1;
	long speed = 0;
	long getCurrentSpeed();
	void setSpeedLimit(long speed);
	//void moveAtSpeed(long val, long newSpeed);
	void setTargetVal(long val);
	void move(long val);
	void loop();
	void setTargetSpeed(long val);
	//void setTargetVal(long val, long distance);
	KangarooStatus status;
	void begin();
};

class Motors{
public:
	long drive = 101;
	long turn = 101;
	Motor *channel[4];
	Motors(KangarooSerial & K, char name);
	long setTargetVal(long drive, long turn);
	void setDrive(long drive);
	void setTurn(long turn);
	void loop();
	void begin();
	//Define Variables we'll be connecting to
	double Setpoint, Input, Output;

	//Specify the links and initial tuning parameters
	double Kp = 0, Ki = 0, Kd = 0;
	PID* syncPID;
};

/*!
\class RMCKangaroo1
\brief  This the main class for Kangaroo X2 Motion Controller
*/
class RMCKangaroo1
{
protected:
	int channelIndex[DEFAULT_NUMBER_OF_CHANNEL];
	Motors* channel[DEFAULT_NUMBER_OF_CHANNEL];
	SoftwareSerial* SerialPort;
	KangarooSerial* K;
	String channelList;
	String channelType;

public:

	RMCKangaroo1(int rxPin, int txPin, String channelList, String channelType);
	void loop();
	void begin();
	void setTargetVal(int channelName, long val);
	void setTargetVal1(int channelName, long val);
	KangarooStatus status[DEFAULT_NUMBER_OF_CHANNEL];
};
