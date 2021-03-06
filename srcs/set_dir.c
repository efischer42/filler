/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:44 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:44 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	x_directions(t_machine *machine, t_map *map)
{
	if (map->x > machine->cur_objective->map->x)
		machine->dir[0] = LEFT;
	else if (map->x < machine->cur_objective->map->x)
		machine->dir[0] = RIGHT;
}

static void	y_directions(t_machine *machine, t_map *map)
{
	if (map->y > machine->cur_objective->map->y)
		machine->dir[0] = UP;
	else if (map->y < machine->cur_objective->map->y)
		machine->dir[0] = DOWN;
}

static void	x_y_directions(t_machine *machine, t_map *map)
{
	t_map	*objective;

	objective = machine->cur_objective->map;
	if (map->x > objective->x && map->y > objective->y)
		machine->dir[0] = UP_LEFT;
	else if (map->x > objective->x && map->y < objective->y)
		machine->dir[0] = DOWN_LEFT;
	else if (map->x < objective->x && map->y > objective->y)
		machine->dir[0] = UP_RIGHT;
	else if (map->x < objective->x && map->y < objective->y)
		machine->dir[0] = DOWN_RIGHT;
}

static void	fill_dir(t_machine *machine)
{
	enum e_direction	i;

	i = 1;
	while (i < NB_DIR_TO_OBJ)
	{
		if (i == 1)
			machine->dir[i] = (machine->dir[0] + NB_DIR - i) % NB_DIR;
		else
			machine->dir[i] = (machine->dir[0] + i - 1) % NB_DIR;
		i++;
	}
}

void		set_dir(t_machine *machine, t_map *map)
{
	size_t	diff_x;
	size_t	diff_y;

	if (map != NULL)
	{
		diff_x = ft_abs(map->x - machine->cur_objective->map->x);
		diff_y = ft_abs(map->y - machine->cur_objective->map->y);
		if (diff_x > diff_y * 2)
			x_directions(machine, map);
		else if (diff_y > diff_x * 2)
			y_directions(machine, map);
		else
			x_y_directions(machine, map);
		fill_dir(machine);
	}
}
