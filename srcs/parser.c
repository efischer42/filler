/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:35 by efischer          #+#    #+#             */
/*   Updated: 2020/05/28 18:28:35 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_enum_tab1(enum e_token **enum_tab)
{
	static enum e_token	token_dollars[] = {EXEC, TAB_END};
	static enum e_token	token_exec[] = {P1, P2, TAB_END};
	static enum e_token	token_player_number[] = {COLON, TAB_END};
	static enum e_token	token_colon[] = {SPACE, END, TAB_END};
	static enum e_token	token_map[] = {NB, TAB_END};

	enum_tab[DOLLARS] = token_dollars;
	enum_tab[EXEC] = token_exec;
	enum_tab[P1] = token_player_number;
	enum_tab[P2] = token_player_number;
	enum_tab[COLON] = token_colon;
	enum_tab[PLATEAU] = token_map;
	enum_tab[PIECE] = token_map;
}

static void	init_enum_tab2(enum e_token **enum_tab)
{
	static enum e_token	token_space[] = {PLAYER_NAME, NB, MAP_LINE,
								SPACE, TAB_END};
	static enum e_token	token_start[] = {DOLLARS, PLATEAU, SPACE, NB, PIECE,
								PIECE_LINE, TAB_END};
	static enum e_token	token_player_name[] = {END, TAB_END};
	static enum e_token	token_nb[] = {SPACE, COLON, END, TAB_END};
	static enum e_token	token_line[] = {END, TAB_END};

	enum_tab[SPACE] = token_space;
	enum_tab[START] = token_start;
	enum_tab[END] = NULL;
	enum_tab[PLAYER_NAME] = token_player_name;
	enum_tab[NB] = token_nb;
	enum_tab[MAP_LINE] = token_line;
	enum_tab[PIECE_LINE] = token_line;
}

static int	check_tokens(enum e_token *enum_tab, enum e_token type)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = FALSE;
	while (enum_tab[i] != (enum e_token)TAB_END)
	{
		if (enum_tab[i] == type)
		{
			ret = TRUE;
			break ;
		}
		i++;
	}
	return (ret);
}

int			parser(t_list *token_lst)
{
	static enum e_token	*enum_tab[NB_TOKEN] = {NULL};
	enum e_token		last_type;
	int					ret;

	ret = SUCCESS;
	if (enum_tab[0] == NULL)
	{
		init_enum_tab1(enum_tab);
		init_enum_tab2(enum_tab);
	}
	while (((t_token*)(token_lst->content))->type != END && ret == SUCCESS)
	{
		last_type = ((t_token*)(token_lst->content))->type;
		token_lst = token_lst->next;
		if (check_tokens(enum_tab[last_type],
			((t_token*)(token_lst->content))->type) == FALSE)
		{
			ret = FAILURE;
		}
	}
	return (ret);
}
