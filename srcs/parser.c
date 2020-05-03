#include "filler.h"

static void	init_enum_tab(enum e_token **enum_tab)
{
	static enum e_token	token_dollars[] = {EXEC, TAB_END};
	static enum e_token	token_exec[] = {P1, P2, TAB_END};
	static enum e_token	token_player_number[] = {COLON, TAB_END};
	static enum e_token	token_colon[] = {SPACE, END, TAB_END};
	static enum e_token	token_map[] = {NB, TAB_END};
	static enum e_token	token_space[] = {PLAYER_NAME, NB, LINE, SPACE, TAB_END};
	static enum e_token	token_start[] = {DOLLARS, PLATEAU, SPACE, NB, PIECE,
								LINE, TAB_END};
	static enum e_token	token_player_name[] = {END, TAB_END};
	static enum e_token	token_nb[] = {SPACE, COLON, END, TAB_END};
	static enum e_token	token_line[] = {END, TAB_END};

	enum_tab[DOLLARS] = token_dollars;
	enum_tab[EXEC] = token_exec;
	enum_tab[P1] = token_player_number;
	enum_tab[P2] = token_player_number;
	enum_tab[COLON] = token_colon;
	enum_tab[PLATEAU] = token_map;
	enum_tab[PIECE] =  token_map;
	enum_tab[SPACE] = token_space;
	enum_tab[START] = token_start;
	enum_tab[END] = NULL;
	enum_tab[PLAYER_NAME] = token_player_name;
	enum_tab[NB] = token_nb;
	enum_tab[LINE] = token_line;
}

static int	check_tokens(enum e_token *enum_tab, enum e_token type)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = FAILURE;
	while (enum_tab[i] != (enum e_token)TAB_END)
	{
		if (enum_tab[i] == type)
		{
			ret = SUCCESS;
			break ;
		}
		i++;
	}
	return (ret);
}

void		parser(t_machine *machine, t_list *token_lst)
{
	static enum e_token	*enum_tab[NB_TOKEN] = {NULL};
	enum e_token		last_type;

	if (enum_tab[0] == NULL)
		init_enum_tab(enum_tab);
	while (((t_token*)(token_lst->content))->type != END)
	{
		last_type = ((t_token*)(token_lst->content))->type;
		token_lst = token_lst->next;
		if (check_tokens(enum_tab[last_type],
			((t_token*)(token_lst->content))->type) == FAILURE)
		{
			ft_putendl_fd("Parse error", 2);
			machine->state = ST_ERROR;
			break ;
		}
	}
}
