#include "filler.h"

#include <stdio.h>

void		init_map_dir(t_map **map_dir, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < NB_DIR)
	{
		ft_bzero(&map_dir[i], sizeof(t_map*));
		i++;
	}
	map_dir[UP] = map->up;
	map_dir[RIGHT] = map->right;
	map_dir[DOWN] = map->down;
	map_dir[LEFT] = map->left;
	if (map->up != NULL)
	{
		map_dir[UP_RIGHT] = map->up->right;
		map_dir[UP_LEFT] = map->up->left;
	}
	if (map->down != NULL)
	{
		map_dir[DOWN_RIGHT] = map->down->right;
		map_dir[DOWN_LEFT] = map->down->left;
	}
}

static int	check_empty_place(t_map *start, t_map *map, t_map *to_obj)
{
	int			ret;

	ret = TRUE;
	if (map == start)
	{
		if ((to_obj != NULL && (to_obj->data & P1_PLAY) == P1_PLAY))
			ret = FALSE;
	}
	else if (map != NULL && ((map->data & DANGER_ZONE) == DANGER_ZONE
			|| (map->data & P1_PLAY) == P1_PLAY || (map->data & P2_PLAY) == P2_PLAY
			|| (map->data & PATH) == PATH))
	{
		ret = FALSE;
	}
	return (ret);
}

int			find_path(t_machine *machine, t_map *start, t_map *map, t_list **lst)
{
	enum e_direction	i;
	t_map				*map_dir[NB_DIR];
	t_list				*lst_new;

	i = 0;
	if (map == machine->cur_objective)
	{
		map->data |= DEBUG;
		lst_new = ft_lstnewnomalloc(map, sizeof(*map));
		ft_lstadd(lst, lst_new);
		return (TRUE);
	}
	if (map == NULL)
		return (TRUE);
//	dprintf(2, "map x: %zu y: %zu\n", map->x, map->y);
	init_map_dir(map_dir, map);
	set_main_dir(machine, map, map_dir);
	if (check_empty_place(start, map, map_dir[machine->dir[0]]) == FALSE)
		return (FALSE);
	while (i < NB_DIR_TO_OBJ)
	{
		if (find_path(machine, start, map_dir[machine->dir[i]], lst) == TRUE)
			break ;
		i++;
	}
/*	if (i == NB_DIR_TO_OBJ)
	{
		map->data |= PATH;
		return  (FALSE);
	}
*/	map->data |= DEBUG;
	lst_new = ft_lstnewnomalloc(map, sizeof(*map));
	ft_lstadd(lst, lst_new);
	return (TRUE);
}
