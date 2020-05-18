#include "filler.h"

void		sort_dead_objective(t_list **lst1, t_list **lst2, t_list **head)
{
	if (((t_objective*)((*lst1)->content))->dead == TRUE
			&& ((t_objective*)((*lst2)->content))->dead == FALSE)
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

void		sort_objective(t_list **lst1, t_list **lst2, t_list **head)
{
	if (*((t_objective*)((*lst1)->content))->map->zone <
			*((t_objective*)((*lst2)->content))->map->zone)
	//		&& *((t_objective*)((*lst2)->content))->map->zone > 0)
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

void		sort_dead_path(t_list **lst1, t_list **lst2, t_list **head)
{
	if (((t_path*)((*lst1)->content))->objective != NULL
			&& ((t_path*)((*lst2)->content))->objective != NULL
			&& ((t_path*)((*lst1)->content))->objective->dead == TRUE
			&& ((t_path*)((*lst2)->content))->objective->dead == FALSE)
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

void		sort_objective_path(t_list **lst1, t_list **lst2, t_list **head)
{
	if (((t_path*)((*lst1)->content))->objective != NULL
			&& ((t_path*)((*lst2)->content))->objective != NULL
			&& *((t_path*)((*lst1)->content))->objective->map->zone <
			*((t_path*)((*lst2)->content))->objective->map->zone)
	//		&& *((t_path*)((*lst2)->content))->objective->map->zone > 0)
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
