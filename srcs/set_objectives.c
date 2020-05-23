#include "filler.h"

static void		get_start(t_map *map, t_map **start, t_map **opponent)
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
				*opponent = map;
			map = map->right;
		}
		map = line_head;
		map = map->down;
	}
}

/*static void		set_zone(t_machine *machine, t_map *map)
{
	int		*zone;

	zone = map->zone;
	if (map->x > (machine->map_width + 1) / 3
		&& map->x < machine->map_width / 3 * 2)
	{
		if (map->y < (machine->map_height + 1) / 2)
			map->zone = &machine->up_zone;
		else
			map->zone = &machine->down_zone;
		if ((map->data & P2_PLAY) == P2_PLAY)
		{
			(*map->zone) += P2_WT;
			(*zone) -= P2_WT;
		}
		else if ((map->data & DANGER_ZONE) == DANGER_ZONE)
		{
			(*map->zone) += DGZ_WT;
			(*zone) -= DGZ_WT;
		}
	}
	else if (map->y > (machine->map_height + 1) / 3
		&& map->y < machine->map_height / 3 * 2)
	{
		if (map->x < (machine->map_width + 1) / 2)
			map->zone = &machine->left_zone;
		else
			map->zone = &machine->right_zone;
		if ((map->data & P2_PLAY) == P2_PLAY)
		{
			(*map->zone) += P2_WT;
			(*zone) -= P2_WT;
		}
		else if ((map->data & DANGER_ZONE) == DANGER_ZONE)
		{
			(*map->zone) += DGZ_WT;
			(*zone) -= DGZ_WT;
		}
	}
}

static void		zone(t_machine *machine, t_map *opponent)
{
	t_map	*map;
	t_map	*head_line;

	(void)opponent;
	map = machine->map;
	while (map != NULL)
	{
		head_line = map;
		while (map != NULL)
		{
			if ((opponent->x < (machine->map_width + 1) / 3
				&& map->x < (machine->map_width + 1) / 3)
				|| (opponent->y < (machine->map_height + 1) / 3
				&& map->y < (machine->map_height + 1) / 3)
				|| (opponent->x > machine->map_width / 3 * 2
				&& map->x > machine->map_width / 3 * 2)
				|| (opponent->y > machine->map_height / 3 * 2
				&& map->y > machine->map_height / 3 * 2))
			{
				set_zone(machine, map);
			}
			map = map->right;
		}
		map = head_line->down;
	}
}*/

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
		else if (map->zone == &machine->left_zone)
			*edge |= (LEFTU_EDGE | LEFTD_EDGE);
		else if (map->zone == &machine->right_zone)
			*edge |= (RIGHTU_EDGE | RIGHTD_EDGE);
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
		else if (map->zone == &machine->up_zone)
			*edge |= (UPL_EDGE | UPR_EDGE);
		else if (map->zone == &machine->down_zone)
			*edge |= (DOWNL_EDGE | DOWNR_EDGE);
	}
}

static int		is_fair(t_machine *machine, t_map *opponent, t_map *start)
{
	if (start->x == machine->map_width - opponent->x
		&& start->y == machine->map_height - opponent->y)
	{
		return (TRUE);
	}
	return (FALSE);
}

static void		new_objective(t_machine *machine, t_map *map, t_map *opponent, t_map *start)
{
	t_objective	objective;
	t_list		*lst_new;

	ft_bzero(&objective, sizeof(objective));
	if (is_fair(machine, opponent, start) == FALSE && (map->zone == opponent->zone || map->zone == start->zone))
		objective.dead = TRUE;
	objective.map = map;
	set_edges(machine, map, &objective.edge);
	lst_new = ft_lstnew(&objective, sizeof(objective));
	if (lst_new != NULL)
		ft_lstadd(&machine->objective_lst, lst_new);
}

void			set_objectives(t_machine *machine)
{
	t_map	*start;
	t_map	*opponent;

	start = NULL;
	opponent = NULL;
	get_start(machine->map, &start, &opponent);
//	zone(machine, opponent);
	new_objective(machine, machine->up_left_corner, opponent, start);
	new_objective(machine, machine->up_right_corner, opponent, start);
	new_objective(machine, machine->bottom_left_corner, opponent, start);
	new_objective(machine, machine->bottom_right_corner, opponent, start);
/*	if (opponent->x < start->x)
		new_objective(machine, machine->mx[(machine->map_height + 1) / 2][0]);
	if (opponent->x > start->x)
		new_objective(machine, machine->mx[(machine->map_height + 1) / 2][machine->map_width - 1]);
	if (opponent->y < start->y)
		new_objective(machine, machine->mx[0][(machine->map_width + 1) / 2]);
	if (opponent->y > start->y)
		new_objective(machine, machine->mx[machine->map_height - 1][(machine->map_width + 1) / 2]);
*/}
