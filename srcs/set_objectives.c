#include "filler.h"

static t_map	*get_opponent_start(t_machine *machine)
{
	t_map	*opponent_start;
	t_map	*line_head;

	while (machine->map != NULL)
	{
		line_head = machine->map;
		while (machine->map != NULL)
		{
			if ((machine->map->data & P2_PLAY) == P2_PLAY)
				opponent_start = machine->map;
			machine->map = machine->map->right;
		}
		machine->map = line_head;
		machine->map = machine->map->down;
	}
	machine->map = machine->up_left_corner;
	return (opponent_start);
}

static void		set_first_objective(t_machine *machine, t_map *opponent_start)
{
	if (opponent_start->x < machine->map_width / 2 + machine->map_width % 2)
	{
		if (opponent_start->y <
			machine->map_height / 2 + machine->map_height % 2)
		{
			machine->objective1 = machine->up_left_corner;
		}
		else
			machine->objective1 = machine->bottom_left_corner;
	}
	else
	{
		if (opponent_start->y <
			machine->map_height / 2 + machine->map_height % 2)
		{
			machine->objective1 = machine->up_right_corner;
		}
		else
			machine->objective1 = machine->bottom_right_corner;
	}
	machine->objective1->id = O1;
}

static void		set_second_third_objectives(t_machine *machine)
{
	if (machine->objective1 == machine->up_left_corner)
	{
		machine->objective2 = machine->up_right_corner;
		machine->objective3 = machine->bottom_left_corner;
	}
	else if (machine->objective1 == machine->up_right_corner)
	{
		machine->objective2 = machine->bottom_right_corner;
		machine->objective3 = machine->up_left_corner;
	}
	else if (machine->objective1 == machine->bottom_right_corner)
	{
		machine->objective2 = machine->bottom_left_corner;
		machine->objective3 = machine->up_right_corner;
	}
	else if (machine->objective1 == machine->bottom_left_corner)
	{
		machine->objective2 = machine->up_left_corner;
		machine->objective3 = machine->bottom_right_corner;
	}
}

void			set_objectives(t_machine *machine)
{
	t_map		*opponent_start;

	opponent_start = get_opponent_start(machine);
	set_first_objective(machine, opponent_start);
	set_second_third_objectives(machine);
	machine->objective2->id = O2;
	machine->objective3->id = O3;
}
