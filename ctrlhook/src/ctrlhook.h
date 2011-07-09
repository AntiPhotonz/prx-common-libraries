#ifndef __CTRLHOOK_H__
#define __CTRLHOOK_H__

// header
#include <pspkernel.h>
#include <pspctrl.h>

// define
typedef int (*CTRL_HANDLER)(SceCtrlData *);

/*
	ctrl.prxへパッチをあてます
	必ず最初に1度だけ実行させてください

	返り値
		1 = 成功、0 = 失敗(すでにパッチされている)、-1 = 失敗
*/
int CtrlControlStartInit(void);

/*
	ctrlの処理に引数の関数を割り込ませることができます

	引数1	... 割り込ませたい関数

	返り値
		前回に指定した関数のポインタ

	使用方法はサンプルを参考にしてください
*/
void *CtrlControlSetHandler(CTRL_HANDLER func);

/*
	指定したボタンを無効化できます

	引数1	... 無効化させたいボタン(複数可)

	返り値
		前回に指定されたボタンの値

	※ PSP_CTRL_VOLUP, PSP_CTRL_VOLDOWN等は無効化できないみたいです
	※ 引数に0を渡すと無効化を解除できます
	使用方法はサンプルを参考にしてください
*/
u32 SetDeleteButtons(u32 buttons);

/*
	SetDeleteButtons関数でボタンを無効化する前の
	SceCtrlData構造体を取得できます

	引数1	... SceCtrlData構造体を渡す

	使用方法はサンプルを参考にしてください
*/
void GetRawCtrlData(SceCtrlData *pad);

#endif

