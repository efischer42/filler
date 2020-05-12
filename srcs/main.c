#include "filler.h"

int					main(int ac, char **av)
{
	t_machine	machine;
	char		*line;
	void		(*f_tab[NB_FCT])(t_machine *) = {get_player, get_map, get_piece,
					error};

	(void)ac;
	line = NULL;
	ft_bzero(&machine, sizeof(machine));
	machine.player_name = av[0];
	machine.state = ST_GET_PLAYER;
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		machine.input = line;
		f_tab[machine.state](&machine);
		if (machine.state == ST_ERROR)
			f_tab[machine.state](&machine);
	}
	del_path_lst(machine.path_lst);
	del_map(&machine.map);
	del_mx(&machine);
	del_objective_lst(machine.objective_lst);
	return (EXIT_SUCCESS);
}
