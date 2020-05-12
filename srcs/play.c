#include "filler.h"

#include <stdio.h>

static void		get_opt(t_machine *machine, t_map *node, t_map *objective)
{
	int			diff_x;
	int			diff_y;

	machine->opt = 0;
	diff_x = node->x - objective->x;
	diff_y = node->y - objective->y;
	if (diff_x <= 0)
		machine->opt |= FROM_LEFT;
	else
		machine->opt |= FROM_RIGHT;
	if (diff_y <= 0)
		machine->opt |= FROM_UP;
	else
		machine->opt |= FROM_DOWN;
}

void			play(t_machine *machine, t_list *path_lst)
{
	t_map	*objective;

	if (machine->opponent_played == 1)
	{
		while (path_lst != NULL)
		{
			objective = machine->objective[((t_path*)(path_lst->content))->id];
			if (objective != NULL)
			{
				get_opt(machine, ((t_path*)(path_lst->content))->node, objective);
				if (piece_placement(machine, ((t_path*)(path_lst->content))->node) == TRUE)
					break ;
			}
			path_lst = path_lst->next;
		}
	}
	if (path_lst == NULL || machine->opponent_played == 0)
	{
		get_opt(machine, machine->map, machine->objective[0]);
		retard_play(machine, machine->map);
	}
//	debug_map(machine->map);
//	dprintf(2, "%d %d\n", machine->play_y, machine->play_x);
	ft_printf("%d %d\n", machine->play_y, machine->play_x);
//	usleep(500000);
	machine->state = ST_GET_MAP;
	del_map(&machine->head_piece);
	machine->piece = machine->head_piece;
}
