#include "filler.h"

static void	check_data(t_map *objective, uint64_t data)
{
	if ((data & P1_PLAY) == P1_PLAY || (data & P2_PLAY) == P2_PLAY
		|| (data & DANGER_ZONE) == DANGER_ZONE)
	{
		objective->id = DEAD;
	}
}

static void	check_objectives(t_machine *machine)
{
	check_data(machine->objective1, machine->objective1->data);
	check_data(machine->objective2, machine->objective2->data);
	check_data(machine->objective3, machine->objective3->data);
	check_data(machine->objective4, machine->objective4->data);
}

void		play_turn(t_machine *machine)
{
//	debug_map(machine->map);
//	debug_map(machine->piece);
	if (machine->objective1 == NULL)
		set_objectives(machine);
	else
		check_objectives(machine);
	if (machine->state != ST_ERROR)
	{
		path(machine, machine->map);
		if (machine->state != ST_ERROR)
			play(machine, machine->path_lst);
		machine->map = machine->up_left_corner;
	}
}
