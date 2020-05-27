/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:07 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 13:39:48 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	set_map_dimensions(t_machine *machine, int nb_count, t_list *lst)
{
	if (nb_count == 0)
		machine->map_height = ft_atoi(((t_token*)(lst->content))->value);
	else
		machine->map_width = ft_atoi(((t_token*)(lst->content))->value);
}

static void	get_map_dimensions(t_machine *machine, t_list *token_lst)
{
	int		nb_count;

	nb_count = 0;
	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == NB)
		{
			set_map_dimensions(machine, nb_count, token_lst);
			nb_count++;
		}
		token_lst = token_lst->next;
	}
	machine->dist = (machine->map_height + machine->map_width) * 1 / 20;
}

static void	map_zone(t_machine *machine, t_map *map)
{
	if (map->x < (machine->map_width + 1) / 2)
	{
		if (map->y < (machine->map_height + 1) / 2)
			map->zone = &machine->upl_zone;
		else
			map->zone = &machine->downl_zone;
	}
	else
	{
		if (map->y < (machine->map_height + 1) / 2)
			map->zone = &machine->upr_zone;
		else
			map->zone = &machine->downr_zone;
	}
}

static int	generate_line(t_map **new_line, t_map *last_line, int y,
					t_machine *machine)
{
	t_map	*new_map;
	int		i;

	i = 0;
	while (i < machine->map_width)
	{
		new_map = (t_map*)malloc(sizeof(t_map));
		if (new_map == NULL)
			return (FAILURE);
		data_map(new_map, last_line, y, i);
		map_zone(machine, new_map);
		if (last_line != NULL)
			last_line = last_line->right;
		add_map(new_line, new_map);
		i++;
	}
	return (SUCCESS);
}

int			generate_map(t_machine *machine)
{
	t_map	*new_line;
	t_map	*last_line;
	int		i;
	int		ret;

	i = 0;
	ret = SUCCESS;
	last_line = NULL;
	get_map_dimensions(machine, machine->token_lst);
	while (i < machine->map_height && ret != FAILURE)
	{
		new_line = NULL;
		ret = generate_line(&new_line, last_line, i, machine);
		if (machine->head_map == NULL)
			machine->head_map = new_line;
		last_line = new_line;
		i++;
	}
	machine->map = machine->head_map;
	return (ret);
}
