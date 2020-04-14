#include "filler.h"

void	play(t_machine *machine)
{
	(void)machine;
	ft_putendl_fd("Play", 2);
	ft_putendl("0 0");
	machine->state = ST_END_TURN;
}
