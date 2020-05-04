#include "filler.h"

void		turn(t_machine *machine)
{
	debug_map(machine->map);
	debug_map(machine->piece);
	set_objectives(machine);
	if (machine->state != ST_ERROR)
	{
		path(machine);
		if (machine->state != ST_ERROR)
			play(machine);
	}
}
