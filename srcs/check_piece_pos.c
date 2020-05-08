#include "filler.h"

static t_map	*get_node(t_map *map, int x, int y)
{
	while (map != NULL && map->x < (size_t)x)
		map = map->right;
	while (map != NULL && map->y < (size_t)y)
		map = map->down;
	return (map);
}

static int		check_piece_line(t_machine *machine, int play_y, t_map *piece,
						t_map *piece_play)
{
	size_t	i;
	int		ret;
	t_map	*node;

	i = 0;
	ret = TRUE;
	while (i < machine->piece_width && piece != NULL)
	{
		if (play_y < 0 || machine->play_x + (int)i < 0
			|| play_y >= (int)machine->map_height
			|| machine->play_x + (int)i >= (int)machine->map_width)
		{
			if ((piece->data & PIECE_PART) == PIECE_PART)
				ret = FALSE;
		}
		else
		{
			node = get_node(machine->map, machine->play_x + i, play_y);
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
		}
		if (ret == FALSE)
			break ;
		piece = piece->right;
		i++;
	}
	return (ret);
}

int				check_piece_pos(t_machine *machine, t_map *node, t_map *piece,
						t_map *piece_play)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = TRUE;
	machine->play_x = node->x - piece_play->x;
	machine->play_y = node->y - piece_play->y;
	while (i < machine->piece_height && piece != NULL)
	{
		ret = check_piece_line(machine, machine->play_y + i, piece, piece_play);
		if (ret == FALSE)
			break ;
		piece = piece->down;
		i++;
	}
	return (ret);
}