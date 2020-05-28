/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:20 by efischer          #+#    #+#             */
/*   Updated: 2020/05/28 18:22:48 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_piece(t_machine *machine)
{
	int		ret;

	ret = lexer_parser(machine);
	if (ret == SUCCESS)
	{
		if (((t_token*)(machine->token_lst->next->content))->type == PIECE_LINE)
		{
			fill_piece(machine, machine->token_lst);
			if (machine->piece == machine->head_piece)
			{
				ret = play_turn(machine);
				machine->state = ST_GET_PLATEAU;
			}
		}
		else
			ret = FAILURE;
	}
	ft_lstdel(&machine->token_lst, del_lst);
	return (ret);
}
