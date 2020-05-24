#include "filler.h"

void	print_path(t_list *lst)
{
	if (lst != NULL)
	{
		ft_putendl_fd("", 2);
		dprintf(2, "x: %d y: %d\n", ((t_map*)(lst->content))->x,
				((t_map*)(lst->content))->y);
		while (lst->next != NULL)
			lst = lst->next;
		dprintf(2, "x: %d y: %d\n", ((t_map*)(lst->content))->x,
			((t_map*)(lst->content))->y);
	}
}

void	debug_path_lst(t_list *path_lst)
{
	ft_putendl_fd("\nDebug path list\n", 2);
	while (path_lst != NULL)
	{
		print_path(((t_path*)(path_lst->content))->lst);
		path_lst = path_lst->next;
	}
}

void	debug_objective_lst(t_list *objective_lst)
{
	ft_putendl_fd("\nDebug objective list\n", 2);
	while (objective_lst != NULL)
	{
		dprintf(2, "objective x: %d y: %d dead: %d\n",
			((t_objective*)(objective_lst->content))->map->x,
			((t_objective*)(objective_lst->content))->map->y,
			((t_objective*)(objective_lst->content))->dead);
		objective_lst = objective_lst->next;
	}
}
