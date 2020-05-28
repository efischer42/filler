/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_piece_dimensions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 13:23:40 by efischer          #+#    #+#             */
/*   Updated: 2020/05/28 18:01:05 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	set_piece_dimensions(t_machine *machine, t_list *lst, int nb_count)
{
	if (nb_count == 0)
		machine->piece_height = ft_atoi(((t_token*)(lst->content))->value);
	else
		machine->piece_width = ft_atoi(((t_token*)(lst->content))->value);
}

int			get_piece_dimensions(t_machine *machine)
{
	int		ret;
	int		nb_count;
	t_list	*token_lst;

	nb_count = 0;
	ret = lexer_parser(machine);
	token_lst = machine->token_lst;
	if (ret == SUCCESS && ((t_token*)(token_lst->next->content))->type == PIECE)
	{
		while (((t_token*)(token_lst->content))->type != END)
		{
			if (((t_token*)(token_lst->content))->type == NB)
			{
				set_piece_dimensions(machine, token_lst, nb_count);
				nb_count++;
			}
			token_lst = token_lst->next;
		}
		ret = generate_piece(machine);
	}
	else
		ret = FAILURE;
	ft_lstdel(&machine->token_lst, del_lst);
	machine->state++;
	return (ret);
}
