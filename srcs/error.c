#include "filler.h"

void	del_line(t_map **map)
{
	if (*map == NULL)
		return ;
	del_line(&(*map)->right);
	free(*map);
	*map = NULL;
}

void	del_map(t_map **map)
{
	if (*map == NULL)
		return ;
	del_map(&(*map)->down);
	del_line(map);
}

void	error(t_machine *machine)
{
	(void)machine;
	ft_putendl_fd("Error", 2);
	del_map(&machine->map);
	ft_putstr("0 0\n");
	exit(EXIT_FAILURE);
}
