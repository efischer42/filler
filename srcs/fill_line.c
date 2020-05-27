/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:09:41 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 12:59:20 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_line(t_list *token_lst, size_t width)
{
	size_t	len;
	int		ret;

	ret = FALSE;
	if (((t_token*)(token_lst->content))->type == MAP_LINE)
	{
		len = ft_strlen(((t_token*)(token_lst->content))->value);
		if (len == width)
			ret = TRUE;
	}
	return (ret);
}

static void	fill_map_data(t_machine *machine, char c)
{
	if (c == machine->player && (machine->map->data & P1_PLAY) != P1_PLAY)
	{
		*machine->map->zone -= P1_WT;
		machine->map->data |= P1_PLAY;
		set_edges(machine, machine->map, &machine->edge);
	}
	else if (c == machine->opponent
		&& (machine->map->data & P2_PLAY) != P2_PLAY)
	{
		*machine->map->zone += P2_WT;
		machine->last_play = machine->map;
		machine->map->data |= P2_PLAY;
		fill_opponent_zone(machine);
		set_edges(machine, machine->map, &machine->edge);
	}
}

int			fill_line(t_machine *machine, t_list *token_lst)
{
	t_map	*line_head;
	char	*line;
	size_t	i;
	int		ret;

	i = 0;
	ret = check_line(token_lst, machine->map_width);
	if (ret == TRUE)
	{
		line_head = machine->map;
		line = ((t_token*)(token_lst->content))->value;
		while (line[i] != '\0')
		{
			fill_map_data(machine, line[i]);
			machine->map = machine->map->right;
			i++;
		}
		machine->map = line_head;
		if (machine->map->down != NULL)
			machine->map = machine->map->down;
	}
	return (ret);
}
