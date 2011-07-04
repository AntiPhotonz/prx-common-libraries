
#ifndef _CM_LIB_CTRL_
#define	_CM_LIB_CTRL_


#include <pspkernel.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <pspctrl_kernel.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/**
 * ユーザーモードで使えるボタンの入力をすべて無効にする
 * 他のプラグインもこの関数を使っている場合、
 * 一つでもオンにしているプラグインがあったらボタンの入力は無効化されます。
 * 
 * @param status - それぞれのプラグイン内でのオン/オフを保存するポインタ。
 * 		libCtrlMaskAllButtonOnとlibCtrlMaskAllButtonOff以外でこの値を変更するとおかしくなります。
 *
 * @return 0 成功, < 0 失敗（既にオンになっている）
 */
int libCtrlMaskAllButtonOn(bool *status);

/**
 * ユーザーモードで使えるボタンの入力をすべて有効にする
 * 他のプラグインもこの関数を使っている場合、
 * すべてのプラグインがオフにしてないとボタンの入力が有効になりません。
 * 
 * @param status - それぞれのプラグイン内でのオン/オフを保存するポインタ。
 * 		libCtrlMaskAllButtonOnとlibCtrlMaskAllButtonOff以外でこの値を変更するとおかしくなります。
 *
 * @return 0 成功, < 0 失敗（既にオフになっている）
 */
int libCtrlMaskAllButtonOff(bool *status);

/**
 * ボタンの入力がすべて有効かどうか調べる
 *
 * @return true 有効, false 無効
 */
bool libCtrlMaskAllButtonStatus();

/**
 * ボタンの入力の有効/無効を再セットする
 * 他のプラグインもこの関数を使っている場合、
 * 一つでもオンにしているプラグインがあったらボタンの入力は無効化され、
 * すべてのプラグインがオフになっていたらボタンの入力は有効になります。
 *
 * @return true 有効, false 無効
 */
bool libCtrlMaskAllButtonAgain();

/**
 * 指定したボタンの入力を無効にする（他のプラグインと競合する可能性があります）
 * 上と←を無効にしたい場合は引数に(PSP_CTRL_UP + PSP_CTRL_RIGHT)と入力してください
 * 
 * @param PspCtrlButtons - 無効にしたいボタン
 *
 * @return 常に0
 */
int libCtrlMaskButtonOn(int PspCtrlButtons);

/**
 * 指定したボタンの入力を有効にする（他のプラグインと競合する可能性があります）
 * 上と←を有効にしたい場合は引数に(PSP_CTRL_UP + PSP_CTRL_RIGHT)と入力してください
 * 
 * @param PspCtrlButtons - 有効にしたいボタン
 *
 * @return 常に0
 */
int libCtrlMaskButtonOff(int PspCtrlButtons);

/**
 * 指定したボタンの有効/無効を調べます
 * 引数に(PSP_CTRL_UP + PSP_CTRL_RIGHT)と入力した場合どうなるかは分かりません。
 * 
 * @param PspCtrlButtons - 調べたいボタン
 *
 * @return true 有効, false 無効
 */
bool libCtrlMaskButtonStatus(int PspCtrlButtons);

/**
 * 指定したボタンのが押されているかどうかを調べます
 * sceCtrlPeekBufferPositive(&pad, 1);を呼ぶ必要がありません。
 * if(pad.Buttons & PspCtrlButtons)と同じと思ってください。
 *
 * 例：if((cmCtrlCheckButton(PSP_CTRL_HOME)) (HOMEが押されたときの処理) ;
 * 
 * @param PspCtrlButtons - 調べたいボタン
 *
 * @return true 有効, false 無効
 *
 */
int libCtrlCheckButton(int PspCtrlButtons);



#endif
