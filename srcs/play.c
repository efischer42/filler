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

	if (machine->last_play != NULL)
	{
		while (path_lst != NULL)
		{
			if (((t_path*)(path_lst->content))->objective != NULL)
			{
				objective = ((t_path*)(path_lst->content))->objective->map;
				if (objective != NULL)
				{
					get_opt(machine, ((t_path*)(path_lst->content))->node, objective);
					if (piece_placement(machine, ((t_path*)(path_lst->content))->node) == TRUE)
						break ;
				}
			}
			path_lst = path_lst->next;
		}
	}
	if (path_lst == NULL || machine->last_play == NULL)
	{
		get_opt(machine, machine->map, ((t_objective*)(machine->objective_lst->content))->map);
		retard_play(machine, machine->map);
	}
	debug_map(machine, machine->map);
	dprintf(2, "%d %d\n", machine->play_y, machine->play_x);
	ft_printf("%d %d\n", machine->play_y, machine->play_x);
//	usleep(500000);
	machine->state = ST_GET_MAP;
	del_map(&machine->head_piece);
	machine->piece = machine->head_piece;
}
