#include "filler.h"

static void	generate_line(t_map **new_line, t_map *last_line, size_t y,
					t_machine *machine)
{
	t_map	*new_piece;
	size_t	i;

	i = 0;
	while (i < machine->piece_width)
	{
		new_piece = (t_map*)malloc(sizeof(t_map));
		if (new_piece != NULL)
		{
			data_map(new_piece, last_line, y, i);
			if (last_line != NULL)
				last_line = last_line->right;
			add_map(new_line, new_piece);
		}
		i++;
	}
}

void		generate_piece(t_machine *machine)
{
	t_map	*new_line;
	t_map	*last_line;
	size_t	i;

	i = 0;
	last_line = NULL;
	while (i < machine->piece_height)
	{
		new_line = NULL;
		generate_line(&new_line, last_line, i, machine);
		last_line = new_line;
		if (machine->piece == NULL)
			machine->piece = new_line;
		i++;
	}
	machine->head_piece = machine->piece;
}
