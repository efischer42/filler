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

void	del_path(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
	((t_map*)(content))->data &= ~DEBUG;
	//free(content);
}

void	del_path_lst(t_list *path_lst)
{
	if (path_lst == NULL)
		return ;
	del_path_lst(path_lst->next);
	ft_lstdel(&((t_path*)(path_lst->content))->lst, del_path);
	free(path_lst);
	path_lst = NULL;
}
