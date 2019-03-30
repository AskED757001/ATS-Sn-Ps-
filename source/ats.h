#pragma once
void SnInit(int);
void SnStart(void);
void SnRun(void);
void SnBeacon(int, int, int);
void SnButton(int);
void PsInit(int);
void PsRun(double);
double PsPatternSig(double, int, double);
double PsPattern(double, int, double);
bool PsWarning(double, double, int, int, double, int);
int PsLimit(double, int);
int SetPsPitch(double);
int SetPs2distance(int);
void PsBeacon(int, int, int);
void EBInit(int);
void EBStart(void);
void EBReset(void);
void RunEB(int, double);

int BrakeNotch;
int PowerNotch;
int Reverser;
int time;
int deltaT;
int emgBrake;
double speed;
int ATSNotch;
bool pilotlamp;

ATSIni g_ini;

class ATSPs
{
public:
	double Basedecelerate = 2.6;
	double deceleratePa;
	double deceleratePb;
	double Pa1;
	double Pa2;
	double Pb1;
	double Pb2;
	double P3;
	double Point1;
	double Point2;
	double Curve1;
	double Curve2;
	double Pitch1;
	double Pitch2;
	double Rinji1;
	double Rinji2;
	int Irekae;
	int Yudo;
	int Point1Speed;
	int Point2Speed;
	int Curve1Speed;
	int Curve2Speed;
	int Pitch1Speed;
	int Pitch2Speed;
	int Rinji1Speed;
	int Rinji2Speed;
	double PatternSpeed;
	int PitchPa;
	int PitchPb;
	bool WarningLamp;
	bool BrakeLamp;
	bool PatternLamp;
	bool PowerLamp;
	bool PsLamp;
	bool PsCut;
	int BrakeSound;
	int PatternStart;
	int PatternEnd;
	int Warning;
	double PsM;
	double Ps2;
	double Ps_2;
	double Ps2_;
	bool PbM2;
	int PsMFrq;
	int PsSpeed;
	int PatternData[4][8] = { {35,45,50,55,60,65,70},{50,60,70,80,90,100,110},{45,55,65,75,85,95,105},{35,40,45,50,55,60,65} };
	int PEnabled;
};
ATSPs Ps;

class ATSSn
{
public:
	bool ATSPower;
	bool ATSRed;
	bool ATSBrake;
	bool ATSChime;
	bool ATSWhite;
	bool Space;
	int LongTimer;
	int PsTimer;
	int SpeedTimer0;
	int SpeedTimer1;
	int SpeedTimer2;
	int SpeedTimer3;
	int SpeedTimer4;
	int bell;
	int chime;
	int chimeR;
	int chimeL;
	int chimeX;
	int bellstop;
	bool chimeLR;
};
ATSSn Sn;
class ATSEB
{
public:
	bool EBPower;
	bool EBLamp;
	int EBTimer;
	bool EBBrake;
	int EBSound;
};
ATSEB EB;