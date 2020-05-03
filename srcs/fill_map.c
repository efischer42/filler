#include "filler.h"

static int	check_index_height(t_list *token_lst, size_t i)
{
	size_t	len;
	size_t	nb;
	int		ret;

	ret = FALSE;
	if (((t_token*)(token_lst->content))->type == NB)
	{
		len = ft_strlen(((t_token*)(token_lst->content))->value);
		if (len == INDEX_HEIGHT_FORMAT)
		{
			nb = ft_atoi(((t_token*)(token_lst->content))->value);
			if (nb == i)
				ret = TRUE;
		}
	}
	return (ret);
}

static void	process_line(t_machine *machine, size_t i)
{
	while (((t_token*)(machine->token_lst->content))->type != NEW_LINE)
	{
		if (((t_token*)(machine->token_lst->content))->type == NB)
			check_index_height(machine->token_lst, i);
		else if (((t_token*)(machine->token_lst->content))->type == LINE)
			fill_line(machine);
		machine->token_lst = machine->token_lst->next;
	}
}

void		fill_map(t_machine *machine)
{
	size_t	i;

	i = 0;
	while (i < machine->map_height)
	{
		process_line(machine, i);
		machine->token_lst = machine->token_lst->next;
		i++;
	}
	machine->map = machine->up_left_corner;
//	debug_map(machine->map);
}
