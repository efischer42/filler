#include "filler.h"

void	lexer_parser(t_machine *machine)
{
	t_list	*lst;

	lst = NULL;
	if (get_input(machine) == FAILURE)
		machine->state = ST_ERROR;
	else
	{
		ft_putstr_fd(machine->input, 2);
		lexer(machine, &lst);
		if (machine->state != ST_ERROR)
			parser(machine, lst);
	}
	machine->state = ST_END_TURN;
}
