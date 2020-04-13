#include "filler.h"

int		main(int ac, char **av)
{
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
	get_next_line(STDIN, &line);
	ft_putendl_fd("");
	while (get_next_line(STDIN, &line) == TRUE)
	{
		ft_putendl_fd(line, 2);
		ft_strdel(&line);
	}
	return (EXIT_SUCCESS);
}
