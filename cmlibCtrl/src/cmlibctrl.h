
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
 * ���[�U�[���[�h�Ŏg����{�^���̓��͂����ׂĖ����ɂ���
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��I���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������܂��B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̃I��/�I�t��ۑ�����|�C���^�B
 * 		libCtrlMaskAllButtonOn��libCtrlMaskAllButtonOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɃI���ɂȂ��Ă���j
 */
int libCtrlMaskAllButtonOn(bool *status);

/**
 * ���[�U�[���[�h�Ŏg����{�^���̓��͂����ׂėL���ɂ���
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ���ׂẴv���O�C�����I�t�ɂ��ĂȂ��ƃ{�^���̓��͂��L���ɂȂ�܂���B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̃I��/�I�t��ۑ�����|�C���^�B
 * 		libCtrlMaskAllButtonOn��libCtrlMaskAllButtonOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɃI�t�ɂȂ��Ă���j
 */
int libCtrlMaskAllButtonOff(bool *status);

/**
 * �{�^���̓��͂����ׂėL�����ǂ������ׂ�
 *
 * @return true �L��, false ����
 */
bool libCtrlMaskAllButtonStatus();

/**
 * �{�^���̓��̗͂L��/�������ăZ�b�g����
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��I���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������A
 * ���ׂẴv���O�C�����I�t�ɂȂ��Ă�����{�^���̓��͂͗L���ɂȂ�܂��B
 *
 * @return true �L��, false ����
 */
bool libCtrlMaskAllButtonAgain();

/**
 * �w�肵���{�^���̓��͂𖳌��ɂ���i���̃v���O�C���Ƌ�������\��������܂��j
 * ��Ɓ��𖳌��ɂ������ꍇ�͈�����(PSP_CTRL_UP + PSP_CTRL_RIGHT)�Ɠ��͂��Ă�������
 * 
 * @param PspCtrlButtons - �����ɂ������{�^��
 *
 * @return ���0
 */
int libCtrlMaskButtonOn(int PspCtrlButtons);

/**
 * �w�肵���{�^���̓��͂�L���ɂ���i���̃v���O�C���Ƌ�������\��������܂��j
 * ��Ɓ���L���ɂ������ꍇ�͈�����(PSP_CTRL_UP + PSP_CTRL_RIGHT)�Ɠ��͂��Ă�������
 * 
 * @param PspCtrlButtons - �L���ɂ������{�^��
 *
 * @return ���0
 */
int libCtrlMaskButtonOff(int PspCtrlButtons);

/**
 * �w�肵���{�^���̗L��/�����𒲂ׂ܂�
 * ������(PSP_CTRL_UP + PSP_CTRL_RIGHT)�Ɠ��͂����ꍇ�ǂ��Ȃ邩�͕�����܂���B
 * 
 * @param PspCtrlButtons - ���ׂ����{�^��
 *
 * @return true �L��, false ����
 */
bool libCtrlMaskButtonStatus(int PspCtrlButtons);

/**
 * �w�肵���{�^���̂�������Ă��邩�ǂ����𒲂ׂ܂�
 * sceCtrlPeekBufferPositive(&pad, 1);���ĂԕK�v������܂���B
 * if(pad.Buttons & PspCtrlButtons)�Ɠ����Ǝv���Ă��������B
 *
 * ��Fif((cmCtrlCheckButton(PSP_CTRL_HOME)) (HOME�������ꂽ�Ƃ��̏���) ;
 * 
 * @param PspCtrlButtons - ���ׂ����{�^��
 *
 * @return true �L��, false ����
 *
 */
int libCtrlCheckButton(int PspCtrlButtons);



#endif
