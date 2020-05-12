#include "filler.h"

void		sort_obj1(t_list **lst1, t_list **lst2, t_list **head)
{
	if (((t_path*)((*lst1)->content))->id >
			((t_path*)((*lst2)->content))->id)
	{
		*head = *lst2;
		*lst2 = (*lst2)->next;
	}
	else
	{
		*head = *lst1;
		*lst1 = (*lst1)->next;
	}
}

void		sort_len_path(t_list **lst1, t_list **lst2, t_list **head)
{
	if (((t_path*)((*lst1)->content))->path_len >
			((t_path*)((*lst2)->content))->path_len)
	{
		*head = *lst2;
		*lst2 = (*lst2)->next;
	}
	else
	{
		*head = *lst1;
		*lst1 = (*lst1)->next;
	}
}
