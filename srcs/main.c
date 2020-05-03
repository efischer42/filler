#include "filler.h"

int					main(int ac, char **av)
{
	t_machine	machine;
	char		*line;
	void		(*f_tab[NB_FCT])(t_machine *) = {get_player, get_map,
					set_objectives, path, get_piece, play, error};

	(void)ac;
	line = NULL;
	ft_bzero(&machine, sizeof(machine));
	machine.player_name = av[0];
	machine.state = ST_GET_PLAYER;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		machine.input = line;
		f_tab[machine.state](&machine);
	}
	return (EXIT_SUCCESS);
}
