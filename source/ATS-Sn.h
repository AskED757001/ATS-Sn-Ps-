void SnInit(int Param)
{
	Sn.ATSBrake = false;
	Sn.ATSChime = false;
	Sn.ATSRed = false;
	Sn.LongTimer = 0;
	Sn.SpeedTimer = 0;
	Sn.SpeedTimer2 = 0;
	Sn.SpeedTimer3 = 0;
	Sn.chimeX = 0;
	Sn.chimeLR = false;
	if (Param == 0)
	{
		Sn.ATSPower = false;
		Sn.ATSWhite = false;
	}
	else
	{
		Sn.ATSPower = true;
		Sn.ATSWhite = true;
	}
}
void SnStart(void)
{
	if (!Sn.ATSPower)
	{
		Sn.ATSPower = true;
		Sn.ATSRed = true;
		Sn.ATSChime = false;
		if (Sn.LongTimer == 0)
			Sn.LongTimer = -time - 1000;
	}
}
void SnRun(void)
{
	if (Sn.LongTimer < 0 && -Sn.LongTimer < time)
	{
		Sn.ATSRed = false;
		Sn.ATSChime = true;
		Sn.ATSWhite = true;
		Sn.LongTimer = 0;
	}
	if (Sn.LongTimer < time - 5000 && Sn.LongTimer > 0 || EB.EBBrake)
	{
		Sn.ATSBrake = true;
		Sn.ATSRed = true;
		Sn.ATSChime = false;
		Sn.ATSWhite = false;
		Sn.LongTimer = 0;
	}
	else if (Sn.LongTimer > 0)
	{
		Sn.ATSRed = true;
		Sn.ATSWhite = false;
		Sn.ATSChime = false;
	}
	if(Sn.SpeedTimer < time)
		Sn.SpeedTimer = 0;

	if (Sn.ATSRed)
		Sn.bell = ATS_SOUND_PLAYLOOPING;
	else
	{
		if (Sn.bell == ATS_SOUND_PLAYLOOPING)
			Sn.bellstop = ATS_SOUND_PLAY;
		else
			Sn.bellstop = ATS_SOUND_CONTINUE;
		Sn.bell = ATS_SOUND_STOP;
	}
	if (Sn.ATSChime)
	{
		Sn.chime = ATS_SOUND_PLAYLOOPING;
		if (Sn.chimeX != 0)
		{
			if (Sn.chimeX < time && !Sn.chimeLR)
			{
				Sn.chimeR = ATS_SOUND_PLAY;
				Sn.chimeX += 250;
				Sn.chimeLR = !Sn.chimeLR;
			}
			else if (Sn.chimeX < time)
			{
				Sn.chimeL = ATS_SOUND_PLAY;
				Sn.chimeX += 250;
				Sn.chimeLR = !Sn.chimeLR;
			}
			else
			{
				Sn.chimeL = ATS_SOUND_CONTINUE;
				Sn.chimeR = ATS_SOUND_CONTINUE;
			}
		}
		else
			Sn.chimeX = time;
	}
	else
	{
		Sn.chimeL = ATS_SOUND_CONTINUE;
		Sn.chimeR = ATS_SOUND_CONTINUE;
		Sn.chime = ATS_SOUND_STOP;
		Sn.chimeX = 0;
		Sn.chimeLR = false;
	}
}
void SnBeacon(int Type, int Signal, int Optional)
{
	if (Type == 0)
	{
		if (Optional == 0 && Signal == 0)
		{
			if (!Sn.ATSBrake)
				Sn.LongTimer = time;
		}
		else if (Optional != 0 && Sn.SpeedTimer3 > time)
		{
			if (!Sn.ATSBrake)
				Sn.LongTimer = time;
		}
	}
	if (Type == 1)
	{
		if (Optional == 0 && Signal == 0)
		{
			if (!Sn.ATSBrake)
				Sn.LongTimer = time - 5000;
		}
		else if (Optional != 0 && Sn.SpeedTimer3 > time)
		{
			if (!Sn.ATSBrake)
				Sn.LongTimer = time - 5000;
		}
	}
	if (Type == 9 && Optional > 0 && Optional < speed)
	{
		if (!Sn.ATSBrake)
		Sn.LongTimer = time - 5000;
	}
	if (Type == 12)
	{
		if (Sn.SpeedTimer == 0 && Signal == 0 && Ps.Pa1 == 0 && Ps.Pb1 == 0)
		{
			Sn.SpeedTimer = time + g_ini.DATA.SnSpeedTimer;
		}
		else if (Sn.SpeedTimer > time && Signal == 0 && Ps.Pa1 == 0 && Ps.Pb1 == 0)
		{
			if (!Sn.ATSBrake)
				Sn.LongTimer = time - 5000;
		}
		else if (Optional < speed && Optional > 0 && Signal == 0 && Ps.Pa1 == 0 && Ps.Pb1 == 0)
		{
			if (!Sn.ATSBrake)
				Sn.LongTimer = time - 5000;
		}
	}
	if (Type == 50)
	{
		if (Sn.SpeedTimer == 0 && Signal == 0 && Ps.Pa1 == 0 && Ps.Pb1 == 0)
		{
			Sn.SpeedTimer = time + g_ini.DATA.SnSpeedTimer;
		}
		else if (Sn.SpeedTimer == 0 && Optional == 0)
		{
			Sn.SpeedTimer = time + g_ini.DATA.SnSpeedTimer;
		}
		else if (Sn.SpeedTimer > time && Signal == 0 && Ps.Pa1 == 0 && Ps.Pb1 == 0)
		{
			if (!Sn.ATSBrake)
				Sn.LongTimer = time - 5000;
		}
		else if (Sn.SpeedTimer > time && Optional == 0)
		{
			if (!Sn.ATSBrake)
				Sn.LongTimer = time - 5000;
		}
	}
	if (Type == 55)
	{
		if (Optional == 0)
		{
			if (Sn.SpeedTimer == 0 && Signal == 0 && Ps.Pa1 == 0 && Ps.Pb1 == 0)
			{
				Sn.SpeedTimer = time + g_ini.DATA.SnSpeedTimer;
			}
			else if (Sn.SpeedTimer > time && Signal == 0 && Ps.Pa1 == 0 && Ps.Pb1 == 0)
			{
				if (!Sn.ATSBrake)
					Sn.LongTimer = time - 5000;
			}
		}
		else
		{
			if (Sn.ATSPower && !Sn.ATSBrake && speed > Optional)
				Sn.LongTimer = time - 5000;
		}
	}
	if (Type == 60)
	{
		Sn.SpeedTimer2 = time;
	}
	if (Type == 61 && Optional > 0 && Signal == 0)
	{
		if (Sn.SpeedTimer2 > time + Optional)
			Sn.LongTimer = time - 5000;
	}
	if (Type == 65)
	{
		Sn.SpeedTimer3 = time + Optional;
	}
}
void SnButton(int atsKeyCode)
{
	if (atsKeyCode == ATS_KEY_S)
	{
		if (Sn.LongTimer > 0 && ATSNotch <= BrakeNotch && !Sn.ATSBrake)
		{
			Sn.LongTimer = 0;
			Sn.ATSRed = false;
			Sn.ATSWhite = true;
			Sn.ATSChime = true;
		}
	}
	if (atsKeyCode == ATS_KEY_A1)
	{
		if (Sn.ATSChime)
		{
			Sn.LongTimer = 0;
			Sn.ATSRed = false;
			Sn.ATSWhite = true;
			Sn.ATSChime = false;
		}
	}
	if (atsKeyCode == ATS_KEY_B1)
	{
		if (Sn.ATSBrake && BrakeNotch == emgBrake && speed == 0)
		{
			Sn.LongTimer = 0;
			Sn.ATSBrake = false;
			Sn.ATSRed = false;
			Sn.ATSWhite = true;
			Sn.ATSChime = true;
		}
	}
}