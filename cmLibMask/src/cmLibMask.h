
#ifndef _CM_LIB_MASK_
#define	_CM_LIB_MASK_


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
 * 		maskAllButtonOnとmaskAllButtonOff以外でこの値を変更するとおかしくなります。
 *
 * @return 0 成功, < 0 失敗（既にオンになっている）
 */
int maskAllButtonOn(bool *status);

/**
 * ユーザーモードで使えるボタンの入力をすべて有効にする
 * 他のプラグインもこの関数を使っている場合、
 * すべてのプラグインがオフにしてないとボタンの入力が有効になりません。
 * 
 * @param status - それぞれのプラグイン内でのオン/オフを保存するポインタ。
 * 		maskAllButtonOnとmaskAllButtonOff以外でこの値を変更するとおかしくなります。
 *
 * @return 0 成功, < 0 失敗（既にオフになっている）
 */
int maskAllButtonOff(bool *status);

/**
 * ボタンの入力がすべて有効かどうか調べる
 *
 * @return true 有効, false 無効
 */
bool maskAllButtonStatus();

/**
 * ボタンの入力の有効/無効を再セットする
 * 他のプラグインもこの関数を使っている場合、
 * 一つでもオンにしているプラグインがあったらボタンの入力は無効化され、
 * すべてのプラグインがオフになっていたらボタンの入力は有効になります。
 *
 * @return true 有効, false 無効
 */
bool maskAllButtonAgain();

/**
 * 指定したボタンの入力を無効にする（他のプラグインと競合する可能性があります）
 * 上と←を無効にしたい場合は引数に(PSP_CTRL_UP + PSP_CTRL_RIGHT)と入力してください
 * 
 * @param PspCtrlButtons - 無効にしたいボタン
 *
 * @return 常に0
 */
int maskButtonOn(int PspCtrlButtons);

/**
 * 指定したボタンの入力を有効にする（他のプラグインと競合する可能性があります）
 * 上と←を有効にしたい場合は引数に(PSP_CTRL_UP + PSP_CTRL_RIGHT)と入力してください
 * 
 * @param PspCtrlButtons - 有効にしたいボタン
 *
 * @return 常に0
 */
int maskButtonOff(int PspCtrlButtons);

/**
 * 指定したボタンの有効/無効を調べます
 * 引数に(PSP_CTRL_UP + PSP_CTRL_RIGHT)と入力した場合どうなるかは分かりません。
 * 
 * @param PspCtrlButtons - 調べたいボタン
 *
 * @return true 有効, false 無効
 */
bool maskButtonStatus(int PspCtrlButtons);

#endif
