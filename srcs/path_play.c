#include "filler.h"

static int	check_player(t_map *map)
{
	int ret;

	ret = FALSE;
	if ((map->data & P1_CHAR) == P1_CHAR)
		ret = TRUE;
	return (ret);
}

void		path_play(t_machine *machine, t_list *lst)
{
	while (lst->next != NULL)
	{
		if (check_player(lst->next->content) == FALSE)
		{
			machine->play = lst->content;
			break ;
		}
		lst = lst->next;
	}
}
