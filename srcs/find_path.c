#include "filler.h"

static void		init_map_dir(t_map **map_dir, t_map *map)
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

static int	check_danger_zone(t_map *map)
{
	int			ret;

	ret = TRUE;
	if (map != NULL && ((map->data & DANGER_ZONE) == DANGER_ZONE
			||(map->data & PATH) == PATH))
		ret = FALSE;
	return (ret);
}

int			find_path(t_map *map, t_map *objective, t_list **lst)
{
	enum e_direction	dir[NB_DIR];
	enum e_direction	i;
	t_map				*map_dir[NB_DIR];
	t_list				*lst_new;

	i = 0;
	if (map == objective)
		return (TRUE);
	if (map == NULL)
		return (TRUE);
	if (check_danger_zone(map) == FALSE)
		return (FALSE);
	set_dir(dir, map, objective);
	init_map_dir(map_dir, map);
	map->data |= PATH;
	while (i < NB_DIR)
	{
		if (find_path(map_dir[dir[i]], objective, lst) == TRUE)
			break ;
		i++;
	}
	map->data |= DEBUG;
	lst_new = ft_lstnew(map, sizeof(*map));
	ft_lstadd(lst, lst_new);
	return (TRUE);
}
