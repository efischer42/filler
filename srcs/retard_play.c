#include "filler.h"

#include <stdio.h>

void	retard_play(t_machine *machine, t_map *map)
{
	if (map != machine->up_left_corner)
	{
		ft_putendl_fd("Your code is broken", 2);
		dprintf(2, "map x: %zu y: %zu\n", map->x, map->y);
	}
}
