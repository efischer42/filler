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

void		fill_map(t_machine *machine)
{
	while (((t_token*)(machine->token_lst->content))->type != END)
	{
		if (((t_token*)(machine->token_lst->content))->type == NB)
			check_index_height(machine->token_lst, machine->map->y);
		else if (((t_token*)(machine->token_lst->content))->type == LINE)
			fill_line(machine);
		machine->token_lst = machine->token_lst->next;
	}
	if (machine->map->y + 1 == machine->map_height)
	{
		machine->state = ST_GET_PIECE;
		machine->map = machine->up_left_corner;
		debug_map(machine->map);
	}
}
