/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 13:36:20 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 13:36:56 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	del_mx(t_machine *machine)
{
	int	i;

	i = 0;
	while (i < machine->map_height && machine->mx[i] != NULL)
	{
		free(machine->mx[i]);
		i++;
	}
	free(machine->mx);
}

void	del_objective_lst(t_list *objective_lst)
{
	if (objective_lst == NULL)
		return ;
	del_objective_lst(objective_lst->next);
	free(objective_lst->content);
	free(objective_lst);
}
