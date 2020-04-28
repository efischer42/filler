#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define STDIN					0
# define EXEC_NAME				"efischer.filler"
# define P1_CHAR				'O'
# define P1_CHAR_LAST			'o'
# define P2_CHAR				'X'
# define P2_CHAR_LAST			'x'
# define INDEX_HEIGHT_FORMAT	3
# define P1_PLAY				0x1
# define P2_PLAY				0x2
# define DANGER_ZONE			0x4
# define PATH					0x8
# define TAB_END				-1
# define NB_TOKEN				14
# define NB_FCT					7
# define NB_DIR					8
# define NB_MAIN_DIR			4

enum	e_functions
{
	ST_LEXER_PARSER,
	ST_GET_PLAYER,
	ST_GET_MAP,
	ST_SET_OBJECTIVES,
	ST_PATH,
	ST_GET_PIECE,
	ST_PLAY,
	ST_END_TURN,
	ST_ERROR,
};

enum	e_id
{
	O1,
	O2,
	O3
};

enum	e_direction
{
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT
};

typedef struct	s_map
{
	struct s_map	*left;
	struct s_map	*right;
	struct s_map	*up;
	struct s_map	*down;
	uint64_t		data;
	size_t			x;
	size_t			y;
	enum e_id		id;
}				t_map;

typedef struct	s_path
{
	t_map			map;
	enum e_id		id;
	struct s_path	*next;
}				t_path;

typedef struct	s_machine
{
	uint64_t	state;
	t_map		*map;
	t_map		*start;
	t_map		*opponent_start;
	t_map		*up_left_corner;
	t_map		*up_right_corner;
	t_map		*bottom_left_corner;
	t_map		*bottom_right_corner;
	t_map		*objective1;
	t_map		*objective2;
	t_map		*objective3;
	t_list		*token_lst;
	t_list		*head;
	t_list		*path_lst;
	size_t		i_input;
	size_t		map_height;
	size_t		map_width;
	size_t		piece_height;
	size_t		piece_width;
	size_t		dist;
	char		**piece;
	char		player;
	char		player_last;
	char		opponent;
	char		opponent_last;
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
int		get_input(char **input);
void	lexer(t_machine *machine, char *input);
void	get_word(t_machine *machine, char *input, t_token *token, size_t *pos);
void	parser(t_machine *machine);
void	get_player(t_machine *machine);
void	get_map(t_machine *machine);
void	get_map_dimensions(t_machine *machine);
int		check_index_width(t_machine *machine);
void	generate_map(t_machine *machine);
void	fill_map(t_machine *machine);
int		fill_line(t_machine *machine);
void	set_objectives(t_machine *machine);
void	path(t_machine *machine);
void	set_dir(enum e_direction *dir, t_map *map, t_map *objective);
void	get_piece(t_machine *machine);
void	get_piece_dimensions(t_machine *machine);
void	play(t_machine *machine);
void	del(void *content, size_t content_size);
void	debug(t_list *lst);
void	debug_map(t_map *map);
void	debug_dir(enum e_direction *dir);

#endif
