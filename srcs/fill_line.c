#include "filler.h"

static int	check_line(t_list *token_lst, size_t width)
{
	size_t	len;
	int		ret;

	ret = FALSE;
	if (((t_token*)(token_lst->content))->type == LINE)
	{
		len = ft_strlen(((t_token*)(token_lst->content))->value);
		if (len == width)
			ret = TRUE;
	}
	return (ret);
}

static void	init_dir_tab(t_map *map, t_map **dir_tab)
{
	ft_bzero(dir_tab, sizeof(*dir_tab));
	if (map != NULL)
	{
		dir_tab[0] = map->up;
		dir_tab[1] = map->right;
		dir_tab[2] = map->down;
		dir_tab[3] = map->left;
	}
}

static void	fill_side(t_map *map, size_t dir, size_t dist)
{
	t_map	*dir_tab[NB_MAIN_DIR];
	size_t	i;

	i = 0;
	while (i < dist)
	{
		init_dir_tab(map, dir_tab);
		map = dir_tab[dir];
		if (map == NULL || map->data != 0)
			break ;
		if (map->data == 0)
			map->data |= DANGER_ZONE;
		i++;
	}
}

static void	fill_danger_zone(t_map *map, size_t dist, size_t pos)
{
	t_map	*dir_tab[NB_MAIN_DIR];
	size_t	i;
	size_t	dir;

	i = 0;
	dir = (pos + 1) % NB_MAIN_DIR;
	while (i + 1 < dist)
	{
		init_dir_tab(map, dir_tab);
		map = dir_tab[pos];
		if (map == NULL || map->data != 0)
			break ;
		if (map->data == 0)
			map->data |= DANGER_ZONE;
		i++;
		fill_side(map, dir, dist - i);
	}
}

static void	fill_opponent_zone(t_machine *machine)
{	
	size_t	i;

	i = 0;
	while (i < NB_MAIN_DIR)
	{
		fill_danger_zone(machine->map, machine->dist, i);
		i++;
	}
}

static void	fill_map_data(t_machine *machine, char c)
{
	if (c == P1_CHAR || c == P1_CHAR_LAST)
		machine->map->data |= P1_PLAY;
	else if (c == P2_CHAR || c == P2_CHAR_LAST)
	{
		machine->map->data |= P2_PLAY;
		fill_opponent_zone(machine);
	}
}

int			fill_line(t_machine *machine, t_list *token_lst)
{
	t_map	*line_head;
	char	*line;
	size_t	i;
	int		ret;

	i = 0;
	ret = check_line(token_lst, machine->map_width);
	if (ret == TRUE)
	{
		line_head = machine->map;
		line = ((t_token*)(token_lst->content))->value;
		while (line[i] != '\0')
		{
			fill_map_data(machine, line[i]);
			machine->map = machine->map->right;
			i++;
		}
		machine->map = line_head;
		if (machine->map->down != NULL)
			machine->map = machine->map->down;
	}
	return (ret);
}