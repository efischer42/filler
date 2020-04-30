#include "filler.h"

/*static int		check_path_objective(t_list *path, enum e_id objective)
{
	int		ret;

	ret = FALSE;
	if (((t_path*)(path->content))->id == objective)
		ret = TRUE;
	return (ret);
}

static int		check_player(t_path *path)
{
	int ret;

	ret = FALSE;
	if ((((t_map*)(path->map))->data & P1_CHAR) == P1_CHAR)
		ret = TRUE;
	return (ret);
}

static t_map	*map_play(t_list *lst)
{
	while (lst->next != NULL)
	{
		if (check_player(lst->next->content) == FALSE)
			break ;
		lst = lst->next;
	}
	return (lst->content);
}

static t_map	*path_play(t_list *path_lst, enum e_id objective)
{
	t_map	*map;

	map = NULL;
	while (path_lst != NULL)
	{
		if (check_path_objective(path_lst->content, objective) == TRUE)
			break ;
		path_lst = path_lst->next;
	}
	if (path_lst != NULL)
		map = map_play(path_lst->content);
	return (map);
}

static int		check_piece_char(uint64_t data)
{
	int		ret;

	ret = FALSE;
	if ((data & PIECE_PART) == PIECE_PART)
		ret = TRUE;
	return (ret);
}

static t_map	*search_line(t_machine *machine, t_map *piece, uint64_t opt)
{
	size_t	i;

	i = 0;
	while (i < machine->piece_height && piece != NULL)
	{
		if ((opt & FROM_UP) == FROM_UP)
		{
			if (check_piece_char(piece->data) == TRUE)
				break ;
		}
		piece = piece->down;
		i++;
	}
	if ((opt & FROM_DOWN) == FROM_DOWN)
	{
		while (i > 0)
		{
			if (check_piece_char(piece->data) == TRUE)
				break ;
			piece = piece->up;
			i--;
		}
	}
	return (piece);
}

static t_map	*search_column(t_machine *machine, t_map *piece, uint64_t opt)
{
	t_map	*point;
	size_t	i;

	i = 0;
	while (i < machine->piece_width && piece != NULL)
	{
		if ((opt & FROM_LEFT) == FROM_LEFT)
			point = search_line(machine, machine->piece, opt);
		if (point != NULL)
			break ;
		piece = piece->right;
		i++;
	}
	if ((opt & FROM_RIGHT) == FROM_RIGHT)
	{
		while (i > 0)
		{
			point = search_line(machine, machine->piece, opt);
			if (point != NULL)
				break ;
			piece = piece->left;
			i--;
		}
	}
	return (point);
}

static t_map	*piece_placement(t_machine *machine, t_map *map, t_map *objective)
{
	int			diff_x;
	int			diff_y;
	uint64_t	opt;

	opt = 0;
	diff_x = map->x - objective->x;
	diff_y = map->y - objective->y;
	if (diff_x <= 0)
		opt |= FROM_LEFT;
	else
		opt |= FROM_RIGHT;
	if (diff_y <= 0)
		opt |= FROM_UP;
	else
		opt |= FROM_DOWN;
	ft_putendl_fd("debug play", 2);
	debug_map(machine->head_piece);
	return (search_column(machine, machine->head_piece, opt));
}

static void		play_piece(t_machine *machine, t_map *map, t_map *objective)
{
	t_map	*piece;
	char	*print;

	piece = piece_placement(machine, map, objective);
	if (piece != NULL)
	{
		print = ft_asprintf("Play on %d %d", piece->x, piece->y);
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
	}
}*/

void			play(t_machine *machine)
{
//	t_map		*objective;
//	t_map		*map;

	ft_putendl_fd("Play", 2);
//	objective = machine->objective1;
//	map = path_play(machine->path_lst, objective->id);
//	if (map != NULL)
//		play_piece(machine, map, objective);
	machine->state = ST_END_TURN;
}
