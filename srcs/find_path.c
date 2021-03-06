/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:04 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		init_map_dir(t_map **map_dir, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < NB_DIR)
	{
		ft_bzero(map_dir + i, sizeof(t_map*));
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

static int	check_empty_place(t_machine *machine, t_map *to_obj)
{
	int			ret;

	(void)machine;
	ret = TRUE;
	if (to_obj != NULL && ((to_obj->data & PATH)
		|| (((to_obj->data & P2_PLAY) || (to_obj->data & DANGER_ZONE))
		&& machine->cur_objective->dead == FALSE)))
	{
		to_obj->data |= PATH;
		ret = FALSE;
	}
	return (ret);
}

int			find_path(t_machine *machine, t_map *map, t_list **lst)
{
	enum e_direction	i;
	t_map				*map_dir[NB_DIR];
	t_list				*lst_new;

	i = 0;
	if (map == NULL || map == machine->cur_objective->map)
		return (TRUE);
	init_map_dir(map_dir, map);
	while (i < NB_DIR_TO_OBJ)
	{
		if (check_empty_place(machine, map_dir[machine->dir[i]]) == TRUE)
		{
			if (find_path(machine, map_dir[machine->dir[i]], lst) == TRUE)
			{
				map->data |= DEBUG;
				lst_new = ft_lstnewnomalloc(map, sizeof(*map));
				ft_lstadd(lst, lst_new);
				return (TRUE);
			}
		}
		i++;
	}
	map->data |= PATH;
	return (FALSE);
}
