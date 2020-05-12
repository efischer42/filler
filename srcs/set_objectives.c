#include "filler.h"

static t_map	*get_start(t_map *map)
{
	t_map	*line_head;

	while (map != NULL)
	{
		line_head = map;
		while (map != NULL)
		{
			if ((map->data & P1_PLAY) == P1_PLAY)
				return (map);
			map = map->right;
		}
		map = line_head;
		map = map->down;
	}
	return (NULL);
}

static void		new_objective(t_machine *machine, t_map *map)
{
	t_objective	objective;
	t_list		*lst_new;

	ft_bzero(&objective, sizeof(objective));
	objective.map = map;
	objective.last_play_dist = ft_abs(map->x - machine->last_play->x) +
				ft_abs(map->y - machine->last_play->y);
	lst_new = ft_lstnew(&objective, sizeof(objective));
	if (lst_new != NULL)
		ft_lstadd(&machine->objective_lst, lst_new);
}

void			set_objectives(t_machine *machine)
{
	t_map		*start;

	start = get_start(machine->map);
	new_objective(machine, machine->up_left_corner);
	new_objective(machine, machine->up_right_corner);
	new_objective(machine, machine->bottom_left_corner);
	new_objective(machine, machine->bottom_right_corner);
}
