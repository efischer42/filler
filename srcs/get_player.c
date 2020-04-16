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
	char	*print;

	print = NULL;
	ft_putendl_fd("Get player character", 2);
	while (((t_token*)(machine->lst->content))->type != PLAYER_NAME)
	{
		set_player_nb(machine);
		machine->lst = machine->lst->next;
	}
	if (check_player_name(machine) == SUCCESS)
		machine->state = ST_GET_MAP;
	else
		machine->state = ST_ERROR;
	print = ft_asprintf("player: %c, player_last: %c, opponent: %c, opponent_last: %c", machine->player, machine->player_last, machine->opponent, machine->opponent_last);
	ft_putendl_fd(print, 2);
}
