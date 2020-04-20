#include "filler.h"

static void	data_map(t_map *map, t_map *line, size_t y, size_t x)
{
	ft_bzero(map, sizeof(*map));
	map->x = x;
	map->y = y;
	if (line != NULL)
	{
		line->down = map;
		map->up = line;
	}
}

static void	add_map(t_map **line, t_map *new_map)
{
	t_map	*head;

	if (line != NULL && new_map != NULL)
	{
		head = *line;
		if (*line == NULL)
			*line = new_map;
		else
		{
			while ((*line)->right != NULL)
				*line = (*line)->right;
			(*line)->right = new_map;
			new_map->left = *line;
			*line = head;
		}
	}
}

static void	generate_line(t_map **new_line, t_map *last_line, size_t y, size_t width)
{
	t_map	*new_map;
	size_t	i;

	i = 0;
	while (i < width)
	{
		new_map = (t_map*)malloc(sizeof(t_map));
		if (new_map != NULL)
		{
			data_map(new_map, last_line, y, i);
			if (last_line != NULL)
				last_line = last_line->right;
			add_map(new_line, new_map);
		}
		i++;
	}
}

void		generate_map(t_machine *machine)
{
	t_map	*new_line;
	t_map	*last_line;
	size_t	i;

	i = 0;
	last_line = NULL;
	ft_putendl_fd("create_map", 2);
	while (i < machine->map_height)
	{
		new_line = NULL;
		generate_line(&new_line, last_line, i, machine->map_width);
		if (machine->map == NULL)
		{
			machine->map = new_line;
			machine->map_head = machine->map;
		}
		last_line = new_line;
		i++;
	}
}
