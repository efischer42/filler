#include "filler.h"

static t_list		*get_new_head(t_list *lst)
{
	t_list	*new_head;

	while (lst != NULL)
	{
		if ((((t_map*)(lst->content))->data & P1_PLAY) == P1_PLAY)
			new_head = lst;
		lst = lst->next;
	}
	return (new_head);
}

void		del_path_first_part(t_machine *machine, t_list *lst, t_list *head)
{
	if (lst == NULL || lst == head)
	{
		((t_path*)(machine->path_lst->content))->lst = lst;
		return ;
	}
	del_path_first_part(machine, lst->next, head);
//	free(lst->content);
	free(lst);
}

void		cut_path(t_machine *machine)
{
	t_list	*head;
	t_list	*new_head;

	head = machine->path_lst;
	while (machine->path_lst != NULL)
	{
		if (((t_path*)(machine->path_lst->content))->objective != NULL)
		{
			new_head = get_new_head(((t_path*)(machine->path_lst->content))->lst);
			if (new_head != ((t_path*)(machine->path_lst->content))->lst)
			{
			//	ft_putendl_fd("Cut path", 2);
				del_path_first_part(machine,
					((t_path*)(machine->path_lst->content))->lst, new_head);
			}
		}
		machine->path_lst = machine->path_lst->next;
	}
	machine->path_lst = head;
}
