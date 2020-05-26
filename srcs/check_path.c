/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 13:43:30 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 13:43:49 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	check_map_arounds(t_map *map)
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

int		check_path(t_path *path, t_list *lst, t_map *map)
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
