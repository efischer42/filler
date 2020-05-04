#include "filler.h"

static void	set_starts(t_machine *machine)
{
	t_map	*line_head;

	while (machine->map != NULL)
	{
		line_head = machine->map;
		while (machine->map != NULL)
		{
			if ((machine->map->data & P1_PLAY) == P1_PLAY)
				machine->start = machine->map;
			else if ((machine->map->data & P2_PLAY) == P2_PLAY)
				machine->opponent_start = machine->map;
			machine->map = machine->map->right;
		}
		machine->map = line_head;
		machine->map = machine->map->down;
	}
	machine->map = machine->up_left_corner;
}

static void	set_first_objective(t_machine *machine)
{
	if (machine->opponent_start->x <
		machine->map_width / 2 + machine->map_width % 2)
	{
		if (machine->opponent_start->y <
			machine->map_height / 2 + machine->map_width % 2)
		{
			machine->objective1 = machine->up_left_corner;
		}
		else
			machine->objective1 = machine->bottom_left_corner;
	}
	else
	{
		if (machine->opponent_start->y <
			machine->map_height / 2 + machine->map_height % 2)
		{
			machine->objective1 = machine->up_right_corner;
		}
		else
			machine->objective1 = machine->bottom_right_corner;
	}
	machine->objective1->id = O1;
}

void		set_objectives(t_machine *machine)
{
	set_starts(machine);
	set_first_objective(machine);
	machine->state = ST_ERROR;
}
