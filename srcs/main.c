/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:33 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 02:36:47 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	free_data(t_machine *machine)
{
	del_path_lst(machine->path_lst);
	del_map(&machine->map);
	del_mx(&machine);
	del_objective_lst(machine->objective_lst);
}

int		main(int ac, char **av)
{
	t_machine		machine;
	char			*line;
	size_t			i;
	int				ret;
	static void		(*f_tab[NB_FCT])(t_machine *) = {get_player, get_map,
						get_piece};

	(void)ac;
	i = 0;
	line = NULL;
	ft_bzero(&machine, sizeof(machine));
	machine.player_name = av[0];
	while (ret = get_next_line(STDIN_FILENO, &line) > 0)
	{
		machine.input = line;
		while (i < NB_FCT)
		{
			if (f_tab[i](&machine) == FAILURE)
				error(machine);
			i++;
		}
	}
	free_data(&machine);
	return (ret);
}
