/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:28 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 15:45:16 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	is_map_line_char(char c)
{
	int		ret;

	ret = FALSE;
	if (c == '.' || c == 'O' || c == 'X')
		ret = TRUE;
	return (ret);
}

static int	is_piece_line_char(char c)
{
	int		ret;

	ret = FALSE;
	if (c == '.' || c == '*')
		ret = TRUE;
	return (ret);
}

static void	get_player_name(t_machine *machine, t_token *token, size_t *pos,
				size_t i)
{
	token->type = PLAYER_NAME;
	while (machine->input[*pos + i] != ']' && machine->input[*pos + i] != '\0')
		i++;
	if (machine->input[*pos + i] == ']')
		i++;
	token->value = ft_strndup(machine->input + *pos, i);
	*pos += i;
}

static void	get_line(t_machine *machine, t_token *token, size_t *pos, size_t i)
{
	if (ft_strlen(machine->input + *pos) == (size_t)machine->map_width)
	{
		token->type = MAP_LINE;
		while (is_map_line_char(machine->input[*pos + i]) == TRUE)
			i++;
		token->value = ft_strndup(machine->input + *pos, i);
		*pos += i;
	}
	else if (ft_strlen(machine->input + *pos) == (size_t)machine->piece_width)
	{
		token->type = PIECE_LINE;
		while (is_piece_line_char(machine->input[*pos + i]) == TRUE)
			i++;
		token->value = ft_strndup(machine->input + *pos, i);
		*pos += i;
	}
	else
		(*pos)++;
}

int			get_word(t_machine *machine, t_token *token, size_t *pos)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(machine->input[*pos]) == TRUE)
	{
		token->type = NB;
		while (ft_isdigit(machine->input[*pos + i]) == TRUE)
			i++;
		token->value = ft_strndup(machine->input + *pos, i);
		*pos += i;
	}
	else if (is_map_line_char(machine->input[*pos]) == TRUE
		|| is_piece_line_char(machine->input[*pos]) == TRUE)
	{
		get_line(machine, token, pos, i);
	}
	else if (machine->input[*pos] == '[')
		get_player_name(machine, token, pos, i);
	else
		return (FAILURE);
	return (SUCCESS);
}
