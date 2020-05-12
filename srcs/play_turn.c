#include "filler.h"

#include <stdio.h>

static void	check_objectives(t_machine *machine)
{
	size_t	i;

	i = 0;
	while (i < NB_OBJECTIVE)
	{
		if ((machine->objective[i]->data & P1_PLAY) == P1_PLAY
			|| (machine->objective[i]->data & P2_PLAY) == P2_PLAY
			|| (machine->objective[i]->data & DANGER_ZONE) == DANGER_ZONE)
		{
			machine->objective[i]->id = DEAD;
		}
		i++;
	}
}

static void	check_path_lst(t_machine *machine, t_list *path_lst)
{
	enum e_id	id;

	while (path_lst != NULL)
	{
		if (((t_path*)(path_lst->content))->id != NONE
			&& ((t_path*)(path_lst->content))->id != DEAD)
		{
			id = ((t_path*)(path_lst->content))->id - 2;
			if (machine->objective[id]->id == DEAD)
				((t_path*)(path_lst->content))->id = DEAD;
		}
		path_lst = path_lst->next;
	}
}

void		play_turn(t_machine *machine)
{
//	debug_map(machine->map);
//	debug_map(machine->piece);
	if (machine->mx == NULL)
	{
		generate_mx(machine);
		set_objectives(machine);
	}
	check_objectives(machine);
	check_path_lst(machine, machine->path_lst);
	if (machine->state != ST_ERROR)
	{
		path(machine, machine->map);
		if (machine->state != ST_ERROR)
			play(machine, machine->path_lst);
		machine->last_play = NULL;
		machine->map = machine->up_left_corner;
	}
}
