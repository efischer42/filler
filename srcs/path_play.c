#include "filler.h"

static int	check_path_objective(t_path *path, enum e_id objective)
{
	int		ret;

	ret = FALSE;
	if (path->id == objective)
		ret = TRUE;
	return (ret);
}

static int	check_player(t_map *map)
{
	int ret;

	ret = FALSE;
	if ((map->data & P1_CHAR) == P1_CHAR)
		ret = TRUE;
	return (ret);
}

static void	map_play(t_machine *machine, t_list *lst)
{
	while (lst->next != NULL)
	{
		if (check_player(lst->next->content) == FALSE)
		{
			machine->play = lst->content;
			break ;
		}
		lst = lst->next;
	}
}

void		path_play(t_machine *machine, t_list *path_lst, enum e_id objective)
{
	while (path_lst != NULL)
	{
		if (check_path_objective(path_lst->content, objective) == TRUE)
			break ;
		path_lst = path_lst->next;
	}
	if (path_lst != NULL)
		map_play(machine, ((t_path*)(path_lst->content))->lst);
}
