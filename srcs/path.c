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

static void	check_map_arounds(t_path *path)
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
		path->dead = TRUE;
}

static int	check_path(t_path *path, t_list *lst)
{
	int		ret;

	ret = TRUE;
	if (lst == NULL)
		ret = FALSE;
	while (lst != NULL)
	{
		if ((((t_map*)(lst->content))->data & P2_PLAY) == P2_PLAY
			|| (((t_map*)(lst->content))->data & P1_PLAY) == P1_PLAY)
		//	||  path->objective->dead == TRUE)
		{
		//	ft_putendl_fd("Del path", 2);
			ret = FALSE;
			ft_lstdel(&path->lst, del_path);
			path->path_len = 0;
			path->dead = FALSE;
			break ;
		}
		lst = lst->next;
	}
	if (ret == FALSE && path->dead == FALSE)
		check_map_arounds(path);
	return (ret);
}

static int		set_path(t_machine *machine, t_path *path)
{
	t_list	*lst;
	int		ret;

	lst = NULL;
	path->objective = machine->cur_objective;
	path->dead = machine->cur_objective->dead;
	ret = find_path(machine, path->node, &lst);
	path->lst = lst;
	path->path_len = ft_lstlen(lst);
	return (ret);
}

void		path(t_machine *machine, t_map *map)
{
	t_map				*head_line;
	t_path				*path;
	t_list				*objective_lst;
	int					ret;

	
	while (map != NULL)
	{
		head_line = map;
		while (map != NULL)
		{
			path = get_node_path(map, machine->path_lst);
			ret = check_path(path, path->lst);
			if ((path->node->data & P1_PLAY) == P1_PLAY	&& ret == FALSE)
			{
				objective_lst = machine->objective_lst;
				while (objective_lst != NULL)
				{
					machine->cur_objective = objective_lst->content;
					if (machine->cur_objective->dead == FALSE)
					{
						set_dir(machine, map);
						if (set_path(machine, path) == TRUE)
							break ;
					}
					objective_lst = objective_lst->next;
				}
			}
			map = map->right;
		}
		map = head_line;
		map = map->down;
	}
//	cut_path(machine);
	ft_merge_sort(&machine->path_lst, sort_len_path);
	ft_merge_sort(&machine->path_lst, sort_objective_path);
	ft_merge_sort(&machine->path_lst, sort_dead_path);
//	debug_path_lst(machine->path_lst);
//	debug_map(machine->map);
}
