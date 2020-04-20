#include "filler.h"

void	debug_map(t_map *map)
{
	char	*print;
	char	*tmp;
	t_map	*head_line;

	tmp = NULL;
	while (map != NULL)
	{
		print = NULL;
		head_line = map;
		while (map->right != NULL)
		{
			tmp = ft_asprintf("[%d, %d] <--> ", map->y, map->x);
			print = ft_join_free(print, tmp, 3);
			map = map->right;
		}
		tmp = ft_asprintf("[%d, %d]", map->y, map->x);
		print = ft_join_free(print, tmp, 3);
		ft_putendl_fd(print, 2);
		ft_strdel(&print);
		map = head_line;
		map = map->down;
	}
}
