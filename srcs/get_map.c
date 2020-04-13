#include "filler.h"

void	get_map(t_machine *machine)
{
	char	*line;

	(void)machine;
	line = NULL;
	get_next_line(STDIN, &line);
	ft_putendl_fd("Get map info:", 2);
	ft_putendl_fd(line, 2);
	ft_strdel(&line);
	ft_putendl_fd("Get map:", 2);
	while (get_next_line(STDIN, &line) == TRUE)
	{
		ft_putendl_fd(line, 2);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
