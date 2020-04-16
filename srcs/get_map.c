#include "filler.h"

void	get_map(t_machine *machine)
{
	ft_putendl_fd("Get map", 2);
	machine->state = ST_GET_PIECE;
}
