#include "filler.h"

static t_map	*get_node(t_map *map, int x, int y)
{
	while (map != NULL && map->x < (size_t)x)
		map = map->right;
	while (map != NULL && map->y < (size_t)y)
		map = map->down;
	return (map);
}

static int		check_piece_line(t_machine *machine, size_t play_y, t_map *piece,
						t_map *piece_play)
{
	size_t	i;
	int		ret;
	t_map	*node;

	i = 0;
	ret = TRUE;
	while (i < machine->piece_width && piece != NULL)
	{
		if (play_y < 0 || machine->play_x + i < 0)
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
				else if (piece != piece_play && (((node->data & P2_PLAY) == P2_PLAY)
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

static int		check_piece_pos(t_machine *machine, t_map *node, t_map *piece,
						t_map *piece_play)
{
	size_t	i;
	int		ret;

	(void)piece;
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

static int		check_piece_char(t_machine *machine, t_map *node, t_map *piece)
{
	int		ret;

	ret = FALSE;
	if ((piece->data & PIECE_PART) == PIECE_PART)
	{
		if (check_piece_pos(machine, node, machine->piece, piece) == TRUE)
			ret = TRUE;
	}
	return (ret);
}

static int		search_line(t_machine *machine, t_map *node, t_map *piece,
						uint64_t opt)
{
	size_t	i;

	i = 0;
	while (i < machine->piece_height && piece != NULL)
	{
		if ((opt & FROM_UP) == FROM_UP)
		{
			if (check_piece_char(machine, node, piece) == TRUE)
				return (TRUE);
		}
		piece = piece->down;
		i++;
	}
	if ((opt & FROM_DOWN) == FROM_DOWN)
	{
		while (i >= 0)
		{
			if (check_piece_char(machine, node, piece) == TRUE)
				return (TRUE) ;
			piece = piece->up;
			i--;
		}
	}
	return (FALSE);
}

int				piece_placement(t_machine *machine, t_map *node, t_map *piece,
						uint64_t opt)
{
	size_t	i;

	i = 0;
	while (i < machine->piece_width && piece->right != NULL)
	{
		if ((opt & FROM_LEFT) == FROM_LEFT)
		{
			if (search_line(machine, node, piece, opt) == TRUE)
				return (TRUE);
		}
		piece = piece->right;
		i++;
	}
	if ((opt & FROM_RIGHT) == FROM_RIGHT)
	{
		while (i > 0)
		{
			if (search_line(machine, node, piece, opt) == TRUE)
				return (TRUE);
			piece = piece->left;
			i--;
		}
	}
	return (FALSE);
}
