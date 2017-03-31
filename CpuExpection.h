#pragma once
#include "CodeManager.h"
enum RunModCode
{
	RMC_User,
	RMC_Supervisor,
	RMC_SYSTEM,
	RMC_Interrupt
};

class RunModePower
{
public:
	static RunModePower Instance()
	{
		static RunModePower instance;
		return instance;
	}

	bool AllowRun(RunModCode mode, OpCode code)
	{
		std::vector<OpCode>::iterator ret;
		ret = std::find(RunModeMap[mode].begin(), RunModeMap[mode].end(), code);
		if (ret == RunModeMap[mode].end())
			return false;
		else
			return true;
	}
private:
	RunModePower() {
		OpCode BaseCode[] =
		{
			OC_MOV,OC_STR,OC_LDR,OC_PUSH,OC_POP,OC_JMP,OC_CJMP,OC_BJMP,OC_RET,OC_END,
			OC_ADD,OC_SUB,OC_MUL,OC_GT,OC_GTE,OC_LT,OC_LTE,OC_STRB,OC_LDRB,OC_SWI
		};

		for (int i = 0; i < sizeof(BaseCode) / sizeof(OpCode); i++)
		{
			UsrPermission.push_back(BaseCode[i]);
			SvcPermission.push_back(BaseCode[i]);
			SysPermission.push_back(BaseCode[i]);
			IrqPermission.push_back(BaseCode[i]);
		}
		SvcPermission.push_back(OC_SWM);
		SysPermission.push_back(OC_SWM);
		SysPermission.push_back(OC_ENTRY);
		SysPermission.push_back(OC_CALL);
		SysPermission.push_back(OC_EXIT);
		RunModeMap.resize(4);
		RunModeMap[RMC_User] = UsrPermission;
		RunModeMap[RMC_Supervisor] = SvcPermission;
		RunModeMap[RMC_SYSTEM] = SysPermission;
		RunModeMap[RMC_Interrupt] = IrqPermission;
	}
	std::vector<OpCode> UsrPermission;
	std::vector<OpCode> SvcPermission;
	std::vector<OpCode> SysPermission;
	std::vector<OpCode> IrqPermission;
	std::vector<std::vector<OpCode>> RunModeMap;
};


