#include "filler.h"

void	lexer_parser(t_machine *machine)
{
	t_list	*head;
	char	*input;

	input = NULL;
	if (get_input(&input) == SUCCESS)
	{
		ft_putstr_fd(input, 2);
		lexer(machine, input);
		if (machine->state != ST_ERROR)
		{
			head = machine->lst;
			parser(machine);
			machine->lst = head;
			if (machine->state != ST_ERROR)
			{
				if (((t_token*)(machine->lst->next->content))->type == PLATEAU)
					machine->state = ST_GET_MAP;
				else
					machine->state = ST_GET_PLAYER;
			}
		}
	}
	else
		machine->state = ST_ERROR;
	ft_strdel(&input);
}
