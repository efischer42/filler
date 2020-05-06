#include "filler.h"

void	lexer_parser(t_machine *machine)
{
	lexer(machine);
	if (machine->state != ST_ERROR)
		parser(machine, machine->token_lst);
//	debug(machine->token_lst);
	ft_strdel(&machine->input);
}
