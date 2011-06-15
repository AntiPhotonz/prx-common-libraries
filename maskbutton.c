#include <pspsdk.h>
#include <pspctrl_kernel.h>


int flag;

bool MaskButton(int flag)
{
  sceCtrl_driver_7CA723DC(0xFFFF, (flag == 0 ? 0 : 1));
  return (flag == 0 ? false : true);
}


int MaskButtonOn(bool status)
{
  if(status != true){
    status = true;
    flag ++;
    MaskButton(flag);
    return 0;
  }
  return -1;
}

int MaskButtonOff(bool status)
{
  if(status == true){
    status = false;
    flag --;
    MaskButton(flag);
    return 0;
  }
  return -1;
}

bool GetStatus()
{
  return (flag == 0 ? false : true);
}

bool MaskAgain()
{
  return MaskButton(flag);
}


/*--------------------------------------------*/
//Example
/*--------------------------------------------*/

bool status = false;
//この変数はMaskButtonOffとMaskButtonOn以外でいじるとうまく動かない。
//必ず初期化するときはfalseでする

int example(){

	MaskButtonOn(status);
	//マスクする
	//MaskButtonをオンにしてるプラグインがひとつでもあればマスクされる。
	//よって、MaskButtonされないのはどのプラグインもMaskButtonがオフのときのみMaskButtonは無効になる
	//return はこのプラグイン上でオンに出来たら0、出来たなかったら-1を返します


	MaskButtonOff(status);
	//マスクを解除する。
	//MaskButtonOnと逆の動きです。
	//MaskButtonされないのはどのプラグインもMaskButtonがオフのときのみMaskButtonは無効になります
	//return はこのプラグイン上でオフに出来たら0、出来たなかったら-1を返します

	GetStatus();
	//マスク出来ていたらtrue、通常の状態だったらfalseを返します。

	MaskAgain();
	//再セットして、マスク出来ていたらtrue、通常の状態だったらfalseを返します。

}