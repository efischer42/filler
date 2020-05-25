#include "filler.h"

static void	set_player_nb(t_machine *machine)
{
	if (((t_token*)(machine->token_lst->content))->type == P1)
	{
		machine->player = P1_CHAR;
		machine->opponent = P2_CHAR;
	}
	else if (((t_token*)(machine->token_lst->content))->type == P2)
	{
		machine->player = P2_CHAR;
		machine->opponent = P1_CHAR;
	}
}

void		get_player(t_machine *machine)
{
	t_list	*head;

	lexer_parser(machine);
	if (machine->state != ST_ERROR)
	{
		head = machine->token_lst;
		while (((t_token*)(machine->token_lst->content))->type != END)
		{
			set_player_nb(machine);
			machine->token_lst = machine->token_lst->next;
		}
		machine->state = ST_GET_MAP;
		ft_lstdel(&head, del_lst);
	}
}
