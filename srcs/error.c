/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:09:38 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:09:40 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	error(t_machine *machine)
{
	ft_putendl_fd("Error", 2);
	del_map(&machine->map);
	ft_putstr("0 0\n");
	exit(EXIT_FAILURE);
}
