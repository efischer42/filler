#include "filler.h"

void		data_map(t_map *map, t_map *line, size_t y, size_t x)
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

void		add_map(t_map **line, t_map *new_map)
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

static void	set_corners(t_machine *machine, t_map *map, size_t y, size_t x)
{
	if (y == 0 && x == 0)
		machine->up_left_corner = map;
	else if (y == 0 && x == machine->map_width - 1)
		machine->up_right_corner = map;
	else if (y == machine->map_height - 1 && x == 0)
		machine->bottom_left_corner = map;
	else if (y == machine->map_height - 1 && x == machine->map_width - 1)
		machine->bottom_right_corner = map;
}

static void	generate_line(t_map **new_line, t_map *last_line, size_t y,
					t_machine *machine)
{
	t_map	*new_map;
	size_t	i;

	i = 0;
	while (i < machine->map_width)
	{
		new_map = (t_map*)malloc(sizeof(t_map));
		if (new_map != NULL)
		{
			data_map(new_map, last_line, y, i);
			set_corners(machine, new_map, y, i);
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
	while (i < machine->map_height)
	{
		new_line = NULL;
		generate_line(&new_line, last_line, i, machine);
		last_line = new_line;
		i++;
	}
	machine->map = machine->up_left_corner;
}
