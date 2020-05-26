/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_main_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:45 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:46 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#include <stdio.h>

static int	check_dist_to_objective(t_machine *machine, t_map *map,
					enum e_direction dir, size_t *dist_to_obj)
{
	size_t	diff_x;
	size_t	diff_y;
	size_t	dist;
	int		ret;

	ret = FALSE;
	if (map != NULL)
	{
		diff_x = ft_abs(map->x - machine->cur_objective->map->x);
		diff_y = ft_abs(map->y - machine->cur_objective->map->y);
		if (dir == UP_RIGHT || dir == UP_LEFT || dir == DOWN_RIGHT
			|| dir == DOWN_LEFT)
		{
			if (diff_x != diff_y)
				return (FALSE);
		}
		dist = diff_x + diff_y;
		if (dist < *dist_to_obj)
		{
			*dist_to_obj = dist;
			ret = TRUE;
		}
	}
	return (ret);
}

static void	switch_dir(t_machine *machine, size_t main_dir)
{
	enum e_direction	tmp;

	if (main_dir == 1)
	{
		tmp = machine->dir[0];
		machine->dir[0] = machine->dir[1];
		machine->dir[1] = tmp;
	}
	else if (main_dir == 2)
	{
		tmp = machine->dir[0];
		machine->dir[0] = machine->dir[1];
		machine->dir[1] = machine->dir[2];
		machine->dir[2] = tmp;
	}
}

void		set_main_dir(t_machine *machine, t_map *map, t_map **map_dir)
{
	size_t	diff_x;
	size_t	diff_y;
	size_t	main_dir;
	size_t	dist;
	size_t	i;

	i = 0;
	main_dir = 0;
	diff_x = ft_abs(map->x - machine->cur_objective->map->x);
	diff_y = ft_abs(map->y - machine->cur_objective->map->y);
	dist = diff_x + diff_y;
	while (i < NB_DIR_TO_OBJ)
	{
		if (check_dist_to_objective(machine, map_dir[machine->dir[i]],
			machine->dir[i], &dist) == TRUE)
		{
			main_dir = i;
		}
		i++;
	}
	if (main_dir != 0)
		switch_dir(machine, main_dir);
}
