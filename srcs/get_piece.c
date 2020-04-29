#include "filler.h"

void		get_piece(t_machine *machine)
{
	ft_putendl_fd("Get piece", 2);
	get_piece_dimensions(machine);
	generate_piece(machine);
	fill_piece(machine);
	if (machine->state != ST_ERROR)
		machine->state = ST_PLAY;
}
