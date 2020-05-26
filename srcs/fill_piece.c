/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_piece.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:00 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:02 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_line(t_list *token_lst, size_t width)
{
	size_t	len;
	int		ret;

	ret = FALSE;
	if (((t_token*)(token_lst->content))->type == LINE)
	{
		len = ft_strlen(((t_token*)(token_lst->content))->value);
		if (len == width)
			ret = TRUE;
	}
	return (ret);
}

static int	fill_piece_line(t_machine *machine, t_list *token_lst)
{
	t_map	*line_head;
	char	*line;
	size_t	i;
	int		ret;

	i = 0;
	ret = check_line(token_lst, machine->piece_width);
	if (ret == TRUE)
	{
		line_head = machine->piece;
		line = ((t_token*)(token_lst->content))->value;
		while (line[i] != '\0')
		{
			if (line[i] == PIECE_CHAR)
				machine->piece->data |= PIECE_PART;
			machine->piece = machine->piece->right;
			i++;
		}
		machine->piece = line_head;
		if (machine->piece->y + 1 == machine->piece_height)
			machine->piece = machine->head_piece;
		else
			machine->piece = machine->piece->down;
	}
	return (ret);
}

void		fill_piece(t_machine *machine, t_list *token_lst)
{
	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == LINE)
			fill_piece_line(machine, token_lst);
		token_lst = token_lst->next;
	}
}
