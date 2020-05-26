/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:30 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:31 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_grammar(char **grammar, char *player_name)
{
	grammar[DOLLARS] = "$$$ ";
	grammar[EXEC] = "exec ";
	grammar[P1] = "p1 ";
	grammar[P2] = "p2 ";
	grammar[COLON] = ":";
	grammar[PLATEAU] = "Plateau ";
	grammar[PIECE] = "Piece ";
	grammar[SPACE] = " ";
	grammar[PLAYER_NAME] = player_name;
	grammar[START] = NULL;
	grammar[END] = NULL;
	grammar[NB] = NULL;
	grammar[LINE] = NULL;
}

static void	init_token_lst(t_list **token_lst, enum e_token type)
{
	t_token	token;
	t_list	*lst_new;

	ft_bzero(&token, sizeof(token));
	token.type = type;
	lst_new = ft_lstnew(&token, sizeof(token));
	if (lst_new != NULL)
		ft_lstaddend(token_lst, lst_new);
}

static void	get_next_token(t_machine *machine, t_token *token, size_t *pos,
				char *input)
{
	static char	*grammar[NB_TOKEN];
	size_t		len;
	size_t		i;

	i = 0;
	if (grammar[0] == NULL)
		init_grammar(grammar, machine->player_name);
	while (i < NB_TOKEN)
	{
		len = ft_strlen(grammar[i]);
		if (ft_strnequ(input + *pos, grammar[i], len) == TRUE)
		{
			token->type = i;
			(*pos) += len;
			break ;
		}
		i++;
	}
	if (i == NB_TOKEN)
		get_word(machine, input, token, pos);
}

void		lexer(t_machine *machine)
{
	t_token		token;
	t_list		*lst_new;
	size_t		pos;

	pos = 0;
	machine->token_lst = NULL;
	init_token_lst(&machine->token_lst, START);
	while (machine->input[pos] != '\0' && machine->state != ST_ERROR)
	{
		ft_bzero(&token, sizeof(token));
		get_next_token(machine, &token, &pos, machine->input);
		lst_new = ft_lstnew(&token, sizeof(token));
		if (lst_new != NULL)
			ft_lstaddend(&machine->token_lst, lst_new);
	}
	init_token_lst(&machine->token_lst, END);
}
