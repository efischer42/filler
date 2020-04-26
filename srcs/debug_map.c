#include "filler.h"

static char	*get_play(uint64_t played)
{
	char	*play;

	play = ".";
	if ((played & PATH) == PATH)
		play = ">";
	else if ((played & LAST_PLAY) == LAST_PLAY)
	{
		if ((played & P1_PLAY) == P1_PLAY)
			play = "o";
		else if ((played & P2_PLAY) == P2_PLAY)
			play = "x";
	}
	else
	{
		if ((played & P1_PLAY) == P1_PLAY)
			play = "O";
		else if ((played & P2_PLAY) == P2_PLAY)
			play = "X";
	}
	return (play);
}

void		debug_map(t_map *map)
{
	char	*print;
	char	*tmp;
	t_map	*head_line;
	char	*play;

	tmp = NULL;
	while (map != NULL)
	{
		print = NULL;
		head_line = map;
		while (map->right != NULL)
		{
			play = get_play(map->played);
			tmp = ft_asprintf("%s ", play);
			print = ft_join_free(print, tmp, 3);
			map = map->right;
		}
		tmp = ft_asprintf("%s", play);
		print = ft_join_free(print, tmp, 3);
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
		map = head_line;
		map = map->down;
	}
}
