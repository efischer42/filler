#include "filler.h"

static int	is_index_width_ok(t_machine *machine, char *index_line)
{
	int		ret;
	char	c;
	size_t	i;

	i = 0;
	c = '0';
	ret = TRUE;
	while (index_line[i] != '\0')
	{
		if (c > '9')
			c = '0';
		if (i > machine->map_width || index_line[i] != c)
		{
			ret = FALSE;
			machine->state = ST_ERROR;
			break ;
		}
		c++;
		i++;
	}
	return (ret);
}

int			check_index_width(t_machine *machine)
{
	char	*index_line;
	int		ret;

	ret = FALSE;
	while (((t_token*)(machine->token_lst->content))->type != NEW_LINE)
	{
		if (((t_token*)(machine->token_lst->content))->type == NB)
		{
			index_line = ((t_token*)(machine->token_lst->content))->value;
			ret = is_index_width_ok(machine, index_line);
		}
		machine->token_lst = machine->token_lst->next;
	}
	machine->token_lst = machine->token_lst->next;
	return (ret);
}
