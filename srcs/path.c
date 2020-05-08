#include "filler.h"

#include <stdio.h>

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
		path->id = DEAD;
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
			|| (((t_map*)(lst->content))->data & DANGER_ZONE) == DANGER_ZONE)
		{
			ft_putendl_fd("del path", 2);
			ret = FALSE;
			ft_lstdel(&path->lst, del_path);
			path->path_len = 0;
			break ;
		}
		lst = lst->next;
	}
	if (ret == FALSE && path->id != DEAD)
		check_map_arounds(path);
	return (ret);
}

static t_map	*play_to(t_machine *machine, t_map *map, size_t i)
{
	t_map	*objective;

	(void)map;
	objective = NULL;
	if (i == 0)
		objective = machine->objective1;
	else if (i == 1)
		objective = machine->objective2;
	else if (i == 2)
		objective = machine->objective3;
	return (objective);
}

static int		set_path(t_path *path, t_map *objective)
{
	t_list	*lst;
	int		ret;

	lst = NULL;
	path->id = objective->id;
	ret = find_path(path->node, path->node, objective, &lst);
	path->lst = lst;
	path->path_len = ft_lstlen(lst);
	return (ret);
}

void		path(t_machine *machine, t_map *map)
{
	t_map	*head_line;
	t_path	*path;
	size_t	i;
	int		ret;

	while (map != NULL)
	{
		head_line = map;
		while (map != NULL)
		{
			path = get_node_path(map, machine->path_lst);
			ret = check_path(path, path->lst);
			if ((path->node->data & P1_PLAY) == P1_PLAY	&& ret == FALSE)
			{
				i = 0;
				while (i < NB_OBJECTIVE)
				{
					if (set_path(path, play_to(machine, map, i)) == TRUE)
						break ;
					i++;
				}
			}
			map = map->right;
		}
		map = head_line;
		map = map->down;
	}
	ft_merge_sort(&machine->path_lst, sort_len_path);
	ft_merge_sort(&machine->path_lst, sort_obj1);
//	debug_path_lst(machine->path_lst);
//	debug_map(machine->map);
}
