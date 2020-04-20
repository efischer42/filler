#include "filler.h"

void		get_map(t_machine *machine)
{
	ft_putendl_fd("Get map", 2);
	get_map_dimensions(machine);
	if (check_index_width(machine) == TRUE)
	{
		generate_map(machine);
		if (machine->map == NULL)
			machine->state = ST_ERROR;
		fill_map(machine);
	}
	if (machine->state != ST_ERROR)
		machine->state = ST_GET_PIECE;
}
