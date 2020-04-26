#include "filler.h"

static void	x_directions(enum e_direction *dir, t_map *map, t_map *objective)
{
	if (map->x > objective->x)
		dir[0] = LEFT;
	else if (map->x < objective->x)
		dir[0] = RIGHT;
}

static void	y_directions(enum e_direction *dir, t_map *map, t_map *objective)
{
	if (map->y > objective->y)
		dir[0] = UP;
	else if (map->y < objective->y)
		dir[0] = DOWN;
}

static void	x_y_directions(enum e_direction *dir, t_map *map, t_map *objective)
{
	if (map->x > objective->x && map->y > objective->y)
		dir[0] = UP_LEFT;
	else if (map->x > objective->x && map->y < objective->y)
		dir[0] = DOWN_LEFT;
	else if (map->x < objective->x && map->y > objective->y)
		dir[0] = UP_RIGHT;
	else if (map->x < objective->x && map->y < objective->y)
		dir[0] = DOWN_RIGHT;
}

static void	fill_dir(enum e_direction *dir)
{
	enum e_direction	i;
	enum e_direction	dir_count;

	i = 1;
	dir_count = 1;
	while (i < NB_DIR)
	{
		if (i % 2 != 0)
			dir[i] = (dir[0] + dir_count) % NB_DIR;
		else
		{
			dir[i] = (dir[0] + NB_DIR - dir_count) % NB_DIR;
			dir_count++;
		}
		i++;
	}
}

void		set_dir(enum e_direction *dir, t_map *map, t_map *objective)
{
	size_t	diff_x;
	size_t	diff_y;

	if (map != objective)
	{
		diff_x = ft_abs(map->x - objective->x);
		diff_y = ft_abs(map->y - objective->y);
		if (diff_x > diff_y)
			x_directions(dir, map, objective);
		else if (diff_x < diff_y)
			y_directions(dir, map, objective);
		else
			x_y_directions(dir, map, objective);
		fill_dir(dir);
	}
}
