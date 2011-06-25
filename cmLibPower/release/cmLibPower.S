	.set noreorder

#include "pspstub.s"

	STUB_START "cmLibPower",0x40090000,0x000E0005
	STUB_FUNC  0x256E1F79,powerControll
	STUB_FUNC  0x10CE1161,exeSoftReset
	STUB_FUNC  0x4C327D27,setCpuClock
	STUB_FUNC  0xD5B5063F,getCpuClock
	STUB_FUNC  0xD67A5BBB,getChargeStatus
	STUB_FUNC  0x0BD86ED2,getBatteryLifePer
	STUB_FUNC  0x0F1AA56F,getBatteryLifeTime
	STUB_FUNC  0x911840EB,getBatteryTemp
	STUB_FUNC  0x14CDE3B3,getBatteryVolt
	STUB_FUNC  0x5E86A953,isPowerOnline
	STUB_FUNC  0x2D9A9B39,isBatteryExist
	STUB_FUNC  0x899C1A19,isLowBattery
	STUB_FUNC  0x19594B5E,isBatteryCharging
	STUB_FUNC  0x00008950,getPowerInfo
	STUB_END
