#include "filler.h"

void	error(t_machine *machine)
{
	ft_putendl_fd("Error", 2);
	del_map(&machine->map);
	ft_putstr("0 0\n");
	exit(EXIT_FAILURE);
}
