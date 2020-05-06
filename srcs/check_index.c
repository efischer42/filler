#include "filler.h"

static void	is_index_width_ok(t_machine *machine, char *index_line)
{
	char	c;
	size_t	i;

	i = 0;
	c = '0';
	while (index_line[i] != '\0')
	{
		if (c > '9')
			c = '0';
		if (i > machine->map_width || index_line[i] != c)
		{
			machine->state = ST_ERROR;
			break ;
		}
		c++;
		i++;
	}
}

void		check_index_width(t_machine *machine, t_list *token_lst)
{
	char	*index_line;

	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == NB)
		{
			index_line = ((t_token*)(token_lst->content))->value;
			is_index_width_ok(machine, index_line);
		}
		token_lst = token_lst->next;
	}
}
