/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:32 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:33 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	lexer_parser(t_machine *machine)
{
	lexer(machine);
	if (machine->state != ST_ERROR)
		parser(machine, machine->token_lst);
	ft_strdel(&machine->input);
}
