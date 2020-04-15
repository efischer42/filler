#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define STDIN					0
# define NB_TOKEN				15
# define NB_FCT					7
# define ST_LEXER_PARSER		0
# define ST_GET_PLAYER			1
# define ST_GET_MAP				2
# define ST_GET_PIECE			3
# define ST_OPPONENT_HEAT_MAP	4
# define ST_PLAYER_HEAT_MAP		5
# define ST_PLAY				6
# define ST_END_TURN			7
# define ST_ERROR				8

typedef struct	s_machine
{
	uint64_t	state;
	char		*input;
	size_t		map_height;
	size_t		map_width;
	size_t		piece_height;
	size_t		piece_width;
}				t_machine;

enum e_token
{
	DOLLARS,
	EXEC,
	P1,
	P2,
	COLON,
	NEW_LINE,
	PLATEAU,
	PIECE,
	SPACE,
	ERROR,
	START,
	END,
	PLAYER_NAME,
	NB,
	LINE
};

typedef struct	s_token
{
	enum e_token	type;
	char			*value;
}				t_token;

void	state_machine(t_machine *machine);
void	lexer_parser(t_machine *machine);
int		get_input(t_machine *machine);
void	lexer(t_machine *machine, t_list **lst);
void	get_word(t_machine *machine, t_token *token, size_t *pos);
void	parser(t_machine *machine, t_list *lst);
void	get_player(t_machine *machine);
void	get_map(t_machine *machine);
void	get_piece(t_machine *machine);
void	opponent_heat_map(t_machine *machine);
void	player_heat_map(t_machine *machine);
void	play(t_machine *machine);
void	debug(t_list *lst);
void	del(void *content, size_t content_size);

#endif
