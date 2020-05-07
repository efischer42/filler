#include "filler.h"

static t_path	*get_node_path(t_map *map, t_list *path_lst)
{
	t_path	*path;

	path = NULL;
	while (path_lst != NULL)
	{
		if (map->x == ((t_path*)(path_lst->content))->node->x
				&& map->y == ((t_path*)(path_lst->content))->node->y)
		{
			path = path_lst->content;
			return (path);
		}
		path_lst = path_lst->next;
	}
	return (path);
}

/*static void	check_map_arounds(t_path *path)
{
	t_map	*map_dir[NB_DIR];
	size_t	i;

	i = 0;
	init_map_dir(map_dir, path->node);
	while (i < NB_DIR)
	{
		if (map_dir[i] != NULL && (map_dir[i]->data & P1_PLAY) != P1_PLAY
			&& (map_dir[i]->data & P1_PLAY) != P2_PLAY)
			break ;
		i++;
	}
	if (i == NB_DIR)
		path->id = DEAD;
}*/

static int	check_path(t_path *path, t_list *lst)
{
	int		ret;

	(void)lst;
//	ret = TRUE;
//	if (lst == NULL)
//		ret = FALSE;
//	while (lst != NULL)
//	{
//		if ((((t_map*)(lst->content))->data & P2_PLAY) == P2_PLAY)
//		{
//			ft_putendl_fd("Del path", 2);
			ret = FALSE;
			ft_lstdel(&path->lst, del_path);
			path->path_len = 0;
//			break ;
//		}
//		lst = lst->next;
//	}
//	if (ret == FALSE && path->id != DEAD)
//		check_map_arounds(path);
	return (ret);
}

static t_map	*play_to(t_machine *machine, t_map *map)
{
	t_map	*objective;

	(void)map;
	objective = machine->objective1;
/*	objective = NULL;
	if (machine->up_left_corner->id != NONE)
		objective = machine->up_left_corner;
	if (machine->up_right_corner->id != NONE && (objective == NULL
		|| map->ul_dist > map->ur_dist))
	{
		objective = machine->up_right_corner;
	}
	if (machine->bottom_left_corner->id != NONE && map->ur_dist > map->bl_dist)
		objective = machine->bottom_left_corner;
	if (machine->bottom_right_corner->id != NONE && map->bl_dist > map->br_dist)
		objective = machine->bottom_right_corner;
*/	return (objective);
}

static void		set_path(t_path *path, t_map *objective)
{
	t_list	*lst;

	lst = NULL;
	path->id = objective->id;
	find_path(path->node, objective, &lst);
	path->lst = lst;
	path->path_len = ft_lstlen(lst);
}

void		path(t_machine *machine, t_map *map)
{
	t_map	*head_line;
	t_path	*path;
	int		ret;

	while (map != NULL)
	{
		head_line = map;
		while (map != NULL)
		{
			path = get_node_path(map, machine->path_lst);
			ret = check_path(path, path->lst);
			if ((path->node->data & P1_PLAY) == P1_PLAY	&& ret == FALSE)
				set_path(path, play_to(machine, map));
			map = map->right;
		}
		map = head_line;
		map = map->down;
	}
	ft_merge_sort(&machine->path_lst, sort_path);
//	debug_path_lst(machine->path_lst);
	debug_map(machine->map);
}
