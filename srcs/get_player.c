/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:22 by efischer          #+#    #+#             */
/*   Updated: 2020/05/28 14:56:37 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	set_player_nb(t_machine *machine)
{
	if (((t_token*)(machine->token_lst->content))->type == P1)
	{
		machine->player = P1_CHAR;
		machine->opponent = P2_CHAR;
	}
	else if (((t_token*)(machine->token_lst->content))->type == P2)
	{
		machine->player = P2_CHAR;
		machine->opponent = P1_CHAR;
	}
}

static int	check_player_name(t_machine *machine)
{
	char	*braced_player_name;
	int		ret;

	ret = TRUE;
	braced_player_name = ft_asprintf("[%s]", machine->player_name);
	if (ft_strequ(((t_token*)(machine->token_lst->content))->value,
		braced_player_name) != TRUE)
	{
		ret = FALSE;
	}
	ft_strdel(&braced_player_name);
	return (ret);
}

int			get_player(t_machine *machine)
{
	t_list	*head;
	int		ret;

	ret = lexer_parser(machine);
	if (ret == SUCCESS)
	{
		head = machine->token_lst;
		while (((t_token*)(machine->token_lst->content))->type != END)
		{
			set_player_nb(machine);
			if (((t_token*)(machine->token_lst->content))->type == PLAYER_NAME)
			{
				if (check_player_name(machine) == FALSE)
				{
					ret = FAILURE;
					break ;
				}
			}
			machine->token_lst = machine->token_lst->next;
		}
		machine->state++;
		ft_lstdel(&head, del_lst);
	}
	return (ret);
}
