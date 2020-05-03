#include "filler.h"

/*static int	check_path(t_machine *machine, t_point *objective)
{
	int		ret;

	ret = FALSE;
	while (machine->path_lst != NULL)
	{
		if (((t_path*)(machine->path_lst->content))->id == objective->id)
			break ;
		machine->path_lst = machine->path_lst->next;
	}
	if (machine->path_lst != NULL)
	{
		while (machine->path_lst->path != NULL)
		{
			if ((machine->path_lst->path->map->data & P2_PLAY) == P2_PLAY)
				break ;
			machine->path_lst->path = machine->path_lst->path-next;
		}
		if (machine->path_lst->path == NULL)
			ret = TRUE;
	}
	return (ret);
}*/

static void	set_path(t_machine *machine, t_map *objective)
{
	t_list	*lst_new;
	t_list	*lst;
	t_path	path;

	lst = NULL;
	path.id = objective->id;
	find_path(machine->start, objective, &lst);
	path.lst = lst;
	lst_new = ft_lstnew(&path, sizeof(path));
	ft_lstaddend(&machine->path_lst, lst_new);
}

void		path(t_machine *machine)
{
//	ft_putendl_fd("Path", 2);
//	if (check_path(machine, machine->objective1) == FALSE)
	set_path(machine, machine->objective1);
	machine->state = ST_GET_PIECE;
//	debug_map(machine->map);
}
