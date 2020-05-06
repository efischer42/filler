#include "filler.h"

void	del_line(t_map **map)
{
	if (*map == NULL)
		return ;
	del_line(&(*map)->right);
	free(*map);
	*map = NULL;
}

void	del_map(t_map **map)
{
	if (*map == NULL)
		return ;
	del_map(&(*map)->down);
	del_line(map);
}

void	del_lst(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_token*)(content))->value);
	free(content);
}
