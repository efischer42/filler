#include "filler.h"

int		get_input(char **input)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(STDIN, &line)) == TRUE)
	{
		if (line != NULL && line[0] != '\0')
		{
			line = ft_join_free(line, "\n", 1);
			*input = ft_join_free(*input, line, 3);
		}
	}
	return (ret);
}
