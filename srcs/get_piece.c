#include "filler.h"

static void	allocate_piece(t_machine *machine)
{
	size_t	i;

	i = 0;
	machine->piece = (char**)malloc(sizeof(char*) * machine->piece_height);
	while (i < machine->piece_height)
	{
		machine->piece[i] = (char*)malloc(sizeof(char) * machine->piece_width);
		i++;
	}
}

static int	check_piece_line(char *line)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = TRUE;
	while (line[i] != '\0')
	{
		if (line[i] != '.' && line[i] != '*')
		{
			ret = FALSE;
			break ;
		}
		i++;
	}
	return (ret);
}

void		get_piece(t_machine *machine)
{
	size_t	i;
	int		ret;

	i = 0;
	ft_putendl_fd("Get piece", 2);
	get_piece_dimensions(machine);
	allocate_piece(machine);
	while (i < machine->piece_height)
	{
		if (((t_token*)(machine->lst->content))->type == LINE)
		{
			ret = check_piece_line(((t_token*)(machine->lst->content))->value);
			if (ret == FALSE)
			{
				machine->state = ST_ERROR;
				break ;
			}
			machine->piece[i] = ft_strdup(((t_token*)(machine->lst->content))->value);
			i++;
		}
		machine->lst = machine->lst->next;
	}
	if (machine->state != ST_ERROR)
		machine->state = ST_PLAY;
}
