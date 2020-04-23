#include "filler.h"

void	play(t_machine *machine)
{
	ft_putendl_fd("Play", 2);
	set_objectives(machine);
	machine->state = ST_END_TURN;
}
