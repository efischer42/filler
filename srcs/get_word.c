#include "filler.h"

static int	is_line_char(char c)
{
	int		ret;

	ret = FALSE;
	if (c == '.' || c == 'O' || c == 'o' || c == 'X' || c == 'x' || c == '*')
		ret = TRUE;
	return (ret);
}

void	get_word(t_machine *machine, t_token *token, size_t *pos)
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
	else if (is_line_char(machine->input[*pos]) == TRUE)
	{
		token->type = LINE;
		while (is_line_char(machine->input[*pos + i]) == TRUE)
			i++;
		token->value = ft_strndup(machine->input + *pos, i);
		*pos += i;
	}
	else if (machine->input[*pos] == '[')
	{
		token->type = PLAYER_NAME;
		while (machine->input[*pos + i] != ']' && machine->input[*pos + i] != '\0')
			i++;
		if (machine->input[*pos + i] == ']')
			i++;
		token->value = ft_strndup(machine->input + *pos, i);
		*pos += i;
	}
	else
		machine->state = ST_ERROR;
}
