#include "filler.h"

/*static int	check_path(t_machine *machine, t_point *objective)
{
	int		ret;

	ret = FALSE;
	while (machine->path_lst != NULL)
	{
		if (((t_path*)(machine->path_lst->content))->id == objective->id)
			break ;
		machine->path_lst = machine->path_lst->next;
	}
	if (machine->path_lst != NULL)
	{
		while (machine->path_lst->path != NULL)
		{
			if ((machine->path_lst->path->map->played & P2_PLAY) == P2_PLAY)
				break ;
			machine->path_lst->path = machine->path_lst->path-next;
		}
		if (machine->path_lst->path == NULL)
			ret = TRUE;
	}
	return (ret);
}*/

static void		init_map_dir(t_map **map_dir, t_map *map)
{
	ft_bzero(map_dir, sizeof(*map_dir));
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

static int	check_opponent_distance(t_map *map, enum e_direction dir, size_t dist)
{
	t_map		*map_dir[NB_DIR];
	size_t		i;
	int			ret;

	i = 0;
	ret = TRUE;
	while (i < dist && map != NULL)
	{
		init_map_dir(map_dir, map);
		map = map_dir[dir];
		if (map != NULL && (map->played & P2_PLAY) == P2_PLAY)
		{
			ret = FALSE;
			break ;
		}
		i++;
	}
	return (ret);
}

int			find_path(t_map **map, t_map *objective, t_path *new_path)
{
	enum e_direction	dir[NB_DIR];
	enum e_direction	i;
	t_map				*map_dir[NB_DIR];
	size_t				dist;

	(void)new_path;
	if (*map == objective)
		return (TRUE);
	if (*map == NULL)
		return (FALSE);
	i = 0;
	dist = 4;
	set_dir(dir, *map, objective);
	init_map_dir(map_dir, *map);
	while (i < NB_DIR)
	{
		if (check_opponent_distance(*map, dir[i], dist) == TRUE)
		{
			find_path(&map_dir[dir[i]], objective, new_path);
			break ;
		}
		i++;
	}
	(*map)->played |= PATH;
	return (TRUE);
}

static void	set_path(t_machine *machine, t_map *objective)
{
//	t_lst	*lst_new;
	t_path	*new_path;

	(void)machine;
	new_path = NULL;
	find_path(&machine->start, objective, new_path);
//	lst_new = ft_lstnew(new_path, sizeof(*new_path));
//	ft_lstaddend(&machine->path_lst, lst_new);
}

void		path(t_machine *machine)
{
	ft_putendl_fd("Path", 2);
//	if (check_path(machine, machine->objective1) == FALSE)
		set_path(machine, machine->objective1);
	machine->state = ST_GET_PIECE;
	debug_map(machine->up_left_corner);
}
