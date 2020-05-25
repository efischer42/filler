#include "filler.h"

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

static t_map	*get_play_node(t_list *lst)
{
	while (lst != NULL && lst->next != NULL)
	{
		if ((((t_map*)(lst->next->content))->data & P1_PLAY) == FALSE)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

void			play(t_machine *machine, t_list *path_lst)
{
	t_map	*objective;
	t_map	*play_node;

	dprintf(2, "%d %d\n", machine->play_y, machine->play_x);
//	debug_path_lst(machine->path_lst);
	if (machine->last_play != NULL)
	{
		while (path_lst != NULL)
		{
			if (((t_path*)(path_lst->content))->objective != NULL)
			{
				objective = ((t_path*)(path_lst->content))->objective->map;
				if (objective != NULL)
				{
					play_node = get_play_node(((t_path*)(path_lst->content))->lst);
					if (play_node != NULL)
					{
						get_opt(machine, play_node, objective);
						if (piece_placement(machine, play_node) == TRUE)
							break ;
					}
				}
			}
			path_lst = path_lst->next;
		}
	}
	if (path_lst == NULL || machine->last_play == NULL)
	{
		get_opt(machine, machine->map, ((t_objective*)(machine->objective_lst->content))->map);
		if (retard_play(machine, machine->map) == FALSE)
		{
			machine->play_x = 0;
			machine->play_y = 0;
		}
	}
//	debug_map(machine, machine->map);
//	dprintf(2, "%d %d\n", machine->play_y, machine->play_x);
	ft_printf("%d %d\n", machine->play_y, machine->play_x);
//	usleep(500000);
	machine->state = ST_GET_MAP;
	del_map(&machine->head_piece);
	machine->piece = machine->head_piece;
}
