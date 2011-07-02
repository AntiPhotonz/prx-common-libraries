	.set noreorder

#include "pspstub.s"

	STUB_START "cmlibAudio",0x40090000,0x000A0005
	STUB_FUNC  0xB0F5E81C,libAudioGetVolume
	STUB_FUNC  0x0D957783,libAudioSetVolume
	STUB_FUNC  0x51FC8DA5,libAudioMuteOn
	STUB_FUNC  0x91C754D2,libAudioMuteOff
	STUB_FUNC  0xAD3F932A,libAudioMuteGetStatus
	STUB_FUNC  0x87EF3CFA,libAudioMuteSetAgain
	STUB_FUNC  0xF5856E31,libAudioIoEnable
	STUB_FUNC  0xA614957F,libAudioIoDisable
	STUB_FUNC  0x8B511909,libAudioIoGetStatus
	STUB_FUNC  0xFD5C4065,libAudioIoSetAgain
	STUB_END
