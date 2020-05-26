/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:10:28 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 12:10:29 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	is_line_char(char c)
{
	int		ret;

	ret = FALSE;
	if (c == '.' || c == 'O' || c == 'X' || c == '*')
		ret = TRUE;
	return (ret);
}

void	get_word(t_machine *machine, char *input, t_token *token, size_t *pos)
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
	else if (is_line_char(input[*pos]) == TRUE)
	{
		token->type = LINE;
		while (is_line_char(input[*pos + i]) == TRUE)
			i++;
		token->value = ft_strndup(input + *pos, i);
		*pos += i;
	}
	else if (input[*pos] == '[')
	{
		token->type = PLAYER_NAME;
		while (input[*pos + i] != ']' && input[*pos + i] != '\0')
			i++;
		if (input[*pos + i] == ']')
			i++;
		token->value = ft_strndup(input + *pos, i);
		*pos += i;
	}
	else
		machine->state = ST_ERROR;
}
