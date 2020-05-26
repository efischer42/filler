/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:18 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 13:09:19 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	set_height_width(t_machine *machine, t_list *token_lst,
				int nb_count)
{
	int	width;
	int	height;
	int	ret;

	ret = TRUE;
	if (nb_count == 0)
	{
		height = ft_atoi(((t_token*)(token_lst->content))->value);
		if (machine->map_height != height)
			ret = FALSE;
	}
	else
	{
		width = ft_atoi(((t_token*)(token_lst->content))->value);
		if (machine->map_width != width)
			ret = FALSE;
	}
	return (ret);
}

static void	check_map_dimensions(t_machine *machine, t_list *token_lst)
{
	int		nb_count;

	nb_count = 0;
	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == NB)
		{
			if (set_height_width(machine, token_lst, nb_count) == FALSE)
				break ;
			nb_count++;
		}
		token_lst = token_lst->next;
	}
	if (((t_token*)(token_lst->content))->type != END)
	{
		ft_putendl_fd("Map dimension ERROR", 2);
		machine->state = ST_ERROR;
	}
}

void		get_map(t_machine *machine)
{
	lexer_parser(machine);
	if (machine->state != ST_ERROR)
	{
		if (((t_token*)(machine->token_lst->next->content))->type == PLATEAU)
		{
			if (machine->map == NULL)
				generate_map(machine);
			else
				check_map_dimensions(machine, machine->token_lst);
		}
		else if (((t_token*)(machine->token_lst->next->content))->type == SPACE)
			check_index_width(machine, machine->token_lst);
		else if (((t_token*)(machine->token_lst->next->content))->type == NB)
			fill_map(machine, machine->token_lst);
	}
	ft_lstdel(&machine->token_lst, del_lst);
}
