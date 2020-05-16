#include "filler.h"

static int	search_from_up(t_machine *machine, t_map *map, t_map *piece)
{
	while (piece != NULL)
	{
		if ((piece->data & PIECE_PART) == PIECE_PART)
		{
			if (check_piece_pos(machine, map, machine->piece, piece) == TRUE)
				return (TRUE);
		}
		piece = piece->down;
	}
	return (FALSE);
}

static int	search_from_down(t_machine *machine, t_map *map, t_map *piece)
{
	while (piece->down != NULL)
		piece = piece->down;
	while (piece != NULL)
	{
		if ((piece->data & PIECE_PART) == PIECE_PART)
		{
			if (check_piece_pos(machine, map, machine->piece, piece) == TRUE)
				return (TRUE);
		}
		piece = piece->up;
	}
	return (FALSE);
}

static int	search_from_left(t_machine *machine, t_map *map, t_map *piece)
{
	while (piece != NULL)
	{
		if ((machine->opt & FROM_UP) == FROM_UP)
		{
			if (search_from_up(machine, map, piece) == TRUE)
				return (TRUE);
		}
		else if ((machine->opt & FROM_DOWN) == FROM_DOWN)
		{
			if (search_from_down(machine, map, piece) == TRUE)
				return (TRUE);
		}
		piece = piece->right;
	}
	return (FALSE);
}

static int	search_from_right(t_machine *machine, t_map *map, t_map *piece)
{
	while (piece->right != NULL)
		piece = piece->right;
	while (piece != NULL)
	{
		if ((machine->opt & FROM_UP) == FROM_UP)
		{
			if (search_from_up(machine, map, piece) == TRUE)
				return (TRUE);
		}
		else if ((machine->opt & FROM_DOWN) == FROM_DOWN)
		{
			if (search_from_down(machine, map, piece) == TRUE)
				return (TRUE);
		}
		piece = piece->left;
	}
	return (FALSE);
}

int			piece_placement(t_machine *machine, t_map *map)
{
	if ((machine->opt & FROM_LEFT) == FROM_LEFT)
	{
		if (search_from_left(machine, map, machine->piece) == TRUE)
			return (TRUE);
	}
	else if ((machine->opt & FROM_RIGHT) == FROM_RIGHT)
	{
		if (search_from_right(machine, map, machine->piece) == TRUE)
			return (TRUE);
	}
	return (FALSE);
}
