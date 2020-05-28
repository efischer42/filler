/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:09:56 by efischer          #+#    #+#             */
/*   Updated: 2020/05/28 15:00:03 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_index_height(t_machine *machine, t_list *token_lst, int i)
{
	static int	index = 0;
	size_t		len;
	int			nb;
	int			ret;

	ret = FALSE;
	if (i == index && i < machine->map_height)
	{
		len = ft_strlen(((t_token*)(token_lst->content))->value);
		if (len == INDEX_HEIGHT_FORMAT)
		{
			nb = ft_atoi(((t_token*)(token_lst->content))->value);
			if (nb == i)
				ret = TRUE;
		}
	}
	index++;
	return (ret);
}

static int	fill(t_machine *machine, t_list *token_lst)
{
	int		ret;

	if (machine->map->y + 1 == machine->map_height)
	{
		ret = fill_line(machine, token_lst);
		machine->state++;
		machine->map = machine->head_map;
	}
	else
		ret = fill_line(machine, token_lst);
	return (ret);
}

int			fill_map(t_machine *machine, t_list *token_lst)
{
	int		checked_index;
	int		ret;

	ret = TRUE;
	checked_index = FALSE;
	while (((t_token*)(token_lst->content))->type != END && ret == TRUE)
	{
		if (((t_token*)(token_lst->content))->type == NB)
		{
			ret = check_index_height(machine, token_lst, machine->map->y);
			checked_index = TRUE;
		}
		else if (((t_token*)(token_lst->content))->type == MAP_LINE)
			ret = fill(machine, token_lst);
		token_lst = token_lst->next;
	}
	if (checked_index == FALSE)
		ret = FALSE;
	return (ret);
}
