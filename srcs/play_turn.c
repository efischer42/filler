#include "filler.h"

#include <stdio.h>

static void	check_objectives(t_machine *machine)
{
	t_list		*objective_lst;
	uint64_t	edge;

	objective_lst = machine->objective_lst;
	while (objective_lst != NULL)
	{
		edge = ((t_objective*)(objective_lst->content))->edge;
		if ((machine->p1_edge & edge) == edge
			|| (machine->p2_edge & edge) == edge)
		{
			dprintf(2, "objective x: %zu y: %zu\n",
				((t_objective*)(objective_lst->content))->map->x,
				((t_objective*)(objective_lst->content))->map->y);
			((t_objective*)(objective_lst->content))->dead = TRUE;
		}
		objective_lst = objective_lst->next;
	}
}

void		play_turn(t_machine *machine)
{
//	dprintf(2, "ul: %zu, ur: %zu, dl: %zu, dr: %zu\n", machine->upl_zone,
//		machine->upr_zone, machine->downl_zone, machine->downr_zone);
	if (machine->mx == NULL)
	{
		generate_mx(machine);
		set_objectives(machine);
	}
	if (machine->last_play != NULL)
		check_objectives(machine);
	ft_merge_sort(&machine->objective_lst, sort_objective_lst);
	debug_objective_lst(machine->objective_lst);
	if (machine->state != ST_ERROR)
	{
		path(machine, machine->map);
		if (machine->state != ST_ERROR)
			play(machine, machine->path_lst);
		machine->last_play = NULL;
		machine->map = machine->up_left_corner;
	}
}
