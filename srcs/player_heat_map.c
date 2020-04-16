#include "filler.h"

void	player_heat_map(t_machine *machine)
{
	ft_putendl_fd("Get player heat map", 2);
	machine->state = ST_PLAY;
}
