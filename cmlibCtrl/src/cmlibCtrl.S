	.set noreorder

#include "pspstub.s"

	STUB_START "cmlibCtrl",0x40090000,0x00080005
	STUB_FUNC  0xD6247E23,libCtrlMaskAllButtonOn
	STUB_FUNC  0xFC2F5EEA,libCtrlMaskAllButtonOff
	STUB_FUNC  0x8F4F3F5D,libCtrlMaskAllButtonStatus
	STUB_FUNC  0xBEBE49D7,libCtrlMaskAllButtonAgain
	STUB_FUNC  0x8A4B458C,libCtrlMaskButtonOn
	STUB_FUNC  0x516F2112,libCtrlMaskButtonOff
	STUB_FUNC  0x59B5EC72,libCtrlMaskButtonStatus
	STUB_FUNC  0xDDA51CD3,libCtrlCheckButton
	STUB_END
