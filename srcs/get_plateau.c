/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plateau.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 12:21:05 by efischer          #+#    #+#             */
/*   Updated: 2020/05/28 18:34:42 by efischer         ###   ########.fr       */
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

static int	check_map_dimensions(t_machine *machine, t_list *token_lst)
{
	int		nb_count;
	int		ret;

	ret = TRUE;
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
	if (((t_token*)(token_lst->content))->type != END || nb_count != 2)
		ret = FALSE;
	return (ret);
}

int			get_plateau(t_machine *machine)
{
	int		ret;

	ret = lexer_parser(machine);
	if (ret == SUCCESS)
	{
		if (((t_token*)(machine->token_lst->next->content))->type == PLATEAU)
		{
			if (machine->map == NULL)
				generate_map(machine);
			else
			{
				if (check_map_dimensions(machine, machine->token_lst) == FALSE)
					ret = FAILURE;
			}
		}
		else
			ret = FAILURE;
	}
	ft_lstdel(&machine->token_lst, del_lst);
	machine->state++;
	return (ret);
}
