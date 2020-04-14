#include "filler.h"

/*static void	get_map_info(t_machine *machine)
{
	char	*line;
	char	**tab;
	char	*print;

	line = NULL;
	get_next_line(STDIN, &line);
	ft_putendl_fd("Get map info:", 2);
	ft_putendl_fd(line, 2);
	tab = ft_split_white_spaces(line);
	if (tab != NULL && ft_tablen(tab) == 3)
	{
		machine->map_height = ft_atoi(tab[1]);
		machine->map_width = ft_atoi(tab[2]);
		print = ft_asprintf("map_height: %u, map_width: %u", machine->map_height,
		machine->map_width);
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
	}
	ft_free_tab(tab);
	ft_strdel(&line);
}*/

void	get_map(t_machine *machine)
{
/*	char	*line;
	size_t	i;

	i = 0;
	line = NULL;
	get_map_info(machine);
*/	ft_putendl_fd("Get map:", 2);
/*	while (i < machine->map_height + 1 && get_next_line(STDIN, &line) == TRUE)
	{
		ft_putendl_fd(line, 2);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
*/	machine->state = ST_GET_PIECE;
}
