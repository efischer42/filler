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

void			set_edges(t_machine *machine, t_map *map, uint64_t *edge)
{
	if (map->x == 0 || map->x == machine->map_width - 1)
	{
		if (map->zone == &machine->upl_zone)
			*edge |= LEFTU_EDGE;
		else if (map->zone == &machine->upr_zone)
			*edge |= RIGHTU_EDGE;
		else if (map->zone == &machine->downl_zone)
			*edge |= LEFTD_EDGE;
		else if (map->zone == &machine->downr_zone)
			*edge |= RIGHTD_EDGE;
	}
	if (map->y == 0 || map->y == machine->map_height - 1)
	{
		if (map->zone == &machine->upl_zone)
			*edge |= UPL_EDGE;
		else if (map->zone == &machine->upr_zone)
			*edge |= UPR_EDGE;
		else if (map->zone == &machine->downl_zone)
			*edge |= DOWNL_EDGE;
		else if (map->zone == &machine->downr_zone)
			*edge |= DOWNR_EDGE;
	}
}

static void		new_objective(t_machine *machine, t_map *map)
{
	t_objective	objective;
	t_list		*lst_new;
	char		*print;

	ft_bzero(&objective, sizeof(objective));
	objective.map = map;
	set_edges(machine, map, &objective.edge);
	lst_new = ft_lstnew(&objective, sizeof(objective));
	if (lst_new != NULL)
		ft_lstadd(&machine->objective_lst, lst_new);
	print = ft_asprintf("edge: %b\n", objective.edge);
	ft_putendl_fd(print, 2);
	ft_strdel(&print);
}

void			set_objectives(t_machine *machine)
{
	t_map		*start;

	(void)start;
	start = get_start(machine->map);
	new_objective(machine, machine->up_left_corner);
	new_objective(machine, machine->up_right_corner);
	new_objective(machine, machine->bottom_left_corner);
	new_objective(machine, machine->bottom_right_corner);
	new_objective(machine, machine->mx[0][start->x]);
	new_objective(machine, machine->mx[machine->map_height - 1][start->x]);
	new_objective(machine, machine->mx[start->y][0]);
	new_objective(machine, machine->mx[start->y][machine->map_width - 1]);
}
