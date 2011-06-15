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
//���̕ϐ���MaskButtonOff��MaskButtonOn�ȊO�ł�����Ƃ��܂������Ȃ��B
//�K������������Ƃ���false�ł���

int example(){

	MaskButtonOn(status);
	//�}�X�N����
	//MaskButton���I���ɂ��Ă�v���O�C�����ЂƂł�����΃}�X�N�����B
	//����āAMaskButton����Ȃ��̂͂ǂ̃v���O�C����MaskButton���I�t�̂Ƃ��̂�MaskButton�͖����ɂȂ�
	//return �͂��̃v���O�C����ŃI���ɏo������0�A�o�����Ȃ�������-1��Ԃ��܂�


	MaskButtonOff(status);
	//�}�X�N����������B
	//MaskButtonOn�Ƌt�̓����ł��B
	//MaskButton����Ȃ��̂͂ǂ̃v���O�C����MaskButton���I�t�̂Ƃ��̂�MaskButton�͖����ɂȂ�܂�
	//return �͂��̃v���O�C����ŃI�t�ɏo������0�A�o�����Ȃ�������-1��Ԃ��܂�

	GetStatus();
	//�}�X�N�o���Ă�����true�A�ʏ�̏�Ԃ�������false��Ԃ��܂��B

	MaskAgain();
	//�ăZ�b�g���āA�}�X�N�o���Ă�����true�A�ʏ�̏�Ԃ�������false��Ԃ��܂��B

}