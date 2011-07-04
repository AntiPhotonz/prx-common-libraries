#ifndef _CM_LIB_POWER_
#define _CM_LIB_POWER_

#include <psppower.h>

typedef struct {
	int chargeStatus;
	int lifePer;
	int lifeTime;
	int cpuClock;
	int busClock;
	int temp;
	int volt;
	int acStatus;
	int isExist;
	int isLow;
	int isCharging;
} POWER_INFO;

typedef struct {
	int cpuClock;
	int busClock;
} CPU_INFO;

#define SLEEP_MODE    0
#define REBOOT_MODE   1
#define SHUTDOWN_MODE 2

#define NO_CHARGING   0
#define CHARGING      1

#define POWER_ONLINE  1
#define POWER_OFFLINE 0

int  powerControll(int mode);
void exeSoftReset(void);
int setCpuClock(int cpuClock);
CPU_INFO getCpuClock(void);
int getChargeStatus(void);
int getBatteryLifePer(void);
int getBatteryLifeTime(void);
int getBatteryTemp(void);
float getBatteryVolt(void);
int isPowerOnline(void);
int isBatteryExist(void);
int isLowBattery(void);
int isBatteryCharging(void);
POWER_INFO getPowerInfo(void);

#endif

