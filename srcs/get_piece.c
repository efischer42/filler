#include "filler.h"

/*static void	get_piece_info(t_machine *machine)
{
	char	*line;
	char	**tab;
	char	*print;

	line = NULL;
	get_next_line(STDIN, &line);
	ft_putendl_fd("Get piece info:", 2);
	ft_putendl_fd(line, 2);
	tab = ft_split_white_spaces(line);
	if (tab != NULL && ft_tablen(tab) == 3)
	{
		machine->piece_height = ft_atoi(tab[1]);
		machine->piece_width = ft_atoi(tab[2]);
		print = ft_asprintf("piece_height: %u, piece_width: %u",
		machine->piece_height, machine->piece_width);
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
	}
	ft_free_tab(tab);
	ft_strdel(&line);
}*/

void		get_piece(t_machine *machine)
{
/*	char	*line;
	size_t	i;

	i = 0;
	line = NULL;
	get_piece_info(machine);
*/	ft_putendl_fd("Get piece", 2);
/*	while (i < machine->piece_height && get_next_line(STDIN, &line) == TRUE)
	{
		ft_putendl_fd(line, 2);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
*/	machine->state = ST_OPPONENT_HEAT_MAP;
}
