#include "filler.h"

static t_map	*get_node(t_map *map, int x, int y)
{
	while (map != NULL && map->x < (size_t)x)
		map = map->right;
	while (map != NULL && map->y < (size_t)y)
		map = map->down;
	return (map);
}

static int		check_piece_line(t_machine *machine, int play_x, int play_y,
						t_map *piece)
{
	size_t	i;
	int		ret;
	t_map	*node;

	i = 0;
	ret = TRUE;
	while (i < machine->piece_width && piece != NULL)
	{
		if (play_y < 0 || play_x + i < 0)
		{
			if ((piece->data & PIECE_PART) == PIECE_PART)
			{
				ret = FALSE;
				break ;
			}
		}
		else
		{
			node = get_node(machine->map, play_x + i, play_y);
			if ((piece->data & PIECE_PART) == PIECE_PART
				&& (node->data & P2_PLAY) == P2_PLAY)
			{
				ret = FALSE;
				break ;
			}
		}
		piece = piece->right;
		i++;
	}
	return (ret);
}

static int		check_piece_pos(t_machine *machine, t_map *piece,
						t_map *piece_play)
{
	size_t	i;
	int		play_x;
	int		play_y;
	int		ret;

	i = 0;
	ret = TRUE;
	play_x = machine->play->x - piece_play->x;
	play_y = machine->play->y - piece_play->y;
	while (i < machine->piece_height && piece != NULL)
	{
		ret = check_piece_line(machine, play_x, play_y + i, piece);
		if (ret == FALSE)
			break ;
		piece = piece->down;
		i++;
	}
	return (ret);
}

static int		check_piece_char(t_machine *machine, t_map *piece)
{
	int		ret;

	ret = FALSE;
	if ((piece->data & PIECE_PART) == PIECE_PART)
	{
		if (check_piece_pos(machine, machine->piece, piece) == TRUE)
		{
			ret = TRUE;
			machine->play_x = machine->play->x - piece->x;
			machine->play_y = machine->play->y - piece->y;
		}
	}
	return (ret);
}

static int		search_line(t_machine *machine, t_map *piece, uint64_t opt)
{
	size_t	i;

	i = 0;
	while (i < machine->piece_height && piece != NULL)
	{
		if ((opt & FROM_UP) == FROM_UP)
		{
			if (check_piece_char(machine, piece) == TRUE)
				return (TRUE);
		}
		piece = piece->down;
		i++;
	}
	if ((opt & FROM_DOWN) == FROM_DOWN)
	{
		while (i >= 0)
		{
			if (check_piece_char(machine, piece) == TRUE)
				return (TRUE) ;
			piece = piece->up;
			i--;
		}
	}
	return (FALSE);
}

void			piece_placement(t_machine *machine, t_map *piece, uint64_t opt)
{
	size_t	i;

	i = 0;
	while (i < machine->piece_width && piece != NULL)
	{
		if ((opt & FROM_LEFT) == FROM_LEFT)
		{
			if (search_line(machine, piece, opt) == TRUE)
				return ;
		}
		piece = piece->right;
		i++;
	}
	if ((opt & FROM_RIGHT) == FROM_RIGHT)
	{
		while (i >= 0)
		{
			if (search_line(machine, piece, opt) == TRUE)
				return ;
			piece = piece->left;
			i--;
		}
	}
}
