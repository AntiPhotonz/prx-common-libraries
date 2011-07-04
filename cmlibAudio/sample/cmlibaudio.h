#ifndef _CM_LIB_AUDIO_
#define	_CM_LIB_AUDIO_


#include <pspimpose_driver.h>
#include <pspkernel.h>
#include <pspsdk.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/**
 * ���݂̉��ʂ��擾����
 *
 * @return ���݂̉���
 */
int libAudioGetVolume(void);

/**
 * ���ʂ�ݒ肷��
 * 
 * @param value - �ݒ肵��������
 *
 * @return < 0 ���s
 */
int libAudioSetVolume(int value);

/**
 * �~���[�g��L���ɂ���
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̗L��/������ۑ�����|�C���^�B
 * 		libAudioMuteOn��libAudioMuteOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɗL���ɂȂ��Ă���j
 */
int libAudioMuteOn(bool *status);

/**
 * �~���[�g�𖳌��ɂ���
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̗L��/������ۑ�����|�C���^�B
 * 		libAudioMuteOn��libAudioMuteOff�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɖ����ɂȂ��Ă���j
 */
int libAudioMuteOff(bool *status);

/**
 * ���݃~���[�g���ǂ������ׂ�
 *
 * @return 1 �L��, 0 ����
 */
int libAudioMuteGetStatus(void);

/**
 * �~���[�g�̗L��/�������ăZ�b�g����
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��L���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������A
 * ���ׂẴv���O�C���������ɂȂ��Ă�����{�^���̓��͂͗L���ɂȂ�܂��B
 *
 * @return true �L��, false ����
 */
bool libAudioMuteSetAgain(void);

/**
 * ���̏o�͂�L���ɂ���
 * �~���[�g�Ƃ͏����Ⴂ�܂��B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̗L��/������ۑ�����|�C���^�B
 * 		libAudioIoEnable��libAudioIoDisable�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɗL���ɂȂ��Ă���j
 */
int libAudioIoEnable(bool *status);

/**
 * ���̏o�͂𖳌��ɂ���
 * �~���[�g�Ƃ͏����Ⴂ�܂��B
 * 
 * @param status - ���ꂼ��̃v���O�C�����ł̗L��/������ۑ�����|�C���^�B
 * 		libAudioIoEnable��libAudioIoDisable�ȊO�ł��̒l��ύX����Ƃ��������Ȃ�܂��B
 *
 * @return 0 ����, < 0 ���s�i���ɖ����ɂȂ��Ă���j
 */
int libAudioIoDisable(bool *status);

/**
 * ���̏o�̗͂L��/�����𒲂ׂ�
 * 
 * @return true �L��, false ����
 */
bool libAudioIoGetStatus(void);

/**
 * ���̏o�̗͂L��/�������ăZ�b�g����
 * ���̃v���O�C�������̊֐����g���Ă���ꍇ�A
 * ��ł��L���ɂ��Ă���v���O�C������������{�^���̓��͖͂���������A
 * ���ׂẴv���O�C���������ɂȂ��Ă�����{�^���̓��͂͗L���ɂȂ�܂��B
 *
 * @return true �L��, false ����
 */
bool libAudioIoSetAgain(void);


#endif