#include "filler.h"

static void init_token_tab(char **token_tab)
{
	token_tab[DOLLARS] = "DOLLARS";
	token_tab[EXEC] = "EXEC";
	token_tab[P1] = "P1";
	token_tab[P2] = "P2";
	token_tab[COLON] = "COLON";
	token_tab[NEW_LINE] = "NEW_LINE";
	token_tab[PLATEAU] = "PLATEAU";
	token_tab[PIECE] = "PIECE";
	token_tab[SPACE] = "SPACE";
	token_tab[START] = "START";
	token_tab[END] = "END";
	token_tab[PLAYER_NAME] = "PLAYER_NAME";
	token_tab[NB] = "NB";
	token_tab[LINE] = "LINE";
}

void		debug(t_list *lst)
{
	enum e_token	type;
	char			*token_tab[NB_TOKEN];
	char			*print;
	char			*value;

	init_token_tab(token_tab);
	while (lst != NULL)
	{
		print = NULL;
		value = NULL;
		type = ((t_token*)(lst->content))->type;
		if (type == PLAYER_NAME || type == NB || type == LINE)
			value = ((t_token*)(lst->content))->value;
		print = ft_asprintf("%s = [%s]\n", token_tab[type], value);
		ft_putstr_fd(print, 2);
		ft_strdel(&print);
		lst = lst->next;
	}
	ft_strdel(&print);
}
