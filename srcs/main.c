#include "filler.h"

static void	init_machine(t_machine *machine)
{
	machine->state = ST_GET_PLAYER;
}

int			main(int ac, char **av)
{
	t_machine	*machine;

	(void)ac;
	(void)av;
	machine = NULL;
	init_machine(machine);
	state_machine(machine);
	return (EXIT_SUCCESS);
}
