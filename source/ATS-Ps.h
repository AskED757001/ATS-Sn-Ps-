#include <math.h>

void PsInit(int param)
{
	Ps.BrakeLamp = false;
	Ps.PsCut = false;
	Sn.PsTimer = 0;
	Ps.PsM = 0;
	Ps.PsMFrq = 0;
	Ps.Ps2 = 0;
	Ps.Ps_2 = 0;
	Ps.Pa1 = 0;
	Ps.Pa2 = 0;
	Ps.Pb1 = 0;
	Ps.Pb2 = 0;
	Ps.P3 = 0;
	Ps.Point1 = 0;
	Ps.Point2 = 0;
	Ps.Point1Speed = 0;
	Ps.Point2Speed = 0;
	Ps.Curve1 = 0;
	Ps.Curve2 = 0;
	Ps.Curve1Speed = 0;
	Ps.Curve2Speed = 0;
	Ps.Pitch1 = 0;
	Ps.Pitch2 = 0;
	Ps.Pitch1Speed = 0;
	Ps.Pitch2Speed = 0;
	Ps.Rinji1 = 0;
	Ps.Rinji2 = 0;
	Ps.Rinji1Speed = 0;
	Ps.Rinji2Speed = 0;
	Ps.Irekae = 0;
	Ps.Yudo = 0;
	Ps.PitchPa = 0;
	Ps.PitchPb = 0;
	if (param == 0)
		Ps.PowerLamp = false;
	else
		Ps.PowerLamp = true;
	Ps.PsLamp = Ps.PowerLamp;
}
void PsRun(double deltaL)
{
	Ps.deceleratePa = Ps.Basedecelerate - (abs(Ps.PitchPa)*9.8 / 1000 * 3600 / 1000);
	Ps.deceleratePb = Ps.Basedecelerate - (abs(Ps.PitchPb)*9.8 / 1000 * 3600 / 1000);
	if (Ps.Pa1 != 0)
		Ps.Pa1 -= deltaL;
	if (Ps.Pa2 > 0)
		Ps.Pa2 -= deltaL;
	else
		Ps.Pa2 = 0;
	if (Ps.Pb1 != 0)
		Ps.Pb1 -= deltaL;
	if (Ps.Pb2 > 0)
		Ps.Pb2 -= deltaL;
	else
		Ps.Pb2 = 0;
	if (Ps.P3 > 0)
		Ps.P3 -= deltaL;
	else
		Ps.P3 = 0;
	if (Ps.Point1 != 0 && Ps.Point1 > -50)
		Ps.Point1 -= deltaL;
	else
		Ps.Point1 = 0;
	if (Ps.Point2 != 0 && Ps.Point2 > -50)
		Ps.Point2 -= deltaL;
	else
		Ps.Point2 = 0;
	if (Ps.Curve1 != 0)
		Ps.Curve1 -= deltaL;
	if (Ps.Curve2 != 0)
		Ps.Curve2 -= deltaL;
	if (Ps.Pitch1 != 0)
		Ps.Pitch1 -= deltaL;
	if (Ps.Pitch2 != 0)
		Ps.Pitch2 -= deltaL;
	if (Ps.Rinji1 != 0)
		Ps.Rinji1 -= deltaL;
	if (Ps.Rinji2 != 0)
		Ps.Rinji2 -= deltaL;

	Ps.PsM -= deltaL;
	if(Ps.Ps2 > 0)
	Ps.Ps2 -= deltaL;
	else
		Ps.Ps2 = 0;
	if (Ps.Ps_2 > 0)
		Ps.Ps_2 -= deltaL;
	else
		Ps.Ps_2 = 0;
	if (Ps.Ps2_ > 0)
		Ps.Ps2_ -= deltaL;
	else
		Ps.Ps2_ = 0;

	Ps.PatternSpeed = Ps.PsSpeed + Ps.PEnabled * 1000 * g_ini.DATA.PPrimary;
	if (Ps.PatternSpeed > PsPatternSig(Ps.Pa1, g_ini.DATA.Speedmeter, Ps.Basedecelerate) && Ps.Pa1 != 0)
		Ps.PatternSpeed = PsPatternSig(Ps.Pa1, g_ini.DATA.Speedmeter, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPatternSig(Ps.Pa2, 10, Ps.deceleratePa) && Ps.Pa2 != 0)
		Ps.PatternSpeed = PsPatternSig(Ps.Pa2, 10, Ps.deceleratePa);

	if (Ps.PatternSpeed > PsPatternSig(Ps.Pb1, g_ini.DATA.Speedmeter, Ps.Basedecelerate) && Ps.Pb1 != 0)
		Ps.PatternSpeed = PsPatternSig(Ps.Pb1, g_ini.DATA.Speedmeter, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPatternSig(Ps.Pb2, 10, Ps.deceleratePb) && Ps.Pb2 != 0)
		Ps.PatternSpeed = PsPatternSig(Ps.Pb2, 10, Ps.deceleratePb);

	if (Ps.PatternSpeed > 15 && Ps.P3 != 0)
		Ps.PatternSpeed = 15;

	if (Ps.PatternSpeed > PsPattern(Ps.Point1, Ps.Point1Speed, Ps.Basedecelerate) && Ps.Point1 != 0)
		Ps.PatternSpeed = PsPattern(Ps.Point1, Ps.Point1Speed, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPattern(Ps.Point2, Ps.Point2Speed, Ps.Basedecelerate) && Ps.Point2 != 0)
		Ps.PatternSpeed = PsPattern(Ps.Point2, Ps.Point2Speed, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPattern(Ps.Curve1, Ps.Curve1Speed, Ps.Basedecelerate) && Ps.Curve1 != 0)
		Ps.PatternSpeed = PsPattern(Ps.Curve1, Ps.Curve1Speed, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPattern(Ps.Curve2, Ps.Curve2Speed, Ps.Basedecelerate) && Ps.Curve2 != 0)
		Ps.PatternSpeed = PsPattern(Ps.Curve2, Ps.Curve2Speed, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPattern(Ps.Pitch1, Ps.Pitch1Speed, Ps.Basedecelerate) && Ps.Pitch1 != 0)
		Ps.PatternSpeed = PsPattern(Ps.Pitch1, Ps.Pitch1Speed, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPattern(Ps.Pitch1, Ps.Pitch2Speed, Ps.Basedecelerate) && Ps.Pitch2 != 0)
		Ps.PatternSpeed = PsPattern(Ps.Pitch1, Ps.Pitch2Speed, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPattern(Ps.Pitch1, Ps.Rinji1Speed, Ps.Basedecelerate) && Ps.Rinji1 != 0)
		Ps.PatternSpeed = PsPattern(Ps.Pitch1, Ps.Rinji1Speed, Ps.Basedecelerate);

	if (Ps.PatternSpeed > PsPattern(Ps.Pitch1, Ps.Rinji2Speed, Ps.Basedecelerate) && Ps.Rinji2 != 0)
		Ps.PatternSpeed = PsPattern(Ps.Pitch1, Ps.Rinji2Speed, Ps.Basedecelerate);

	if (Ps.PatternSpeed > Ps.Irekae && Ps.Irekae != 0)
		Ps.PatternSpeed = Ps.Irekae;

	if (Ps.PatternSpeed > Ps.Yudo && Ps.Yudo != 0)
		Ps.PatternSpeed = Ps.Yudo;

	
	if (
		speed > g_ini.DATA.PsMaxspeed - 5 + Ps.PEnabled * 1000 * g_ini.DATA.PPrimary && Ps.PsLamp
		|| Ps.P3 != 0 && speed > 10 && Ps.PsLamp || Ps.Irekae != 0 && speed > Ps.Irekae - 5 && Ps.PsLamp || Ps.Yudo != 0 && speed > Ps.Yudo - 5 && Ps.PsLamp
		|| PsWarning(Ps.Pa1, speed, 0, g_ini.DATA.Speedmeter - 5, Ps.Basedecelerate, g_ini.DATA.Margin)
		|| PsWarning(Ps.Pb1, speed, 0, g_ini.DATA.Speedmeter - 5, Ps.Basedecelerate, g_ini.DATA.Margin)
		|| PsWarning(Ps.Pa2, speed, 0, 5, Ps.deceleratePa, g_ini.DATA.Margin)
		|| PsWarning(Ps.Pb2, speed, 0, 5, Ps.deceleratePb, g_ini.DATA.Margin)
		|| PsWarning(Ps.Point1, speed, Ps.Point1Speed, Ps.Point1Speed - 5, Ps.Basedecelerate, 0)
		|| PsWarning(Ps.Point2, speed, Ps.Point2Speed, Ps.Point2Speed - 5, Ps.Basedecelerate, 0)
		|| PsWarning(Ps.Curve1, speed, Ps.Curve1Speed, Ps.Curve1Speed - 5, Ps.Basedecelerate, 0)
		|| PsWarning(Ps.Curve2, speed, Ps.Curve2Speed, Ps.Curve2Speed - 5, Ps.Basedecelerate, 0)
		|| PsWarning(Ps.Pitch1, speed, Ps.Pitch1Speed, Ps.Pitch1Speed - 5, Ps.Basedecelerate, 0)
		|| PsWarning(Ps.Pitch2, speed, Ps.Pitch2Speed, Ps.Pitch2Speed - 5, Ps.Basedecelerate, 0)
		|| PsWarning(Ps.Rinji1, speed, Ps.Rinji1Speed, Ps.Rinji1Speed - 5, Ps.Basedecelerate, 0)
		|| PsWarning(Ps.Rinji2, speed, Ps.Rinji2Speed, Ps.Rinji2Speed - 5, Ps.Basedecelerate, 0)
		)
	{
		if (!Ps.WarningLamp)
			Ps.Warning = ATS_SOUND_PLAY;
		else
			Ps.Warning = ATS_SOUND_CONTINUE;
		Ps.WarningLamp = true;
	}
	else
	{
		if (Ps.WarningLamp)
			Ps.Warning = ATS_SOUND_PLAY;
		else
			Ps.Warning = ATS_SOUND_CONTINUE;
		Ps.WarningLamp = false;
	}

	if (Ps.PatternSpeed < speed && Ps.PsLamp)
	{
		if (!Ps.BrakeLamp)
			Ps.BrakeSound = ATS_SOUND_PLAY;
		else
			Ps.BrakeSound = ATS_SOUND_CONTINUE;
		Ps.BrakeLamp = true;
	}
	if (Ps.Pa1 != 0 || Ps.Pa2 != 0 || Ps.Pb1 != 0 || Ps.Pb2 != 0 || Ps.P3 != 0
		|| Ps.Point1 != 0 || Ps.Point2 != 0 || Ps.Curve1 != 0 || Ps.Curve2 != 0
		|| Ps.Pitch1 != 0 || Ps.Pitch2 != 0 || Ps.Rinji1 != 0 || Ps.Rinji2 != 0 || Ps.Irekae != 0 || Ps.Yudo != 0)
	{
		if (!Ps.PatternLamp)
			Ps.PatternStart = ATS_SOUND_PLAY;
		else
			Ps.PatternStart = ATS_SOUND_CONTINUE;
		Ps.PatternLamp = true;
	}
	else
	{
		if (Ps.PatternLamp)
			Ps.PatternEnd = ATS_SOUND_PLAY;
		else
			Ps.PatternEnd = ATS_SOUND_CONTINUE;
		Ps.PatternLamp = false;
	}
	if (Ps.PatternSpeed > Ps.PsSpeed)
		Ps.PatternSpeed = Ps.PsSpeed;
}
double PsPatternSig(double distance,int speed,double decelerate)
{
	double PatternSpeed;

	if (distance - g_ini.DATA.Margin > 0 && Ps.PsLamp)
	{
		PatternSpeed = sqrt(7.2 * decelerate * (distance - g_ini.DATA.Margin));
	}
	else
	{
		PatternSpeed = speed;
	}
	if (speed > PatternSpeed)
		PatternSpeed = speed;

	return PatternSpeed;
}
double PsPattern(double distance,int speed,double decelerate)
{
	double PatternSpeed;

	if (distance > 0 && Ps.PsLamp)
	{
		PatternSpeed = sqrt((speed * speed) + (7.2 * decelerate * distance));
	}
	else if (distance < 0 && Ps.PsLamp)
	{
		PatternSpeed = speed;
	}
	else
	{
		PatternSpeed = 0;
	}

	return PatternSpeed;
}
bool PsWarning(double distance,double speed,int Limit,int ReleaseSpeed,double decelerate,int Margin)
{
	bool Warning;
	double Pattern = (speed * speed - Limit * Limit) / 7.2 / decelerate + Margin;

	if (distance - speed * 50 / 36 < Pattern && speed > ReleaseSpeed && distance != 0 && Ps.PsLamp)
	{
		Warning = true;
	}
	else
	{
		Warning = false;
	}
	return Warning;
}
int PsLimit(double distance, int Data)
{
	if (!Ps.PsLamp)
	{
		return 0;
	}
	else if (distance > 21)
	{
		return Ps.PatternData[Data][0];
	}
	else if (distance > 17)
	{
		return Ps.PatternData[Data][1];
	}
	else if (distance > 13.5)
	{
		return Ps.PatternData[Data][2];
	}
	else if (distance > 10.5)
	{
		return Ps.PatternData[Data][3];
	}
	else if (distance > 8)
	{
		return Ps.PatternData[Data][4];
	}
	else if (distance > 5.5)
	{
		return Ps.PatternData[Data][5];
	}
	else if (distance > 3)
	{
		return Ps.PatternData[Data][6];
	}
	else
	{
		return 0;
	}
}
int SetPsPitch(double Pitch)
{
	if (Pitch < 3)
		return 15;
	else if (Pitch < 5)
		return 25;
	else if (Pitch < 7.5)
		return 35;
	else
		return 0;
}
int SetPs2distance(int Pitch)
{
	if (Pitch == 35)
		return 765;
	else if (Pitch == 25)
		return 560;
	else if (Pitch == 15)
		return 455;
	else
		return 390;
}

void PsBeacon(int Type, int Signal, int Optional)
{
	if (Type == 0)
	{
		if (abs(Optional) > 1)
		{
			if (25 - Ps.PsM > 7.5 && Ps.PsMFrq == 108)
				Ps.PitchPa = abs(Optional);
			if (25 - Ps.PsM > 7.5 && Ps.PsMFrq == 95)
				Ps.PitchPb = abs(Optional);
		}
		else
		{
			if (25 - Ps.PsM > 7.5 && Ps.PsMFrq == 108)
				Ps.PitchPa = SetPsPitch(25 - Ps.PsM);
			if (25 - Ps.PsM > 7.5 && Ps.PsMFrq == 95)
				Ps.PitchPb = SetPsPitch(25 - Ps.PsM);
		}
		if (Signal != 0)
			Ps.Irekae = 0;
	}
	if (Type == 1)
	{
		if (Signal == 0 && (Ps.Pa1 != 0 || Ps.Pa2 != 0))
			Ps.P3 = 80;
		else if (Signal != 0)
		{
			if (Ps.PsM > 0 && Ps.PsMFrq == 95 && Ps.PsM < 25)
			{
				Ps.Pb1 = 0;
				Ps.Pb2 = 0;
				Ps.PitchPb = 0;
			}
			else
			{
				Ps.Pa1 = 0;
				Ps.Pa2 = 0;
				Ps.PitchPa = 0;
			}
		}
		if (Signal != 0)
			Ps.Irekae = 0;
	}
	if (Type == 11)
	{
		if (Ps.PsMFrq == 108 && Ps.PsM > 0 && Signal == 0 && Ps.PsM < 25)
			Ps.Pa2 = 100;
		else if (Ps.PsMFrq == 95 && Ps.PsM > 0 && Signal == 0 && Ps.PsM < 25)
			Ps.Pb1 = 655;
		else if (Signal == 0)
			Ps.Pa1 = 655;
	}
	if (Type == 12)
	{
		if (Ps.Ps_2 > 0 && (Ps.Pb1 != 0 || Ps.Pa1 != 0) && Signal == 0)
		{
			if (Ps.Pb1 != 0 && Ps.PbM2)
				Ps.Pb2 = SetPs2distance(Ps.PitchPb);
			else if(Ps.Pa1 != 0)
				Ps.Pa2 = SetPs2distance(Ps.PitchPa);
		}
		else
		{
			if (Ps.Ps2 == 0 && Ps.Ps2_ == 0)
			{
				Ps.Ps_2 = 25;
				if (Ps.PsMFrq == 95 && Ps.PsM > 0 && Ps.PsM < 25)
					Ps.PbM2 = true;
				else
					Ps.PbM2 = false;

			}
		}
	}
	if (Type == 13)
	{
		if (Signal != 0)
		{
			if (Ps.PsM > 0 && Ps.PsMFrq == 95 && Ps.PsM < 25)
			{
				Ps.Pb1 = 0;
				Ps.Pb2 = 0;
				Ps.PitchPb = 0;
			}
			else
			{
				Ps.Pa1 = 0;
				Ps.Pa2 = 0;
				Ps.PitchPa = 0;
			}
		}
	}
	if (Type == 14)
	{
		if (Optional == 90 || Optional == 95 || Optional == 108)
		{
			if (Ps.PsM < 0)
			{
				Ps.PsM = 25;
				Ps.PsMFrq = Optional;
			}
		}
	}
	if (Type == 15)
	{
		if (Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 25)
		{
			if (Optional != 0)
			{
				if (Ps.Point1 == 0 || Ps.Point1 > 550)
				{
					Ps.Point1 = 555;
					Ps.Point1Speed = Optional;
				}
				else
				{
					Ps.Point2 = 555;
					Ps.Point2Speed = Optional;
				}
			}
			else
			{
				if (Ps.Point2 == 0 || Ps.Point2 > Ps.Point1 && Ps.Point1 != 0)
				{
					Ps.Point1 = 0;
					Ps.Point1Speed = 0;
				}
				else
				{
					Ps.Point2 = 0;
					Ps.Point2Speed = 0;
				}
			}
		}
	}
	if (Type == 16)
	{
		if (Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 25)
		{
			if (Optional != 0)
			{
				if (Ps.Curve1 == 0 || Ps.Curve1 > 550)
				{
					Ps.Curve1 = 555;
					Ps.Curve1Speed = Optional;
				}
				else
				{
					Ps.Curve2 = 555;
					Ps.Curve2Speed = Optional;
				}
			}
			else
			{
				if (Ps.Curve2 == 0 || Ps.Curve2 > Ps.Curve1 && Ps.Curve1 != 0)
				{
					Ps.Curve1 = 0;
					Ps.Curve1Speed = 0;
				}
				else
				{
					Ps.Curve2 = 0;
					Ps.Curve2Speed = 0;
				}
			}
		}
	}
	if (Type == 17)
	{
		if (Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 25)
		{
			if (Optional != 0)
			{
				if (Ps.Pitch1 == 0 || Ps.Pitch1 > 550)
				{
					Ps.Pitch1 = 555;
					Ps.Pitch1Speed = Optional;
				}
				else
				{
					Ps.Pitch2 = 555;
					Ps.Pitch2Speed = Optional;
				}
			}
			else
			{
				if (Ps.Pitch2 == 0 || Ps.Pitch2 > Ps.Pitch1 && Ps.Pitch1 != 0)
				{
					Ps.Pitch1 = 0;
					Ps.Pitch1Speed = 0;
				}
				else
				{
					Ps.Pitch2 = 0;
					Ps.Pitch2Speed = 0;
				}
			}
		}
	}
	if (Type == 18)
	{
		if (Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 25)
		{
			if (Optional != 0)
			{
				if (Ps.Rinji1 == 0 || Ps.Rinji1 > 550)
				{
					Ps.Rinji1 = 555;
					Ps.Rinji1Speed = Optional;
				}
				else
				{
					Ps.Rinji2 = 555;
					Ps.Rinji2Speed = Optional;
				}
			}
			else
			{
				if (Ps.Rinji2 == 0 || Ps.Rinji2 > Ps.Rinji1 && Ps.Rinji1 != 0)
				{
					Ps.Rinji1 = 0;
					Ps.Rinji1Speed = 0;
				}
				else
				{
					Ps.Rinji2 = 0;
					Ps.Rinji2Speed = 0;
				}
			}
		}
	}
	if (Signal == 19)
	{
		if (25 - Ps.PsM > 0 && 25 - Ps.PsM <= 6 && Ps.PsMFrq == 108 && Optional != 0)
			Ps.Irekae = Optional;
		else if (25 - Ps.PsM > 0 && 25 - Ps.PsM <= 3 && Ps.PsMFrq == 108)
			Ps.Irekae = 50;
		else if (25 - Ps.PsM > 3 && 25 - Ps.PsM <= 6 && Ps.PsMFrq == 108)
			Ps.Irekae = 30;
	}
	if (Signal == 20)
	{
		if (25 - Ps.PsM > 0 && 25 - Ps.PsM <= 3 && Ps.PsMFrq == 108)
			Ps.Yudo = 25;
	}
	if (Type == 50)
	{
		if (Optional == 0 || Signal == 0)
		{
			if(Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 3)
				Ps.PsCut = true;
			else if(Ps.PsMFrq == 90 && Ps.PsM > 3 && Ps.PsM < 6)
				Ps.PsCut = false;
			if (Ps.Ps2_ > 0 && Ps.Ps2_ < 25 && (Ps.Pb1 != 0 || Ps.Pa1 != 0))
			{
				if (Ps.PbM2 && Ps.Pb1 != 0)
					Ps.Pb2 = SetPs2distance(Ps.PitchPb);
				else if (Ps.Pa1 != 0)
					Ps.Pa2 = SetPs2distance(Ps.PitchPa);
			}
			else
			{
				if (Ps.Ps_2 == 0 && Ps.Ps2 == 0)
				{
					Ps.Ps2_ = 25;
					if (Ps.PsMFrq == 95 && Ps.PsM > 0 && Ps.PsM < 25)
						Ps.PbM2 = true;
					else
						Ps.PbM2 = false;
				}
			}
			Ps.PsM = 25;
			Ps.PsMFrq = 108;
		}
	}
	if (Type == 55)
	{
		if (Ps.Ps2 > 0 && Ps.Ps2 < 25 && (Ps.Pb1 != 0 || Ps.Pa1 != 0) && Signal == 0)
		{
			if (Ps.PbM2 && Ps.Pb1 != 0)
				Ps.Pb2 = SetPs2distance(Ps.PitchPb);
			else if (Ps.Pa1 != 0)
				Ps.Pa2 = SetPs2distance(Ps.PitchPa);
		}
		else
		{
			if (Ps.Ps_2 == 0 && Ps.Ps2_ == 0)
			{
				Ps.Ps2 = 25;
				if (Ps.PsMFrq == 95 && Ps.PsM > 0 && Ps.PsM < 25)
					Ps.PbM2 = true;
				else
					Ps.PbM2 = false;
			}
		}
	}
	if (Type == 64)
	{
		if (Optional < g_ini.DATA.PsMaxspeed && Optional > 0)
			Ps.PsSpeed = Optional;
		else
			Ps.PsSpeed = g_ini.DATA.PsMaxspeed;
	}
	if (Type == 70)
	{
		if (Optional == 80)
		{
			if (Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 25)
			{
				if (PsLimit(25 - Ps.PsM, 2) != 0)
				{
					if (Ps.Pitch1 == 0 || Ps.Pitch1 > 550)
					{
						Ps.Pitch1 = 555;
						Ps.Pitch1Speed = PsLimit(25 - Ps.PsM, 2);
					}
					else
					{
						Ps.Pitch2 = 555;
						Ps.Pitch2Speed = PsLimit(25 - Ps.PsM, 2);
					}
				}
				else
				{
					if (Ps.Pitch2 == 0 || Ps.Pitch2 > Ps.Pitch1 && Ps.Pitch1 != 0)
					{
						Ps.Pitch1 = 0;
						Ps.Pitch1Speed = 0;
					}
					else
					{
						Ps.Pitch2 = 0;
						Ps.Pitch2Speed = 0;
					}
				}
			}
			else if (Ps.PsMFrq == 108 && Ps.PsM > 0 && Signal == 0 && Ps.PsM < 25)
				Ps.Pa2 = 100;
			else if (Ps.PsMFrq == 95 && Ps.PsM > 0 && Signal == 0 && Ps.PsM < 25)
				Ps.Pb1 = 655;
			else if (Signal == 0)
				Ps.Pa1 = 655;
		}
		if (Optional == 85)
		{
			if (Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 25)
			{
				if (PsLimit(25 - Ps.PsM, 1) != 0)
				{
					if (Ps.Curve1 == 0 || Ps.Curve1 > 550)
					{
						Ps.Curve1 = 555;
						Ps.Curve1Speed = PsLimit(25 - Ps.PsM, 1);
					}
					else
					{
						Ps.Curve2 = 555;
						Ps.Curve2Speed = PsLimit(25 - Ps.PsM, 1);
					}
				}
				else
				{
					if (Ps.Curve2 == 0 || Ps.Curve2 > Ps.Curve1 && Ps.Curve1 != 0)
					{
						Ps.Curve1 = 0;
						Ps.Curve1Speed = 0;
					}
					else
					{
						Ps.Curve2 = 0;
						Ps.Curve2Speed = 0;
					}
				}
			}
			if (25 - Ps.PsM > 0 && 25 - Ps.PsM <= 3 && Ps.PsMFrq == 108)
				Ps.Yudo = 25;
			else if (25 - Ps.PsM > 0 && 25 - Ps.PsM <= 3 && Ps.PsMFrq == 108)
				Ps.Yudo = 0;
		}
		if (Optional == 90)
		{
			if (Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 25)
			{
				if (PsLimit(25 - Ps.PsM, 3) != 0)
				{
					if (Ps.Rinji1 == 0 || Ps.Rinji1 > 550)
					{
						Ps.Rinji1 = 555;
						Ps.Rinji1Speed = PsLimit(25 - Ps.PsM, 3);
					}
					else
					{
						Ps.Rinji2 = 555;
						Ps.Rinji2Speed = PsLimit(25 - Ps.PsM, 3);
					}
				}
				else
				{
					if (Ps.Rinji2 == 0 || Ps.Rinji2 > Ps.Rinji1 && Ps.Rinji1 != 0)
					{
						Ps.Rinji1 = 0;
						Ps.Rinji1Speed = 0;
					}
					else
					{
						Ps.Rinji2 = 0;
						Ps.Rinji2Speed = 0;
					}
				}
			}
			else if (25 - Ps.PsM > 0 && 25 - Ps.PsM <= 3 && Ps.PsMFrq == 108)
				Ps.Irekae = 50;
			else if (25 - Ps.PsM > 3 && 25 - Ps.PsM <= 6 && Ps.PsMFrq == 108)
				Ps.Irekae = 30;
			else
			{
				Ps.PsM = 25;
				Ps.PsMFrq = 90;
			}
		}
		if (Optional == 95)
		{
			if (Ps.PsMFrq == 90 && Ps.PsM > 0 && Ps.PsM < 25)
			{
				if (PsLimit(25 - Ps.PsM, 0) != 0)
				{
					if (Ps.Point1 == 0 || Ps.Point1 > 550)
					{
						Ps.Point1 = 555;
						Ps.Point1Speed = PsLimit(25 - Ps.PsM, 0);
					}
					else
					{
						Ps.Point2 = 555;
						Ps.Point2Speed = PsLimit(25 - Ps.PsM, 0);
					}
				}
				else
				{
					if (Ps.Point2 == 0 || Ps.Point2 > Ps.Point1 && Ps.Point1 != 0)
					{
						Ps.Point1 = 0;
						Ps.Point1Speed = 0;
					}
					else
					{
						Ps.Point2 = 0;
						Ps.Point2Speed = 0;
					}
				}
			}
			else
			{
				Ps.PsM = 25;
				Ps.PsMFrq = 95;
			}
		}
		if (Optional == 103)
		{
			if (Signal != 0)
			{
				if (Ps.PsM > 0 && Ps.PsMFrq == 95 && Ps.PsM < 25)
				{
					Ps.Pb1 = 0;
					Ps.Pb2 = 0;
					Ps.PitchPb = 0;
				}
				else
				{
					Ps.Pa1 = 0;
					Ps.Pa2 = 0;
					Ps.PitchPa = 0;
				}
				Ps.Irekae = 0;
			}
		}
	}
}