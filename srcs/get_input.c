#include "filler.h"

int		get_input(t_machine *machine)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(STDIN, &line)) == TRUE)
	{
		line = ft_join_free(line, "\n", 1);
		machine->input = ft_join_free(machine->input, line, 3);
	}
	return (ret);
}
