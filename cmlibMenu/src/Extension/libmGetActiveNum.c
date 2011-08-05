/*	libmGetActiveNum
	現在のアイテムが指定したアイテムから何番目にあるか調べます
	
	@param: *Context
	target MenuContext
	
	@param: *Item
	target MenuItem(NULLで先頭(コンテナ内の場合はそのコンテナ内の先頭)が対象になる)
	
	@param: Invalid_Skip
	Whether to enable Invalid_Skip.
	
	@return : 0 = Active is target MenuItem, -1 = failed

 */
int libmGetActiveNum(MenuContext *Context, MenuItem *Item , bool Invalid_Skip )
{
	MenuItem *now = libmGetActive(Context);
	MenuItem *top;
	int ret = 0;

	if(Item)top = Item;
	else top = libmGetTopItem( now, Invalid_Skip );

	if(!top)return 0;
	MenuItem *next = top;

	while( next )
	{
		if(next == now)return ret;
		next = libmGetNextItem(next,Invalid_Skip);
		ret ++;
	}
	return -1;
}
