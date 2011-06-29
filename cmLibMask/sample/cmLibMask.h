
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
 * ���[�U�[���[�h�Ŏg����{�^���̓��͂����ׂĖ����ɂ���
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��I���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������܂��B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̃I��/�I�t��ۑ�����|�C���^�B
 * 		maskAllButtonOn��maskAllButtonOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɃI���ɂȂ��Ă���j
 */
int maskAllButtonOn(bool *status);

/**
 * ���[�U�[���[�h�Ŏg����{�^���̓��͂����ׂėL���ɂ���
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ���ׂẴv���O�C�����I�t�ɂ��ĂȂ��ƃ{�^���̓��͂��L���ɂȂ�܂���B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̃I��/�I�t��ۑ�����|�C���^�B
 * 		maskAllButtonOn��maskAllButtonOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɃI�t�ɂȂ��Ă���j
 */
int maskAllButtonOff(bool *status);

/**
 * �{�^���̓��͂����ׂėL�����ǂ������ׂ�
 *
 * @return true �L��, false ����
 */
bool maskAllButtonStatus();

/**
 * �{�^���̓��̗͂L��/�������ăZ�b�g����
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��I���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������A
 * ���ׂẴv���O�C�����I�t�ɂȂ��Ă�����{�^���̓��͂͗L���ɂȂ�܂��B
 *
 * @return true �L��, false ����
 */
bool maskAllButtonAgain();

/**
 * �w�肵���{�^���̓��͂𖳌��ɂ���i���̃v���O�C���Ƌ�������\��������܂��j
 * ��Ɓ��𖳌��ɂ������ꍇ�͈�����(PSP_CTRL_UP + PSP_CTRL_RIGHT)�Ɠ��͂��Ă�������
 * 
 * @param PspCtrlButtons - �����ɂ������{�^��
 *
 * @return ���0
 */
int maskButtonOn(int PspCtrlButtons);

/**
 * �w�肵���{�^���̓��͂�L���ɂ���i���̃v���O�C���Ƌ�������\��������܂��j
 * ��Ɓ���L���ɂ������ꍇ�͈�����(PSP_CTRL_UP + PSP_CTRL_RIGHT)�Ɠ��͂��Ă�������
 * 
 * @param PspCtrlButtons - �L���ɂ������{�^��
 *
 * @return ���0
 */
int maskButtonOff(int PspCtrlButtons);

/**
 * �w�肵���{�^���̗L��/�����𒲂ׂ܂�
 * ������(PSP_CTRL_UP + PSP_CTRL_RIGHT)�Ɠ��͂����ꍇ�ǂ��Ȃ邩�͕�����܂���B
 * 
 * @param PspCtrlButtons - ���ׂ����{�^��
 *
 * @return true �L��, false ����
 */
bool maskButtonStatus(int PspCtrlButtons);

#endif
