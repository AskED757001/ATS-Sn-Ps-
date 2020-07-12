#include "ATSIni.h"
#include "ats.h"
#include "dllmain.hpp"
#include "ATS-Sn.h"
#include "ATS-Ps.h"
#include "EB.h"

/// このATSプラグインの、コンピュータ上の絶対パス
char g_module_dir[MAX_PATH];

/// DLLのメイン関数
BOOL WINAPI DllMain(
					HINSTANCE hinstDLL,  ///< DLL モジュールのハンドル
					DWORD fdwReason,     ///< 関数を呼び出す理由
					LPVOID lpvReserved   ///< 予約済み
					)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:

        {
            char fullpath[MAX_PATH];
            char drive[MAX_PATH],
                    dir[MAX_PATH];
			char *posIni;

            GetModuleFileNameA(hinstDLL, fullpath, MAX_PATH);
            _splitpath_s(fullpath, drive, MAX_PATH, dir, MAX_PATH, 0, 0, 0, 0);

            strcpy(g_module_dir, drive);
            strcat(g_module_dir, dir);

			//パスから.dllの位置を検索
			posIni = strstr(fullpath, ".dll");

			// .dllを.iniに置換
			memmove(posIni, ".ini", 4);

			// INIファイルをロードして結果を取得
			if (!g_ini.load(fullpath))
				g_ini.save(fullpath);
	}

        break;

	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:	
        break;
	}
	return true;
}

/// このプラグインがBVEによって読み込まれた時に呼び出される。
void WINAPI atsLoad()
{
}

/// このプラグインがBVEから解放された時に呼び出される。
void WINAPI atsDispose()
{
}

/// BVEがこのATSプラグインのバージョン値を取得しようとした時に呼び出される。
/// \return ATSプラグインのバージョン値
int WINAPI atsGetPluginVersion()
{
	return ATS_VERSION;
}

/// BVEに列車が読み込まれた時に呼び出される。
/// \param[in] vspec 車両の諸元
void WINAPI atsSetVehicleSpec(ATS_VEHICLESPEC vspec)
{
	emgBrake = vspec.BrakeNotches + 1;
	ATSNotch = vspec.AtsNotch;
	Ps.Basedecelerate = g_ini.DATA.Psdecelerate;
}

/// BVEのシナリオが開始された時に呼び出される。
/// \param[in] param ブレーキハンドルの位置
void WINAPI atsInitialize(int param)
{
	speed = 0;
	Ps.PsSpeed = g_ini.DATA.PsMaxspeed;
	if (g_ini.DATA.SnEnabled != 0)
		SnInit(g_ini.DATA.ATSStart);
	if (g_ini.DATA.PsEnabled != 0)
		PsInit(g_ini.DATA.ATSStart);
	if (g_ini.DATA.EBEnabled != 0)
		EBInit(g_ini.DATA.ATSStart);
	Sn.Space = false;
}

/// BVEがシナリオ実行中に毎フレームごとに呼び出される。
/// \param[in] vs 毎処理ごとの車両の状態
/// \param[out] p_panel 運転台へ送る値の配列 (配列の範囲: 0-255)
/// \param[out] p_sound サウンド命令の値の配列 (配列の範囲: 0-255)
/// \return 列車の操縦命令
ATS_HANDLES WINAPI atsElapse(ATS_VEHICLESTATE vs, int *p_panel, int *p_sound)
{
	speed = fabs(vs.Speed);
	deltaT = vs.Time - time;
	double deltaL = vs.Speed / 3600 * deltaT;
	time = vs.Time;
	ATS_HANDLES ret;
	if(Ps.BrakeLamp || Sn.ATSBrake)
	ret.Brake = emgBrake;
	else
	ret.Brake = BrakeNotch;

	if (Reverser * vs.Speed < -7)
		Ps.BrakeLamp = true;

	if (g_ini.DATA.DIR != 0 && !pilotlamp || Ps.BrakeLamp || Sn.ATSBrake)
		ret.Power = 0;
	else
		ret.Power = PowerNotch;
	ret.Reverser = Reverser;


	if (g_ini.DATA.PsEnabled != 0)
	{
		if (p_panel[2] != 0 && p_panel[4] == 0)
			Ps.PEnabled = 1;
		else
			Ps.PEnabled = 0;
		if (BrakeNotch < emgBrake && p_panel[6] != 1)
		{
			if (Sn.PsTimer == 0)
				Sn.PsTimer = time + 2700;
		}
		if (Sn.PsTimer < time && Sn.PsTimer != 0)
		{
			if (!Ps.PowerLamp)
				PsInit(1);
			Sn.PsTimer = 0;
		}
		PsRun(deltaL);
		if (p_panel[6] == 1 || p_panel[53] != 0)
			PsInit(0);
	}
	if (g_ini.DATA.SnEnabled != 0)
	{
		if (BrakeNotch < emgBrake && p_panel[6] != 1 && p_panel[53] == 0)
		{
			SnStart();
		if (Sn.PsTimer == 0)
			Sn.PsTimer = time + 2700;
		}
		SnRun();
		if (p_panel[6] == 1 || p_panel[53] != 0)
			SnInit(0);
	}
	if (g_ini.DATA.EBEnabled != 0)
	{
		if (BrakeNotch < emgBrake && !EB.EBPower)
			EBStart();
		RunEB(deltaT, speed);
	}

	if (Ps.PowerLamp && Ps.PsCut)
		Ps.PsLamp = false;
	else if (Ps.PowerLamp)
		Ps.PsLamp = true;

	if (g_ini.DATA.SnEnabled != 0)
	{
		if (Sn.Space)
			p_panel[0] = 0;
		else
			p_panel[0] = Sn.ATSWhite;
		if (Sn.ATSBrake)
			p_panel[1] = (time % 750) / 375;
		else
			p_panel[1] = Sn.ATSRed;
		p_sound[0] = Sn.bell;
		p_sound[1] = Sn.chime;
		p_sound[20] = Sn.bellstop;
		p_sound[21] = Sn.chimeL;
		p_sound[22] = Sn.chimeR;
	}
	if (g_ini.DATA.PsEnabled != 0)
	{
		p_panel[11] = Ps.PsLamp;
		p_panel[12] = Ps.PowerLamp;
		p_panel[13] = Ps.PatternLamp;
		p_panel[14] = Ps.WarningLamp;
		p_panel[15] = Ps.BrakeLamp;
		p_panel[16] = Ps.PsCut;
		p_sound[10] = Ps.PatternStart;
		p_sound[11] = Ps.Warning;
		p_sound[12] = Ps.PatternEnd;
		p_sound[13] = Ps.BrakeSound;
	}
	if (g_ini.DATA.EBEnabled != 0)
	{
		p_sound[3] = EB.EBSound;
		p_panel[10] = EB.EBLamp;
	}
	

	if (Ps.PsLamp && g_ini.DATA.PsEnabled != 0)
	{
		if (speed < g_ini.DATA.BarFullGauge)
			p_panel[18] = speed * g_ini.DATA.BarFullNumber / g_ini.DATA.BarFullGauge;
		else
			p_panel[18] = g_ini.DATA.BarFullNumber;

		if (Ps.PatternSpeed < g_ini.DATA.BarFullGauge)
			p_panel[19] = Ps.PatternSpeed * g_ini.DATA.BarFullNumber / g_ini.DATA.BarFullGauge;
		else
			p_panel[19] = g_ini.DATA.BarFullNumber;
	}
	else if(g_ini.DATA.PsEnabled != 0)
	{
		p_panel[18] = 0;
		p_panel[19] = g_ini.DATA.BarFullNumber;
	}
	
	return ret;
}

/// プレイヤーによって力行ノッチ位置が変更された時に呼び出される。
/// \param[in] notch 変更後の力行ノッチ位置
void WINAPI atsSetPower(int notch)
{
	if (g_ini.DATA.EBEnabled != 0)
		EBReset();
	PowerNotch = notch;
}

/// プレイヤーによってブレーキノッチ位置が変更された時に呼び出される。
/// \param[in] notch 変更後のブレーキノッチ位置
void WINAPI atsSetBrake(int notch)
{
	if (g_ini.DATA.EBEnabled != 0)
		EBReset();
	BrakeNotch = notch;
}

/// プレイヤーによってレバーサーの位置が変更された時に呼び出される。
/// \param[in] pos 変更後のレバーサーの位置
void WINAPI atsSetReverser(int pos)
{
	if (g_ini.DATA.EBEnabled != 0)
		EBReset();
	Reverser = pos;
}

/// プレイヤーによってATSプラグインで使用するキーが押された時に呼び出される。
/// \param[in] ats_key_code ATSプラグインで使用するキーのインデックス
void WINAPI atsKeyDown(int ats_key_code)
{
	SnButton(ats_key_code);
	if (ats_key_code == ATS_KEY_B1 && BrakeNotch == emgBrake && speed == 0)
	{
		Ps.BrakeLamp = false;
		EBStart();
	}
	if (ats_key_code == ATS_KEY_S)
	{
		Sn.Space = true;
	}
	if (ats_key_code == ATS_KEY_A2)
	{
		if (g_ini.DATA.EBEnabled != 0)
			EBReset();
	}
}
/// プレイヤーによってATSプラグインで使用するキーが押されていて、それが離された時に呼び出される。
/// \param[in] ats_key_code ATSプラグインで使用するキーのインデックス
void WINAPI atsKeyUp(int ats_key_code)
{
	if (ats_key_code == ATS_KEY_S)
	{
		Sn.Space = false;
	}
}

/// プレイヤーによって警笛が取り扱われた時に呼び出される。
/// \param[in] ats_horn 警笛の種類
void WINAPI atsHornBlow(int ats_horn)
{
	if (g_ini.DATA.EBEnabled != 0)
		EBReset();
}

/// BVEによって列車のドアが開かれた時に呼び出される。
void WINAPI atsDoorOpen()
{
	pilotlamp = false;
}

/// BVEによって列車のドアが閉じられた時に呼び出される。
void WINAPI atsDoorClose()
{
	pilotlamp = true;
}

/// BVEによって現在の信号現示が変更された時に呼び出される。
/// \param[in] signal 信号現示のインデックス
void WINAPI atsSetSignal(int signal)
{
}

/// BVEによって地上子を通過した際に呼び出される。
/// \param[in] beacon_data 地上子の情報
void WINAPI atsSetBeaconData(ATS_BEACONDATA beacon_data)
{
	if (g_ini.DATA.PsEnabled != 0 && speed != 0)
		PsBeacon(beacon_data.Type, beacon_data.Signal, beacon_data.Optional);
	if (g_ini.DATA.SnEnabled != 0 && speed != 0)
		SnBeacon(beacon_data.Type, beacon_data.Signal, beacon_data.Optional);
}