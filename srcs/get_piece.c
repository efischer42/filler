/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:20 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:21 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_piece(t_machine *machine)
{
	lexer_parser(machine);
	if (machine->state != ST_ERROR)
	{
		if (((t_token*)(machine->token_lst->next->content))->type == PIECE)
		{
			get_piece_dimensions(machine, machine->token_lst);
			if (machine->piece == NULL)
				generate_piece(machine);
		}
		else if (((t_token*)(machine->token_lst->next->content))->type == LINE)
		{
			fill_piece(machine, machine->token_lst);
			if (machine->piece == machine->head_piece)
				play_turn(machine);
		}
	}
	ft_lstdel(&machine->token_lst, del_lst);
}
