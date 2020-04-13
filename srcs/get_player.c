#include "filler.h"

void	get_player(t_machine *machine)
{
	char		*line;

	(void)machine;
	line = NULL;
	ft_putendl_fd("Get player character", 2);
	get_next_line(STDIN, &line);
	ft_putendl_fd(line, 2);
	ft_strdel(&line);
}
