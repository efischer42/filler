/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:09:16 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:09:26 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static t_list	*get_new_head(t_list *lst)
{
	t_list	*new_head;

	new_head = NULL;
	while (lst != NULL)
	{
		if ((((t_map*)(lst->content))->data & P1_PLAY) == P1_PLAY)
			new_head = lst;
		lst = lst->next;
	}
	return (new_head);
}

void			cut_path(t_path *path)
{
	t_list	*new_head;

	new_head = get_new_head(path->lst);
	ft_lstdelto(&path->lst, new_head, del_path);
	path->path_len = ft_lstlen(path->lst);
}
