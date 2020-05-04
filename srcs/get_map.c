#include "filler.h"

void		get_map(t_machine *machine)
{
	lexer_parser(machine);
	if (machine->state != ST_ERROR)
	{
		if (((t_token*)(machine->token_lst->next->content))->type == PLATEAU)
		{
			if (machine->map == NULL)
				generate_map(machine);
//			else
//				check_map_dimensions(machine->map_width, machine->map_height);
		}
		else if (((t_token*)(machine->token_lst->next->content))->type == SPACE)
			check_index_width(machine, machine->token_lst);
		else if (((t_token*)(machine->token_lst->next->content))->type == NB)
			fill_map(machine, machine->token_lst);
	}
	ft_lstdel(&machine->token_lst, del_lst);
}
