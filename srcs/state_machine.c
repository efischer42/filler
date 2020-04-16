#include "filler.h"

void	state_machine(t_machine *machine)
{
	void	(*f_tab[NB_FCT])(t_machine *) = {lexer_parser, get_player, get_map,
				get_piece, opponent_heat_map, player_heat_map, play};
	
	while (machine->state != ST_END_TURN && machine->state != ST_ERROR)
		f_tab[machine->state](machine);
}
