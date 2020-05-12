#include "filler.h"

static t_map	*get_opponent_start(t_map *map, t_map **opponent_start, t_map **start)
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
				*opponent_start = map;
			map = map->right;
		}
		map = line_head;
		map = map->down;
	}
	return (NULL);
}

static void		set_first_objective(t_machine *machine, t_map *start)
{
	if (start->x < machine->map_width / 2 + machine->map_width % 2)
	{
		if (start->y < machine->map_height / 2 + machine->map_height % 2)
			machine->objective[0] = machine->up_left_corner;
		else
			machine->objective[0] = machine->bottom_left_corner;
	}
	else
	{
		if (start->y < machine->map_height / 2 + machine->map_height % 2)
			machine->objective[0] = machine->up_right_corner;
		else
			machine->objective[0] = machine->bottom_right_corner;
	}
	machine->objective[0]->id = O1;
}

static void		set_second_third_objectives(t_machine *machine, t_map *start)
{
	t_map	*head;

	head = start;
	if (machine->objective[0] == machine->up_left_corner
		|| machine->objective[0] == machine->bottom_left_corner)
	{
		while (start->left != NULL)
			start = start->left;
	}
	else
	{
		while (start->right != NULL)
			start = start->right;
	}
	machine->objective[1] = start;
	start = head;
	if (machine->objective[0] == machine->up_left_corner
		|| machine->objective[0] == machine->up_right_corner)
	{
		while (start->up != NULL)
			start = start->up;
	}
	else
	{
		while (start->down != NULL)
			start = start->down;
	}
	machine->objective[2] = start;
}

static void		set_other_objectives(t_machine *machine)
{
	if (machine->objective[0] == machine->up_left_corner)
	{
		machine->objective[3] = machine->up_right_corner;
		machine->objective[4] = machine->bottom_left_corner;
		machine->objective[5] = machine->bottom_right_corner;
	}
	else if (machine->objective[0] == machine->up_right_corner)
	{
		machine->objective[3] = machine->bottom_right_corner;
		machine->objective[4] = machine->up_left_corner;
		machine->objective[5] = machine->bottom_left_corner;
	}
	else if (machine->objective[0] == machine->bottom_right_corner)
	{
		machine->objective[3] = machine->bottom_left_corner;
		machine->objective[4] = machine->up_right_corner;
		machine->objective[5] = machine->up_left_corner;
	}
	else if (machine->objective[0] == machine->bottom_left_corner)
	{
		machine->objective[3] = machine->up_left_corner;
		machine->objective[4] = machine->bottom_right_corner;
		machine->objective[5] = machine->up_right_corner;
	}
}

void			set_objectives(t_machine *machine)
{
	t_map		*opponent_start;
	t_map		*start;

	opponent_start = NULL;
	start = NULL;
	get_opponent_start(machine->map, &opponent_start, &start);
	set_first_objective(machine, opponent_start);
	set_second_third_objectives(machine, start);
	set_other_objectives(machine);
	machine->objective[1]->id = O2;
	machine->objective[2]->id = O3;
	machine->objective[3]->id = O4;
	machine->objective[4]->id = O5;
	machine->objective[5]->id = O6;
}
