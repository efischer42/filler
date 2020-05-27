/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:40 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 16:17:40 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	clean_map(t_map *map)
{
	t_map	*head_line;

	while (map != NULL)
	{
		head_line = map;
		while (map != NULL)
		{
			if ((map->data & DANGER_ZONE) == DANGER_ZONE)
				*map->zone -= DGZ_WT;
			map->data &= ~PATH;
			map->data &= ~DANGER_ZONE;
			map = map->right;
		}
		map = head_line->down;
	}
}

static void	check_objectives(t_machine *machine)
{
	t_list		*objective_lst;
	uint64_t	edge;

	objective_lst = machine->objective_lst;
	while (objective_lst != NULL)
	{
		edge = ((t_objective*)(objective_lst->content))->edge;
		if ((machine->edge & edge) == edge)
			((t_objective*)(objective_lst->content))->dead = TRUE;
		objective_lst = objective_lst->next;
	}
}

int			play_turn(t_machine *machine)
{
	int		ret;

	ret = SUCCESS;
	if (machine->mx == NULL)
	{
		if (generate_mx(machine) == FAILURE)
			return (FAILURE);
		ret = set_objectives(machine);
	}
	if (machine->last_play != NULL)
		check_objectives(machine);
	ft_merge_sort(&machine->objective_lst, sort_objective);
	ft_merge_sort(&machine->objective_lst, sort_dead_objective);
	if (ret == SUCCESS)
	{
		if (machine->last_play != NULL)
			ret = path(machine, machine->map);
		if (ret == SUCCESS)
			play(machine, machine->path_lst);
		machine->last_play = NULL;
		clean_map(machine->map);
	}
	return (ret);
}
