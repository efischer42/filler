#include "filler.h"
#include "stdio.h"

int		get_input(char **input)
{
	char	*line;
	int		ret;
	int		count;

	count = -1;
	line = NULL;
	while ((ret = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		dprintf(2, "count: %d\n", count);
		if (line != NULL)
		{
			dprintf(2, "line: %s\n", line);
			if (ft_strnequ(line, "Piece ", 6) == TRUE)
				count = ft_atoi(line + 6) + 1;
			line = ft_join_free(line, "\n", 1);
			*input = ft_join_free(*input, line, 3);
			if (count != -1)
				count--;
		}
		if (count < -1 || count == 0)
			break ;
	}
	dprintf(2, "ret: %d\n", ret);
	return (ret);
}
