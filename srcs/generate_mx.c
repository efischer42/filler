/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_mx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:10 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:12 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	fill_line_mx(t_machine *machine, int line, t_map *map)
{
	int	i;

	i = 0;
	while (i < machine->map_width && map != NULL)
	{
		machine->mx[line][i] = map;
		map = map->right;
		i++;
	}
}

void		generate_mx(t_machine *machine)
{
	t_map	*map;
	int		i;

	i = 0;
	map = machine->map;
	machine->mx = (t_map***)malloc(sizeof(t_map**) * machine->map_height);
	if (machine->mx == NULL)
		return ;
	while (i < machine->map_height && map != NULL)
	{
		machine->mx[i] = (t_map**)malloc(sizeof(t_map*) * machine->map_width);
		if (machine->mx[i] == NULL)
		{
			//voir plus tard
			return ;
		}
		fill_line_mx(machine, i, map);
		map = map->down;
		i++;
	}
}
