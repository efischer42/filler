/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:09:56 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:26:45 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_index_height(t_list *token_lst, size_t i)
{
	size_t	len;
	size_t	nb;
	int		ret;

	ret = FALSE;
	if (((t_token*)(token_lst->content))->type == NB)
	{
		len = ft_strlen(((t_token*)(token_lst->content))->value);
		if (len == INDEX_HEIGHT_FORMAT)
		{
			nb = ft_atoi(((t_token*)(token_lst->content))->value);
			if (nb == i)
				ret = TRUE;
		}
	}
	return (ret);
}

void		fill_map(t_machine *machine, t_list *token_lst)
{
	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == NB)
		{
			if (check_index_height(token_lst, machine->map->y) == FALSE)
			{
				ft_putendl_fd("Map height index ERROR", 2);
				machine->state = ST_ERROR;
			}
		}
		else if (((t_token*)(token_lst->content))->type == LINE)
		{
			if (machine->map->y + 1 == machine->map_height)
			{
				fill_line(machine, token_lst);
				machine->state = ST_GET_PIECE;
				machine->map = machine->head_map;
			}
			else
				fill_line(machine, token_lst);
		}
		token_lst = token_lst->next;
	}
}
