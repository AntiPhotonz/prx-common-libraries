	.set noreorder

#include "pspstub.s"

	STUB_START "cmLibMask",0x40090000,0x00070005
	STUB_FUNC  0xA11A230C,maskAllButtonOn
	STUB_FUNC  0x14808A5D,maskAllButtonOff
	STUB_FUNC  0xB4855A04,maskAllButtonStatus
	STUB_FUNC  0x923A5FC7,maskAllButtonAgain
	STUB_FUNC  0x72730D7F,maskButtonOn
	STUB_FUNC  0x6D85A0A5,maskButtonOff
	STUB_FUNC  0x6C537735,maskButtonStatus
	STUB_END
