#include  "filler.h"

static void	set_map_dimensions(t_machine *machine, int nb_count, t_list *token_lst)
{
	if (nb_count == 0)
		machine->map_height = ft_atoi(((t_token*)(token_lst->content))->value);
	else
		machine->map_width = ft_atoi(((t_token*)(token_lst->content))->value);
}

void		get_map_dimensions(t_machine *machine, t_list *token_lst)
{
	int		nb_count;

	nb_count = 0;
	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == NB)
		{
			set_map_dimensions(machine, nb_count, token_lst);
			nb_count++;
		}
		token_lst = token_lst->next;
	}
	machine->dist = (machine->map_height + machine->map_width) * 1 / 20;
}

static void	set_piece_dimensions(t_machine *machine, t_list *token_lst, int nb_count)
{
	if (nb_count == 0)
		machine->piece_height = ft_atoi(((t_token*)(token_lst->content))->value);
	else
		machine->piece_width = ft_atoi(((t_token*)(token_lst->content))->value);
}

void		get_piece_dimensions(t_machine *machine, t_list *token_lst)
{
	int		nb_count;

	nb_count = 0;
	while (((t_token*)(token_lst->content))->type != END)
	{
		if (((t_token*)(token_lst->content))->type == NB)
		{
			set_piece_dimensions(machine, token_lst, nb_count);
			nb_count++;
		}
		token_lst = token_lst->next;
	}
}
