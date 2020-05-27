/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:32 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 15:40:08 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		lexer_parser(t_machine *machine)
{
	int		ret;

	ret = lexer(machine);
	if (ret == SUCCESS)
		ret = parser(machine->token_lst);
	ft_strdel(&machine->input);
	return (ret);
}
