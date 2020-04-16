#include "filler.h"

void		get_piece(t_machine *machine)
{
	ft_putendl_fd("Get piece", 2);
	machine->state = ST_OPPONENT_HEAT_MAP;
}
