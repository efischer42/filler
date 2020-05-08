#include "filler.h"

#include <stdio.h>

static t_map	*get_objective(t_machine *machine, enum e_id id)
{
	t_map	*objective;

	objective = NULL;
	if (id == O1)
		objective = machine->objective1;
	else if (id == O2)
		objective = machine->objective2;
	else if (id == O3)
		objective = machine->objective3;
	else if (id == O4)
		objective = machine->objective4;
	return (objective);
}

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

	while (path_lst != NULL)
	{
		objective = get_objective(machine, ((t_path*)(path_lst->content))->id);
		if (objective != NULL)
		{
			get_opt(machine, ((t_path*)(path_lst->content))->node, objective);
			if (piece_placement(machine, ((t_path*)(path_lst->content))->node) == TRUE)
				break ;
		}
		path_lst = path_lst->next;
	}
	
	if (path_lst == NULL)
	{
		get_opt(machine, machine->map, machine->objective1);
		retard_play(machine, machine->map);
	}

	debug_map(machine->map);
	dprintf(2, "%d %d\n", machine->play_y, machine->play_x);
	ft_printf("%d %d\n", machine->play_y, machine->play_x);
//	usleep(500000);
	machine->state = ST_GET_MAP;
	del_map(&machine->head_piece);
	machine->piece = machine->head_piece;
}
