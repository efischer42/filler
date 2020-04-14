#include "filler.h"

static void	init_grammar(char **grammar)
{
	grammar[DOLLARS] = "$$$ ";
	grammar[EXEC] = "exec ";
	grammar[P1] = "p1 ";
	grammar[P2] = "p2 ";
	grammar[COLON] = ":";
	grammar[OP_BRACKET] = " [";
	grammar[CL_BRACKET] = "]";
	grammar[NEW_LINE] = "\n";
	grammar[PLATEAU] = "Plateau ";
	grammar[PIECE] = "Piece ";
	grammar[START] = NULL;
	grammar[END] = NULL;
	grammar[PLAYER_NAME] = NULL;
	grammar[NB] = NULL;
	grammar[INDEX] = NULL;
	grammar[MAP_LINE] = NULL;
	grammar[PIECE_LINE] = NULL;
}

static void	get_next_token(t_machine *machine, t_token *token, size_t *pos,
				char **grammar)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (i < NB_TOKEN)
	{
		len = ft_strlen(grammar[i]);
		if (ft_strnequ(machine->input + *pos, grammar[i], len) == TRUE)
		{
			token->type = i;
			(*pos) += len;
			break ;
		}
		i++;
	}
	if (i == NB_TOKEN)
		get_word(machine, token, pos);
}

void		lexer(t_machine *machine, t_list **lst)
{
	char	*grammar[NB_TOKEN];
	t_token	*token;
	t_list	*lst_new;
	size_t	pos;

	pos = 0;
	init_grammar(grammar);
	while (machine->input[pos] != '\n')
	{
		ft_bzero(token, sizeof(*token));
		get_next_token(machine, token, &pos, grammar);
		lst_new = ft_lstnew(token, sizeof(*token));
		if (lst_new != NULL)
			ft_lstadd(lst_new, lst);
	}
}
