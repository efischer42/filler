#include "filler.h"

static int		check_path_objective(t_list *path, enum e_id objective)
{
	int		ret;

	ret = FALSE;
	if (((t_path*)(path->content))->id == objective)
		ret = TRUE;
	return (ret);
}

static int		check_player(t_map *map)
{
	int ret;

	ret = FALSE;
	if ((map->data & P1_CHAR) == P1_CHAR)
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

/*static void		play_piece(t_machine *machine, t_map *map, t_map *objective)
{
	piece_placement(map, objective, machine->piece);
}*/

void			play(t_machine *machine)
{
	t_map		*objective;
	t_map		*map;

	ft_putendl_fd("Play", 2);
	objective = machine->objective1;
	map = path_play(machine->path_lst, objective->id);
//	if (map != NULL)
//		play_piece(machine, map, objective);
	machine->state = ST_END_TURN;
}
