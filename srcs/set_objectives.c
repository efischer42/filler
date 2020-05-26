/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objectives.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:47 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:20:33 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		get_start(t_map *map, t_map **start, t_map **opponent)
{
	t_map	*line_head;

	while (map != NULL)
	{
		line_head = map;
		while (map != NULL)
		{
			if ((map->data & P1_PLAY) == P1_PLAY)
				*start = map;
			else if ((map->data & P2_PLAY) == P2_PLAY)
				*opponent = map;
			map = map->right;
		}
		map = line_head;
		map = map->down;
	}
}

void			set_edges(t_machine *machine, t_map *map, uint64_t *edge)
{
	if (map->x == 0 || map->x == machine->map_width - 1)
	{
		if (map->zone == &machine->upl_zone)
			*edge |= LEFTU_EDGE;
		else if (map->zone == &machine->upr_zone)
			*edge |= RIGHTU_EDGE;
		else if (map->zone == &machine->downl_zone)
			*edge |= LEFTD_EDGE;
		else if (map->zone == &machine->downr_zone)
			*edge |= RIGHTD_EDGE;
	}
	if (map->y == 0 || map->y == machine->map_height - 1)
	{
		if (map->zone == &machine->upl_zone)
			*edge |= UPL_EDGE;
		else if (map->zone == &machine->upr_zone)
			*edge |= UPR_EDGE;
		else if (map->zone == &machine->downl_zone)
			*edge |= DOWNL_EDGE;
		else if (map->zone == &machine->downr_zone)
			*edge |= DOWNR_EDGE;
	}
}

static int		is_fair(t_machine *machine, t_map *opponent, t_map *start)
{
	if (ft_abs(start->x - (machine->map_width - opponent->x)) < machine->dist
		&& ft_abs(start->y - (machine->map_height - opponent->y))
		< machine->dist)
	{
		return (TRUE);
	}
	return (FALSE);
}

static void		new_objective(t_machine *machine, t_map *map, t_map *opponent,
					t_map *start)
{
	t_objective	objective;
	t_list		*lst_new;

	ft_bzero(&objective, sizeof(objective));
	if (is_fair(machine, opponent, start) == FALSE
		&& (map->zone == opponent->zone || map->zone == start->zone))
	{
		objective.dead = TRUE;
	}
	objective.map = map;
	set_edges(machine, map, &objective.edge);
	lst_new = ft_lstnew(&objective, sizeof(objective));
	if (lst_new != NULL)
		ft_lstadd(&machine->objective_lst, lst_new);
}

void			set_objectives(t_machine *machine)
{
	t_map	*start;
	t_map	*opponent;

	start = NULL;
	opponent = NULL;
	get_start(machine->map, &start, &opponent);
	new_objective(machine, machine->mx[0][0], opponent, start);
	new_objective(machine, machine->mx[0][machine->map_width - 1], opponent,
		start);
	new_objective(machine, machine->mx[machine->map_height - 1][0], opponent,
		start);
	new_objective(machine,
		machine->mx[machine->map_height - 1][machine->map_width - 1], opponent,
		start);
}
