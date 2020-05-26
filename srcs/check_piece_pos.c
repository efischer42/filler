/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_piece_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:09:12 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 13:01:25 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_pos(t_map *piece, t_map *piece_play, t_map *node)
{
	int		ret;

	ret = TRUE;
	if ((piece->data & PIECE_PART) == PIECE_PART)
	{
		if (piece == piece_play && (node->data & P1_PLAY) != P1_PLAY)
			ret = FALSE;
		else if ((piece->data & PIECE_PART) == PIECE_PART
			&& piece != piece_play && (((node->data & P2_PLAY) == P2_PLAY)
			|| (node->data & P1_PLAY) == P1_PLAY))
		{
			ret = FALSE;
		}
	}
	return (ret);
}

static int	check_piece_line(t_machine *machine, int play_y, t_map *piece,
						t_map *piece_play)
{
	t_map	*node;
	int		i;
	int		ret;

	i = 0;
	ret = TRUE;
	while (i < machine->piece_width && piece != NULL && ret == TRUE)
	{
		if (play_y < 0 || machine->play_x + i < 0
			|| play_y >= machine->map_height
			|| machine->play_x + i >= machine->map_width)
		{
			if ((piece->data & PIECE_PART) == PIECE_PART)
				ret = FALSE;
		}
		else
		{
			node = machine->mx[play_y][machine->play_x + i];
			ret = check_pos(piece, piece_play, node);
		}
		piece = piece->right;
		i++;
	}
	return (ret);
}

int			check_piece_pos(t_machine *machine, t_map *node, t_map *piece,
						t_map *piece_play)
{
	int		i;
	int		ret;

	i = 0;
	ret = TRUE;
	machine->play_x = node->x - piece_play->x;
	machine->play_y = node->y - piece_play->y;
	while (i < machine->piece_height && piece != NULL && ret == TRUE)
	{
		ret = check_piece_line(machine, machine->play_y + i, piece, piece_play);
		piece = piece->down;
		i++;
	}
	return (ret);
}
