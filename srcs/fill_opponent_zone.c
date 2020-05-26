/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_opponent_zone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 13:28:18 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 13:29:34 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_dir_tab(t_map *map, t_map **dir_tab)
{
	ft_bzero(dir_tab, sizeof(*dir_tab));
	if (map != NULL)
	{
		dir_tab[0] = map->up;
		dir_tab[1] = map->right;
		dir_tab[2] = map->down;
		dir_tab[3] = map->left;
	}
}

static void	fill_side(t_map *map, size_t dir, size_t dist)
{
	t_map	*dir_tab[NB_MAIN_DIR];
	size_t	i;

	i = 0;
	while (i < dist)
	{
		init_dir_tab(map, dir_tab);
		map = dir_tab[dir];
		if (map == NULL || (map->data & P2_PLAY) == P2_PLAY
			|| (map->data & P1_PLAY) == P1_PLAY)
			break ;
		if ((map->data & DANGER_ZONE) == FALSE)
		{
			map->data |= DANGER_ZONE;
			*map->zone += DGZ_WT;
		}
		i++;
	}
}

static void	fill_danger_zone(t_map *map, size_t dist, size_t pos)
{
	t_map	*dir_tab[NB_MAIN_DIR];
	size_t	i;
	size_t	dir;

	i = 0;
	dir = (pos + 1) % NB_MAIN_DIR;
	while (i + 1 < dist)
	{
		init_dir_tab(map, dir_tab);
		map = dir_tab[pos];
		if (map == NULL || (map->data & P2_PLAY) == P2_PLAY)
		{
			break ;
		}
		if ((map->data & P1_PLAY) == FALSE
			&& (map->data & DANGER_ZONE) == FALSE)
		{
			map->data |= DANGER_ZONE;
			*map->zone += DGZ_WT;
		}
		i++;
		fill_side(map, dir, dist - i);
	}
}

void		fill_opponent_zone(t_machine *machine)
{
	size_t	i;

	i = 0;
	while (i < NB_MAIN_DIR)
	{
		fill_danger_zone(machine->map, machine->dist, i);
		i++;
	}
}
