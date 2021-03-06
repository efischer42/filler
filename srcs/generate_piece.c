/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_piece.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:12 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 13:34:37 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	generate_line(t_map **new_line, t_map *last_line, int y,
					t_machine *machine)
{
	t_map	*new_piece;
	int		i;

	i = 0;
	while (i < machine->piece_width)
	{
		new_piece = (t_map*)malloc(sizeof(t_map));
		if (new_piece == NULL)
			return (FAILURE);
		data_map(new_piece, last_line, y, i);
		if (last_line != NULL)
			last_line = last_line->right;
		add_map(new_line, new_piece);
		i++;
	}
	return (SUCCESS);
}

int			generate_piece(t_machine *machine)
{
	t_map	*new_line;
	t_map	*last_line;
	int		i;
	int		ret;

	i = 0;
	ret = SUCCESS;
	last_line = NULL;
	while (i < machine->piece_height && ret == SUCCESS)
	{
		new_line = NULL;
		ret = generate_line(&new_line, last_line, i, machine);
		last_line = new_line;
		if (machine->piece == NULL)
			machine->piece = new_line;
		i++;
	}
	machine->head_piece = machine->piece;
	return (ret);
}
