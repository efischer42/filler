/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:28 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 02:44:01 by efischer         ###   ########.fr       */
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

static void	get_player_name(t_token *token, char *input, size_t *pos, size_t i)
{
	token->type = PLAYER_NAME;
	while (input[*pos + i] != ']' && input[*pos + i] != '\0')
		i++;
	if (input[*pos + i] == ']')
		i++;
	token->value = ft_strndup(input + *pos, i);
	*pos += i;
}

void		get_word(t_machine *machine, char *input, t_token *token,
				size_t *pos)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(input[*pos]) == TRUE)
	{
		token->type = NB;
		while (ft_isdigit(input[*pos + i]) == TRUE)
			i++;
		token->value = ft_strndup(input + *pos, i);
		*pos += i;
	}
	else if (is_map_line_char(input[*pos]) == TRUE)
	{
		token->type = MAP_LINE;
		while (is_map_line_char(input[*pos + i]) == TRUE)
			i++;
		token->value = ft_strndup(input + *pos, i);
		*pos += i;
	}
	else if (is_piece_line_char(input[*pos]) == TRUE)
	{
		token->type = PIECE_LINE;
		while (is_piece_line_char(input[*pos + i]) == TRUE)
			i++;
		token->value = ft_strndup(input + *pos, i);
		*pos += i;
	}
	else if (input[*pos] == '[')
		get_player_name(token, input, pos, i);
	else
		machine->state = ST_ERROR;
}
