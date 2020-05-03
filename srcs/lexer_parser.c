#include "filler.h"

void	lexer_parser(t_machine *machine)
{
	char	*input;

	input = NULL;
	if (get_input(&input) == TRUE && input != NULL)
	{
		ft_putendl_fd("//////////INPUT//////////", 2);
		ft_putstr_fd(input, 2);
		lexer(machine, input);
		if (machine->state != ST_ERROR)
		{
			machine->head = machine->token_lst;
			parser(machine);
			machine->token_lst = machine->head;
			if (machine->state != ST_ERROR)
			{
				if (((t_token*)(machine->token_lst->next->content))->type == PLATEAU)
					machine->state = ST_GET_MAP;
				else
					machine->state = ST_GET_PLAYER;
			}
		}
	}
	else if (input != NULL)
		machine->state = ST_ERROR;
	ft_strdel(&input);
}
