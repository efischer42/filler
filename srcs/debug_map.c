#include "filler.h"

static char	*get_play(uint64_t data)
{
	char	*play;

	play = ".";
	if ((data & PATH) == PATH)
		play = ">";
	else if ((data & DANGER_ZONE) == DANGER_ZONE)
			play = "!";
	else if ((data & P1_PLAY) == P1_PLAY)
			play = "O";
	else if ((data & P2_PLAY) == P2_PLAY)
			play = "X";
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
		while (map != NULL)
		{
			play = get_play(map->data);
			tmp = ft_asprintf("%s ", play);
			print = ft_join_free(print, tmp, 3);
			map = map->right;
		}
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
		map = head_line;
		map = map->down;
	}
}
