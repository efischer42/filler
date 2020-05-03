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

static int	fill_piece_line(t_machine *machine)
{
	t_map	*line_head;
	char	*line;
	size_t	i;
	int		ret;

	i = 0;
	ret = check_line(machine->token_lst, machine->piece_width);
	if (ret == TRUE)
	{
		line_head = machine->piece;
		line = ((t_token*)(machine->token_lst->content))->value;
		while (line[i] != '\0')
		{
			if (line[i] == PIECE_CHAR)
				machine->piece->data |= PIECE_PART;
			machine->piece = machine->piece->right;
			i++;
		}
		machine->piece = line_head;
		machine->piece = machine->piece->down;
	}
	return (ret);
}

static void	process_line(t_machine *machine)
{
	while (((t_token*)(machine->token_lst->content))->type != END)
	{
		if (((t_token*)(machine->token_lst->content))->type == LINE)
			fill_piece_line(machine);
		machine->token_lst = machine->token_lst->next;
	}
}

void	fill_piece(t_machine *machine)
{
	size_t	i;

	i = 0;
	while (i < machine->piece_height)
	{
		process_line(machine);
		machine->token_lst = machine->token_lst->next;
		i++;
	}
	machine->piece = machine->head_piece;
//	debug_map(machine->piece);
}
