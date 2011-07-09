#ifndef __CTRLHOOK_H__
#define __CTRLHOOK_H__

// header
#include <pspkernel.h>
#include <pspctrl.h>

// define
typedef int (*CTRL_HANDLER)(SceCtrlData *);

/*
	ctrl.prx�փp�b�`�����Ă܂�
	�K���ŏ���1�x�������s�����Ă�������

	�Ԃ�l
		1 = �����A0 = ���s(���łɃp�b�`����Ă���)�A-1 = ���s
*/
int CtrlControlStartInit(void);

/*
	ctrl�̏����Ɉ����̊֐������荞�܂��邱�Ƃ��ł��܂�

	����1	... ���荞�܂������֐�

	�Ԃ�l
		�O��Ɏw�肵���֐��̃|�C���^

	�g�p���@�̓T���v�����Q�l�ɂ��Ă�������
*/
void *CtrlControlSetHandler(CTRL_HANDLER func);

/*
	�w�肵���{�^���𖳌����ł��܂�

	����1	... ���������������{�^��(������)

	�Ԃ�l
		�O��Ɏw�肳�ꂽ�{�^���̒l

	�� PSP_CTRL_VOLUP, PSP_CTRL_VOLDOWN���͖������ł��Ȃ��݂����ł�
	�� ������0��n���Ɩ������������ł��܂�
	�g�p���@�̓T���v�����Q�l�ɂ��Ă�������
*/
u32 SetDeleteButtons(u32 buttons);

/*
	SetDeleteButtons�֐��Ń{�^���𖳌�������O��
	SceCtrlData�\���̂��擾�ł��܂�

	����1	... SceCtrlData�\���̂�n��

	�g�p���@�̓T���v�����Q�l�ɂ��Ă�������
*/
void GetRawCtrlData(SceCtrlData *pad);

#endif

