#include "filler.h"

static t_machine	*init_machine(void)
{
	t_machine *machine;

	machine = (t_machine*)malloc(sizeof(t_machine));
	ft_bzero(machine, sizeof(*machine));
	machine->state = ST_LEXER_PARSER;
	return (machine);
}

int					main(int ac, char **av)
{
	t_machine	*machine;

	(void)ac;
	(void)av;
	machine = init_machine();
	state_machine(machine);
	return (EXIT_SUCCESS);
}
