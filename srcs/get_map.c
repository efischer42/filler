/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 12:21:31 by efischer          #+#    #+#             */
/*   Updated: 2020/05/28 18:03:32 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	is_index_width_ok(t_machine *machine, char *index_line)
{
	char	c;
	int		i;
	int		ret;

	i = 0;
	c = '0';
	ret = TRUE;
	while (index_line[i] != '\0')
	{
		if (c > '9')
			c = '0';
		if (i > machine->map_width || index_line[i] != c)
		{
			ret = FALSE;
			break ;
		}
		c++;
		i++;
	}
	if (i != machine->map_width)
		ret = FALSE;
	return (ret);
}

static int	check_index_width(t_machine *machine, t_list *token_lst)
{
	char	*index_line;
	size_t	nb_space;

	nb_space = 0;
	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == SPACE)
			nb_space++;
		else if (((t_token*)(token_lst->content))->type == NB)
		{
			index_line = ((t_token*)(token_lst->content))->value;
			if (nb_space != 4
				|| is_index_width_ok(machine, index_line) == FALSE)
			{
				return (FALSE);
			}
		}
		token_lst = token_lst->next;
	}
	return (TRUE);
}

int			get_map(t_machine *machine)
{
	static int	width_checked = FALSE;
	int			ret;

	ret = lexer_parser(machine);
	if (ret == SUCCESS)
	{
		if (((t_token*)(machine->token_lst->next->content))->type == SPACE)
		{
			if (check_index_width(machine, machine->token_lst) == FALSE)
				ret = FAILURE;
			width_checked = TRUE;
		}
		else if (width_checked == FALSE
		|| fill_map(machine, machine->token_lst) == FALSE)
		{
			ret = FAILURE;
		}
	}
	ft_lstdel(&machine->token_lst, del_lst);
	return (ret);
}
