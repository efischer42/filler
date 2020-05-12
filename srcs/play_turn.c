#include "filler.h"

#include <stdio.h>

static void	check_objectives(t_machine *machine)
{
	t_list		*objective_lst;
	t_map		*objective;
	uint64_t	data;
	size_t		diff_x;
	size_t		diff_y;

	objective_lst = machine->objective_lst;
	while (objective_lst != NULL)
	{
		data = ((t_objective*)(objective_lst->content))->map->data;
		if ((data & P1_PLAY) == P1_PLAY || (data & P2_PLAY) == P2_PLAY
			|| (data & DANGER_ZONE) == DANGER_ZONE)
		{
			((t_objective*)(objective_lst->content))->dead = TRUE;
		}
		else
		{
			objective = ((t_objective*)(objective_lst->content))->map;
			diff_x = ft_abs(objective->x - machine->last_play->x);
			diff_y = ft_abs(objective->y - machine->last_play->y);
			((t_objective*)(objective_lst->content))->last_play_dist = diff_x + diff_y;
		}
		objective_lst = objective_lst->next;
	}
}

void		play_turn(t_machine *machine)
{
	if (machine->mx == NULL)
	{
		generate_mx(machine);
		set_objectives(machine);
	}
	if (machine->last_play != NULL)
		check_objectives(machine);
	ft_merge_sort(&machine->objective_lst, sort_objective_lst);
	if (machine->state != ST_ERROR)
	{
		path(machine, machine->map);
		if (machine->state != ST_ERROR)
			play(machine, machine->path_lst);
		machine->last_play = NULL;
		machine->map = machine->up_left_corner;
	}
}
