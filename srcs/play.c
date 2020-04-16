#include "filler.h"

void	play(t_machine *machine)
{
	ft_putendl_fd("Play", 2);
	machine->state = ST_END_TURN;
}
