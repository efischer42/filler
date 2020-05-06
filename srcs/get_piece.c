#include "filler.h"

void		get_piece(t_machine *machine)
{
	lexer_parser(machine);
	if (machine->state != ST_ERROR)
	{
		if (((t_token*)(machine->token_lst->next->content))->type == PIECE)
		{
			get_piece_dimensions(machine, machine->token_lst);
			if (machine->piece == NULL)
			{
				ft_putendl_fd("Generate piece", 2);
				generate_piece(machine);
			}
		}
		else if (((t_token*)(machine->token_lst->next->content))->type == LINE)
		{
			fill_piece(machine, machine->token_lst);
			if (machine->piece == machine->head_piece)
				play_turn(machine);
		}
	}
	ft_lstdel(&machine->token_lst, del_lst);
}
