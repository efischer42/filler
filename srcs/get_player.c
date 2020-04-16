#include "filler.h"

void	get_player(t_machine *machine)
{
	ft_putendl_fd("Get player character", 2);
	machine->state = ST_GET_MAP;
}
