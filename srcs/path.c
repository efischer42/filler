#include "filler.h"

static t_path	*get_path(t_machine *machine, t_map *cur_map)
{
	t_list	*path_lst;
	t_map	*map;

	path_lst = machine->path_lst;
	while (path_lst != NULL)
	{
		if (((t_path*)(path_lst->content))->lst != NULL)
		{
			map = ((t_path*)(path_lst->content))->lst->content;
			if (cur_map == map)
				return (path_lst->content);
		}
		path_lst = path_lst->next;
	}
	return (NULL);
}

void			check_map_arounds(t_map *map)
{
	t_map	*map_dir[NB_DIR];
	size_t	i;

	i = 0;
	init_map_dir(map_dir, map);
	while (i < NB_DIR)
	{
		if (map_dir[i] != NULL && (map_dir[i]->data & P1_PLAY) != P1_PLAY
			&& (map_dir[i]->data & P1_PLAY) != P2_PLAY)
			break ;
		i++;
	}
	if (i == NB_DIR)
		map->dead = TRUE;
}

static int		check_path(t_path *path, t_list *lst, t_map *map)
{
	int		ret;

	ret = TRUE;
	if (lst == NULL)
		ret = FALSE;
	while (lst != NULL)
	{
		if ((((t_map*)(lst->content))->data & P2_PLAY) == P2_PLAY
			|| map->dead == TRUE
			|| ((((t_map*)(lst->content))->data & DANGER_ZONE) == DANGER_ZONE
			&& path->objective->dead == FALSE))
		{
			ret = FALSE;
			ft_lstdel(&path->lst, del_path);
			path->path_len = 0;
			path->objective = NULL;
			break ;
		}
		lst = lst->next;
	}
	if (ret == FALSE && map->dead == FALSE)
		check_map_arounds(map);
	return (ret);
}

static int		set_path(t_machine *machine, t_path *path, t_map *map)
{
	t_list	*objective_lst;
	t_list	*lst;
	int		ret;

	ret = check_path(path, path->lst, map);
	if (ret == FALSE && map->dead == FALSE)
	{
		objective_lst = machine->objective_lst;
		while (objective_lst != NULL)
		{
			machine->cur_objective = objective_lst->content;
			set_dir(machine, map);
			lst = NULL;
			path->objective = machine->cur_objective;
			ret = find_path(machine, map, &lst);
			path->lst = lst;
			path->path_len = ft_lstlen(lst);
			if (ret == TRUE)
				return (TRUE);
			objective_lst = objective_lst->next;
		}
	}
	else if (ret == TRUE)
		cut_path(path);
	return (FALSE);
}

void			path(t_machine *machine, t_map *map)
{
	t_map	*head_line;
	t_path	*path;
	t_path	new_path;
	t_list	*lst_new;
	
	while (map != NULL)
	{
		head_line = map;
		while (map != NULL)
		{
			if ((map->data & P1_PLAY) == P1_PLAY && map->dead == FALSE)
			{
				path = get_path(machine, map);
				if (path == NULL)
				{
					ft_bzero(&new_path, sizeof(new_path));
					lst_new = ft_lstnew(&new_path, sizeof(new_path));
					ft_lstadd(&machine->path_lst, lst_new);
					path = lst_new->content;
				}
				if (set_path(machine, path, map) == TRUE)
					break ;
			}
			map = map->right;
		}
		map = head_line->down;
	}
	ft_merge_sort(&machine->path_lst, sort_len_path);
	ft_merge_sort(&machine->path_lst, sort_objective_path);
//	ft_merge_sort(&machine->path_lst, sort_dead_path);
//	debug_path_lst(machine->path_lst);
//	debug_map(machine, machine->map);
}
