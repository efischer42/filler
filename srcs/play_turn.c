#include "filler.h"

void		play_turn(t_machine *machine)
{
//	debug_map(machine->map);
//	debug_map(machine->piece);
	if (machine->objective1 == NULL)
		set_objectives(machine);
	if (machine->state != ST_ERROR)
	{
//		path(machine, machine->map);
//		if (machine->state != ST_ERROR)
			play(machine, machine->path_lst);
		machine->map = machine->up_left_corner;
	}
}
