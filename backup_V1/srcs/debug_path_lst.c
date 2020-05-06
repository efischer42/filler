#include "filler.h"

void	print_path(t_list *lst)
{
	char	*print;

	while (lst != NULL)
	{
		print = ft_asprintf("x: %d y: %d", ((t_map*)(lst->content))->x,
					((t_map*)(lst->content))->y);
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
		lst = lst->next;
	}
}

void	debug_path_lst(t_list *path_lst)
{
	ft_putendl_fd("\n\n\nDebug path list\n\n\n", 2);
	while (path_lst != NULL)
	{
		print_path(((t_path*)(path_lst->content))->lst);
		path_lst = path_lst->next;
	}
}
