#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define FROM_LEFT				0x1
# define FROM_RIGHT				0x2
# define FROM_UP				0x4
# define FROM_DOWN				0x8
# define P1_CHAR				'O'
# define P1_CHAR_LAST			'o'
# define P2_CHAR				'X'
# define P2_CHAR_LAST			'x'
# define PIECE_CHAR				'*'
# define INDEX_HEIGHT_FORMAT	3
# define P1_PLAY				0x1
# define P2_PLAY				0x2
# define DANGER_ZONE			0x4
# define PATH					0x8
# define PIECE_PART				0x10
# define DEBUG					0x20
# define TAB_END				-1
# define NB_TOKEN				13
# define NB_FCT					4
# define NB_DIR					8
# define NB_MAIN_DIR			4

enum	e_functions
{
	ST_GET_PLAYER,
	ST_GET_MAP,
	ST_GET_PIECE,
	ST_ERROR,
};

enum	e_id
{
	O1 = 1,
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
	t_list			*lst;
	enum e_id		id;
}				t_path;

typedef struct	s_machine
{
	uint64_t	state;
	uint64_t	opt;
	t_map		*map;
	t_map		*start;
	t_map		*play;
	t_map		*opponent_start;
	t_map		*up_left_corner;
	t_map		*up_right_corner;
	t_map		*bottom_left_corner;
	t_map		*bottom_right_corner;
	t_map		*objective1;
	t_map		*objective2;
	t_map		*objective3;
	t_map		*piece;
	t_map		*head_piece;
	t_list		*token_lst;
	t_list		*path_lst;
	size_t		i_input;
	size_t		map_height;
	size_t		map_width;
	size_t		piece_height;
	size_t		piece_width;
	size_t		dist;
	char		*input;
	char		*player_name;
	int			play_x;
	int			play_y;
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

void	lexer_parser(t_machine *machine);
void	lexer(t_machine *machine);
void	get_word(t_machine *machine, char *input, t_token *token, size_t *pos);
void	parser(t_machine *machine, t_list *token_lst);
void	get_player(t_machine *machine);
void	get_map(t_machine *machine);
void	get_map_dimensions(t_machine *machine, t_list *token_lst);
void	check_index_width(t_machine *machine, t_list *token_lst);
void	generate_map(t_machine *machine);
void	data_map(t_map *map, t_map *line, size_t y, size_t x);
void	add_map(t_map **line, t_map *new_map);
void	fill_map(t_machine *machine, t_list *token_lst);
int		fill_line(t_machine *machine, t_list *token_lst);
void	set_objectives(t_machine *machine);
void	path(t_machine *machine);
void	set_dir(enum e_direction *dir, t_map *map, t_map *objective);
void	get_piece(t_machine *machine);
void	get_piece_dimensions(t_machine *machine, t_list *token_lst);
void	generate_piece(t_machine *machine);
void	fill_piece(t_machine *machine, t_list *token_lst);
void	play(t_machine *machine);
void	path_play(t_machine *machine, t_list *path_lst);
void	piece_placement(t_machine *machine, t_map *piece, uint64_t opt);
int		find_path(t_map *map, t_map *objective, t_list **path);
void	turn(t_machine *machine);
void	del_lst(void *content, size_t content_size);
void	error(t_machine *machine);
void	del_line(t_map **map);
void	del_map(t_map **map);
void	debug(t_list *lst);
void	debug_map(t_map *map);
void	debug_dir(enum e_direction *dir);
void	debug_path(t_list *lst);

#endif
