#include "common.h"

void libmRemoveContext(MenuContext* Context)
{
	if( !Context || !IS_OPT_FUNC_F(Context->opt) ) return;
	
	MenuItem* Curr = Context->Root;
	
	
	//���j���[�S�A�C�e�����폜(����������j
	while( Curr )
	{
		MenuItem *last = Curr;
		
		if ( Curr->Type == MenuContainer && Curr->Children )
		{
			Curr = Curr->Children;
		}
		else
		{
			Curr = Curr->Next;
			
			if (!Curr && last->Parent)
			{
				Curr = last->Parent->Next;
			}
		}
		
		Context->opt->func.free_p(last);
	}
	
	//�R���e�L�X�g�폜�i����������j
	Context->opt->func.free_p(Context);
}
