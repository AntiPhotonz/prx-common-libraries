#include "common.h"

int libmCloseAllContainer(MenuContext* Context)
{
	if(Context->IsOpen == false)return -1;

	while( Context->Active->Parent ){
		Context->Active = Context->Active->Parent;
		Context->Active->Ctrl.CNT.IsOpen = false;
	}
	//���j���[������ꂽ
	Context->Params.Action	= Menu_Close;
	Context->IsOpen 		= false;

	return 0;
}
