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
			if ((machine->path_lst->path->map->played & P2_PLAY) == P2_PLAY)
				break ;
			machine->path_lst->path = machine->path_lst->path-next;
		}
		if (machine->path_lst->path == NULL)
			ret = TRUE;
	}
	return (ret);
}

static void	set_dir(enum e_direction *dir, t_machine *machine, t_point *objective)
{
	
}

int			find_path(t_machine *machine, t_point *objective, t_path *new_path)
{
	enum e_direction	dir[NB_DIR];

	set_dir(dir, machine, objective);
}

static void	set_path(t_machine *machine, t_point *objective)
{
	t_lst	*lst_new;
	t_path	*new_path;

	new_path = NULL;
	find_path(machine, objective, new_path);
	lst_new = ft_lstnew(new_path, sizeof(*new_path));
	ft_lstaddend(&machine->path_lst, lst_new);
}*/

void	path(t_machine *machine)
{
	ft_putendl_fd("Path", 2);
//	if (check_path(machine, machine->objective1) == FALSE)
//		set_path(machine, machine->objective1);
	machine->state = ST_GET_PIECE;
}
