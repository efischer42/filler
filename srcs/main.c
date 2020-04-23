#include "filler.h"

static t_point		*init_point(void)
{
	t_point		*point;

	point = (t_point*)malloc(sizeof(t_point));
	if (point != NULL)
		ft_bzero(point, sizeof(*point));
	return (point);
}

static void			init_points(t_machine *machine)
{
	machine->start = init_point();
	machine->opponent_start = init_point();
	machine->up_left_corner = init_point();
	machine->up_right_corner = init_point();
	machine->bottom_left_corner = init_point();
	machine->bottom_right_corner = init_point();
	machine->objective1 = init_point();
	machine->objective2 = init_point();
	machine->objective3 = init_point();
}

static t_machine	*init_machine(void)
{
	t_machine	*machine;

	machine = (t_machine*)malloc(sizeof(t_machine));
	ft_bzero(machine, sizeof(*machine));
	init_points(machine);
	machine->state = ST_LEXER_PARSER;
	return (machine);
}

int					main(int ac, char **av)
{
	t_machine	*machine;

	(void)ac;
	(void)av;
	while (1)
	{
		machine = init_machine();
		state_machine(machine);
		ft_putstr("0 0\n");
	}
	return (EXIT_SUCCESS);
}
