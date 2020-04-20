#include "filler.h"

static void	set_player_nb(t_machine *machine)
{
	if (((t_token*)(machine->lst->content))->type == P1)
	{
		machine->player = P1_CHAR;
		machine->player_last = P1_CHAR_LAST;
		machine->opponent = P2_CHAR;
		machine->opponent_last = P2_CHAR_LAST;
	}
	else if (((t_token*)(machine->lst->content))->type == P2)
	{
		machine->player = P2_CHAR;
		machine->player_last = P2_CHAR_LAST;
		machine->opponent = P1_CHAR;
		machine->opponent_last = P1_CHAR_LAST;
	}
}

static int	check_player_name(t_machine *machine)
{
	int		ret;

	ret = FAILURE;
	if (ft_strstr(((t_token*)(machine->lst->content))->value, EXEC_NAME) != NULL)
		ret = SUCCESS;
	return (ret);
}

void		get_player(t_machine *machine)
{
	ft_putendl_fd("Get player character", 2);
	machine->state = ST_ERROR;
	while (((t_token*)(machine->lst->content))->type != NEW_LINE)
	{
		set_player_nb(machine);
		if (((t_token*)(machine->lst->content))->type == PLAYER_NAME)
		{
			if (check_player_name(machine) == SUCCESS)
				machine->state = ST_GET_MAP;
		}
		machine->lst = machine->lst->next;
	}
	machine->lst = machine->lst->next;
}
