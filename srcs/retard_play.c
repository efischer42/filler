#include "filler.h"

int		retard_play(t_machine *machine, t_map *map)
{
	t_map	*line_head;

	while (map != NULL)
	{
		line_head = map;
		while (map != NULL)
		{
			if (map->dead == FALSE)
				check_map_arounds(map);
			if ((map->data & P1_PLAY) == P1_PLAY && map->dead == FALSE)
			{
				if (piece_placement(machine, map) == TRUE)
					return (TRUE);
			}
			map = map->right;
		}
		map = line_head->down;
	}
	return (FALSE);
}
