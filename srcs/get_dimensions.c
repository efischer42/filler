#include  "filler.h"

static void	set_map_dimensions(t_machine *machine, int nb_count)
{
	if (nb_count == 0)
		machine->map_height = ft_atoi(((t_token*)(machine->lst->content))->value);
	else
		machine->map_width = ft_atoi(((t_token*)(machine->lst->content))->value);
}

void		get_map_dimensions(t_machine *machine)
{
	int		nb_count;

	nb_count = 0;
	while (((t_token*)(machine->lst->content))->type != NEW_LINE)
	{
		if (((t_token*)(machine->lst->content))->type == NB)
		{
			set_map_dimensions(machine, nb_count);
			nb_count++;
		}
		machine->lst = machine->lst->next;
	}
	machine->lst = machine->lst->next;
}
