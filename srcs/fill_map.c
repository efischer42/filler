#include "filler.h"

static int	check_index_height(t_list *lst, size_t i)
{
	size_t	len;
	size_t	nb;
	int		ret;

	ret = FALSE;
	if (((t_token*)(lst->content))->type == NB)
	{
		len = ft_strlen(((t_token*)(lst->content))->value);
		if (len == INDEX_HEIGHT_FORMAT)
		{
			nb = ft_atoi(((t_token*)(lst->content))->value);
			if (nb == i)
				ret = TRUE;
		}
	}
	return (ret);
}

static int	check_line(t_list *lst, size_t width)
{
	size_t	len;
	int		ret;

	ret = FALSE;
	if (((t_token*)(lst->content))->type == LINE)
	{
		len = ft_strlen(((t_token*)(lst->content))->value);
		if (len == width)
			ret = TRUE;
	}
	return (ret);
}

static int	fill_line(t_machine *machine)
{
	t_map	*line_head;
	char	*line;
	size_t	i;
	int		ret;

	i = 0;
	ret = check_line(machine->lst, machine->map_width);
	if (ret == TRUE)
	{
		line_head = machine->map;
		line = ((t_token*)(machine->lst->content))->value;
		while (line[i] != '\0')
		{
			if (line[i] == P1_CHAR)
				machine->map->played |= P1_PLAY;
			else if (line[i] == P2_CHAR)
				machine->map->played |= P2_PLAY;
			if (line[i] == P1_CHAR_LAST || line[i] == P2_CHAR_LAST)
				machine->map->played |= LAST_PLAY;
			machine->map = machine->map->right;
			i++;
		}
		machine->map = line_head;
		machine->map = machine->map->down;
	}
	return (ret);
}

static void	process_line(t_machine *machine, size_t i)
{
	int		ret;

	while (((t_token*)(machine->lst->content))->type != NEW_LINE)
	{
		if (((t_token*)(machine->lst->content))->type == NB)
			ret = check_index_height(machine->lst, i);
		else if (((t_token*)(machine->lst->content))->type == LINE)
			ret = fill_line(machine);
		machine->lst = machine->lst->next;
	}
}

void		fill_map(t_machine *machine)
{
	size_t	i;

	i = 0;
	while (i < machine->map_height)
	{
		process_line(machine, i);
		machine->lst = machine->lst->next;
		i++;
	}
	machine->map = machine->map_head;
}
