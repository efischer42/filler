/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:33 by efischer          #+#    #+#             */
/*   Updated: 2020/05/28 15:12:17 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	free_data(t_machine *machine)
{
	del_path_lst(machine->path_lst);
	del_map(&machine->map);
	del_mx(machine);
	del_objective_lst(machine->objective_lst);
}

int			main(int ac, char **av)
{
	t_machine		machine;
	char			*line;
	int				ret;
	static int		(*f_tab[NB_FCT])(t_machine *) = {get_player, get_plateau,
						get_map, get_piece_dimensions, get_piece};

	(void)ac;
	line = NULL;
	ft_bzero(&machine, sizeof(machine));
	machine.player_name = av[0];
	while ((ret = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		ft_putendl_fd(line, 2);
		machine.input = line;
		if (f_tab[machine.state](&machine) == FAILURE)
			error(&machine);
	}
	if (machine.state == ST_GET_PIECE)
		error(&machine);
	free_data(&machine);
	return (ret);
}
