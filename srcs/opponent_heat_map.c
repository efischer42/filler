#include "filler.h"

void	opponent_heat_map(t_machine *machine)
{
	ft_putendl_fd("Get opponent heat map", 2);
	machine->state = ST_PLAYER_HEAT_MAP;
}
