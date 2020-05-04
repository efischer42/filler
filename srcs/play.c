#include "filler.h"

static void		get_opt(t_machine *machine, t_map *objective)
{
	int			diff_x;
	int			diff_y;

	machine->opt = 0;
	diff_x = machine->play->x - objective->x;
	diff_y = machine->play->y - objective->y;
	if (diff_x <= 0)
		machine->opt |= FROM_LEFT;
	else
		machine->opt |= FROM_RIGHT;
	if (diff_y <= 0)
		machine->opt |= FROM_UP;
	else
		machine->opt |= FROM_DOWN;
}

static void		play_piece(t_machine *machine)
{
	char	*print;

	piece_placement(machine, machine->piece, machine->opt);
	print = ft_asprintf("%d %d\n", machine->play_x, machine->play_y);
	ft_putstr_fd(print, 2);
	ft_strdel(&print);
	ft_printf("%d %d\n", machine->play_y, machine->play_x);
}

void			play(t_machine *machine)
{
	t_path	*objective;

	ft_putendl_fd("Play", 2);
	objective = machine->path_lst->content;
	path_play(machine, objective->lst);
	get_opt(machine, machine->objective1);
	play_piece(machine);
	machine->state = ST_GET_MAP;
	del_map(&machine->head_piece);
	machine->piece = NULL;
}
