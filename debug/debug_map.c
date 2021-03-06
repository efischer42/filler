/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:09:30 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:09:32 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static char	*get_play(t_machine *machine, uint64_t data, int *zone)
{
	char	*play;

	(void)zone;
	(void)machine;
	play = ".";
	if ((data & PIECE_PART) == PIECE_PART)
		play = "*";
	else if ((data & P1_PLAY) == P1_PLAY)
		play = "O";
	else if ((data & P2_PLAY) == P2_PLAY)
		play = "X";
	else if ((data & PATH) == PATH)
		play = "#";
	else if ((data & DEBUG) == DEBUG)
		play = ">";
	else if ((data & DANGER_ZONE) == DANGER_ZONE)
			play = "!";
/*	else if (zone == &machine->upl_zone)
		play = "1";
	else if (zone == &machine->up_zone)
		play = "2";
	else if (zone == &machine->upr_zone)
		play = "3";
	else if (zone == &machine->left_zone)
		play = "4";
	else if (zone == &machine->mid_zone)
		play = "5";
	else if (zone == &machine->right_zone)
		play = "6";
	else if (zone == &machine->downl_zone)
		play = "7";
	else if (zone == &machine->down_zone)
		play = "8";
	else if (zone == &machine->downr_zone)
		play = "9";
*/	return (play);
}

void		debug_map(t_machine *machine, t_map *map)
{
	char	*print;
	char	*tmp;
	t_map	*head_line;
	char	*play;

	tmp = NULL;
	while (map != NULL)
	{
		print = NULL;
		head_line = map;
		while (map != NULL)
		{
			play = get_play(machine, map->data, map->zone);
			tmp = ft_asprintf("%s ", play);
			print = ft_join_free(print, tmp, 3);
			map = map->right;
		}
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
		map = head_line;
		map = map->down;
	}
}
