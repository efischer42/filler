/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:09:26 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 14:29:58 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void init_token_tab(char **token_tab)
{
	token_tab[DOLLARS] = "DOLLARS";
	token_tab[EXEC] = "EXEC";
	token_tab[P1] = "P1";
	token_tab[P2] = "P2";
	token_tab[COLON] = "COLON";
	token_tab[PLATEAU] = "PLATEAU";
	token_tab[PIECE] = "PIECE";
	token_tab[SPACE] = "SPACE";
	token_tab[START] = "START";
	token_tab[END] = "END";
	token_tab[PLAYER_NAME] = "PLAYER_NAME";
	token_tab[NB] = "NB";
	token_tab[MAP_LINE] = "MAP LINE";
	token_tab[PIECE_LINE] = "PIECE LINE";
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
		if (type == PLAYER_NAME || type == NB || type == MAP_LINE || type == PIECE_LINE)
			value = ((t_token*)(lst->content))->value;
		print = ft_asprintf("%s = [%s]\n", token_tab[type], value);
		ft_putstr_fd(print, 2);
		ft_strdel(&print);
		lst = lst->next;
	}
	ft_strdel(&print);
}

static void	init_dir_tab(char **dir_tab)
{
	dir_tab[UP] = "UP";
	dir_tab[UP_RIGHT] = "UP_RIGHT";
	dir_tab[RIGHT] = "RIGHT";
	dir_tab[DOWN_RIGHT] = "DOWN_RIGHT";
	dir_tab[DOWN] = "DOWN";
	dir_tab[DOWN_LEFT] = "DOWN_LEFT";
	dir_tab[LEFT] = "LEFT";
	dir_tab[UP_LEFT] = "UP_LEFT";
}

void		debug_dir(enum e_direction *dir)
{
	enum e_direction	i;
	char				*dir_tab[NB_DIR];
	char				*print;
	char				*tmp;

	i = 0;
	print = NULL;
	init_dir_tab(dir_tab);
	while (i < NB_DIR)
	{
		tmp = ft_asprintf("dir[%d]: %s\n", i, dir_tab[dir[i]]);
		print = ft_join_free(print, tmp, 3);
		i++;
	}
	ft_putstr_fd(print, 2);
	ft_strdel(&print);
}

void		debug_path(t_list *lst)
{
	char	*print;

	while (lst != NULL)
	{
		print = ft_asprintf("path x: %d y: %d", ((t_map*)(lst->content))->x,
					((t_map*)(lst->content))->y);
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
		lst = lst->next;
	}
}
