#include "filler.h"

void		sort_objective_lst(t_list **lst1, t_list **lst2, t_list **head)
{
	if (((t_objective*)((*lst1)->content))->last_play_dist >
			((t_objective*)((*lst2)->content))->last_play_dist)
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

void		sort_objectives(t_list **lst1, t_list **lst2, t_list **head)
{
	if (((t_path*)((*lst1)->content))->objective != NULL &&
			((t_path*)((*lst2)->content))->objective != NULL &&
			((t_path*)((*lst1)->content))->objective->last_play_dist >
			((t_path*)((*lst2)->content))->objective->last_play_dist)
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
