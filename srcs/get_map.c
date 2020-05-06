#include "filler.h"

static void	check_map_dimensions(t_machine *machine, t_list *token_lst)
{
	int		nb_count;
	size_t	width;
	size_t	height;

	nb_count = 0;
	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == NB)
		{
			if (nb_count == 0)
			{
				height = ft_atoi(((t_token*)(token_lst->content))->value);
				if (machine->map_height != height)
					break;
			}
			else
			{
				width = ft_atoi(((t_token*)(token_lst->content))->value);
				if (machine->map_width != width)
					break;
			}
			nb_count++;
		}
		token_lst = token_lst->next;
	}
	if (((t_token*)(token_lst->content))->type != END)
	{
		ft_putendl_fd("Map dimension ERROR", 2);
		machine->state = ST_ERROR;
	}
	token_lst = token_lst->next;
}

void		get_map(t_machine *machine)
{
	lexer_parser(machine);
	if (machine->state != ST_ERROR)
	{
		if (((t_token*)(machine->token_lst->next->content))->type == PLATEAU)
		{
			if (machine->map == NULL)
				generate_map(machine);
			else
				check_map_dimensions(machine, machine->token_lst);
		}
		else if (((t_token*)(machine->token_lst->next->content))->type == SPACE)
			check_index_width(machine, machine->token_lst);
		else if (((t_token*)(machine->token_lst->next->content))->type == NB)
			fill_map(machine, machine->token_lst);
	}
	ft_lstdel(&machine->token_lst, del_lst);
}
