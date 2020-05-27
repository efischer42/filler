/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:37 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 14:04:29 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int		set_new_path(t_machine *machine, t_path **path)
{
	t_path	new_path;
	t_list	*lst_new;

	if (*path == NULL)
	{
		ft_bzero(&new_path, sizeof(new_path));
		lst_new = ft_lstnew(&new_path, sizeof(new_path));
		if (lst_new == NULL)
			return (FAILURE);
		ft_lstadd(&machine->path_lst, lst_new);
		*path = lst_new->content;
	}
	return (SUCCESS);
}

int				path(t_machine *machine, t_map *map)
{
	t_map	*head_line;
	t_path	*path;

	while (map != NULL)
	{
		head_line = map;
		while (map != NULL)
		{
			if ((map->data & P1_PLAY) == P1_PLAY && map->dead == FALSE)
			{
				path = get_path(machine, map);
				if (set_new_path(machine, &path) == FAILURE)
					return (FAILURE);
				if (set_path(machine, path, map) == TRUE)
					break ;
			}
			map = map->right;
		}
		map = head_line->down;
	}
	ft_merge_sort(&machine->path_lst, sort_len_path);
	ft_merge_sort(&machine->path_lst, sort_objective_path);
	ft_merge_sort(&machine->path_lst, sort_dead_path);
	return (SUCCESS);
}
