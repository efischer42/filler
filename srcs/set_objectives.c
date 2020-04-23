#include "filler.h"

static void	find_start(t_machine *machine)
{
	t_map	*line_head;

	while (machine->map != NULL)
	{
		line_head = machine->map;
		while (machine->map != NULL)
		{
			if ((machine->map->played & P1_PLAY) == P1_PLAY)
			{
				machine->start->x = machine->map->x;
				machine->start->y = machine->map->y;
			}
			else if ((machine->map->played & P2_PLAY) == P2_PLAY)
			{
				machine->opponent_start->x = machine->map->x;
				machine->opponent_start->y = machine->map->y;
			}
			machine->map = machine->map->right;
		}
		machine->map = line_head;
		machine->map = machine->map->down;
	}
	machine->map = machine->map_head;
}

void		set_objectives(t_machine *machine)
{
	char	*print;

	find_start(machine);
	print = ft_asprintf("start x: %d, start y: %d", machine->start->x,
				machine->start->y);
	ft_putendl_fd(print, 2);
	ft_strdel(&print);
	if (machine->start->x < machine->map_width / 2 + machine->map_width % 2)
	{
		if (machine->start->y < machine->map_height / 2 + machine->map_width % 2)
			machine->objective1 = machine->bottom_right_corner;
		else
			machine->objective1 = machine->up_right_corner;
	}
	else
	{
		if (machine->start->y < machine->map_height / 2 + machine->map_height % 2)
			machine->objective1 = machine->bottom_left_corner;
		else
			machine->objective1 = machine->up_left_corner;
	}
	print = ft_asprintf("objective1 x: %d, objective1 y: %d", machine->objective1->x,
				machine->objective1->y);
	ft_putendl_fd(print, 2);
	ft_strdel(&print);
}
