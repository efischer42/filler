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
//	print = ft_asprintf("Piece play %d %d", machine->play_x, machine->play_y);
//	ft_putendl_fd(print, 2);
//	ft_strdel(&print);
	print = ft_asprintf("%d %d\n", machine->play_x, machine->play_y);
	ft_putstr_fd(print, 2);
	ft_strdel(&print);
	ft_printf("%d %d\n", machine->play_x, machine->play_y);
}

void			play(t_machine *machine)
{
	t_map	*objective;

//	ft_putendl_fd("Play", 2);
	objective = machine->objective1;
	path_play(machine, machine->path_lst, objective->id);
	get_opt(machine, objective);
	play_piece(machine);
	machine->state = ST_END_TURN;
}
