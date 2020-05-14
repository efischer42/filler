#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define P1_CHAR				'O'
# define P2_CHAR				'X'
# define PIECE_CHAR				'*'
# define INDEX_HEIGHT_FORMAT	3
# define P1_PLAY				0x01
# define P2_PLAY				0x02
# define DANGER_ZONE			0x04
# define PIECE_PART				0x08
# define PATH					0x10
# define DEBUG					0x20
# define UPL_EDGE				0x01
# define UPR_EDGE				0x02
# define DOWNL_EDGE				0x04
# define DOWNR_EDGE				0x08
# define LEFTU_EDGE				0x10
# define LEFTD_EDGE				0x20
# define RIGHTU_EDGE			0x40
# define RIGHTD_EDGE			0x80
# define FROM_LEFT				0x01
# define FROM_RIGHT				0x02
# define FROM_UP				0x04
# define FROM_DOWN				0x08
# define TAB_END				-1
# define NB_TOKEN				13
# define NB_FCT					4
# define NB_DIR					8
# define NB_MAIN_DIR			4
# define NB_DIR_TO_OBJ			3

enum	e_functions
{
	ST_GET_PLAYER,
	ST_GET_MAP,
	ST_GET_PIECE,
	ST_ERROR,
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

typedef struct	s_objective
{
	struct s_map	*map;
	uint64_t		edge;
	uint8_t			dead;
}				t_objective;

typedef struct	s_map
{
	struct s_map	*left;
	struct s_map	*right;
	struct s_map	*up;
	struct s_map	*down;
	uint64_t		data;
	size_t			*zone;
	size_t			x;
	size_t			y;
	t_objective		*objective;
}				t_map;

typedef struct	s_path
{
	t_list			*lst;
	t_map			*node;
	size_t			path_len;
	uint8_t			dead;
	t_objective		*objective;
}				t_path;

typedef struct	s_machine
{
	uint64_t			state;
	uint64_t			opt;
	uint64_t			p1_edge;
	uint64_t			p2_edge;
	t_map				***mx;
	t_map				*map;
	t_map				*up_left_corner;
	t_map				*up_right_corner;
	t_map				*bottom_left_corner;
	t_map				*bottom_right_corner;
	t_map				*piece;
	t_map				*head_piece;
	t_map				*last_play;
	t_list				*token_lst;
	t_list				*objective_lst;
	t_list				*path_lst;
	t_objective			*cur_objective;
	enum e_direction	dir[NB_DIR_TO_OBJ];
	size_t				map_height;
	size_t				map_width;
	size_t				piece_height;
	size_t				piece_width;
	size_t				dist;
	size_t				upl_zone;
	size_t				upr_zone;
	size_t				downl_zone;
	size_t				downr_zone;
	char				*input;
	char				*player_name;
	int					play_x;
	int					play_y;
	char				player;
	char				player_last;
	char				opponent;
	char				opponent_last;
}						t_machine;

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

void	add_map(t_map **line, t_map *new_map);
void	check_index_width(t_machine *machine, t_list *token_lst);
void	data_map(t_map *map, t_map *line, size_t y, size_t x);
int		check_piece_pos(t_machine *machine, t_map *node, t_map *piece,
						t_map *piece_play);
void	cut_path(t_machine *machine);
void	del_line(t_map **map);
void	del_lst(void *content, size_t content_size);
void	del_map(t_map **map);
void	del_mx(t_machine *machine);
void	del_objective_lst(t_list *objective_lst);
void	del_path(void *content, size_t content_size);
void	del_path_first_part(t_machine *machine, t_list *lst, t_list *head);
void	del_path_lst(t_list *path_lst);
void	error(t_machine *machine);
int		fill_line(t_machine *machine, t_list *token_lst);
void	fill_map(t_machine *machine, t_list *token_lst);
void	fill_piece(t_machine *machine, t_list *token_lst);
int		find_path(t_machine *machine, t_map *start, t_map *map, t_list **path);
void	generate_map(t_machine *machine);
void	generate_mx(t_machine *machine);
void	generate_piece(t_machine *machine);
void	get_map(t_machine *machine);
void	get_map_dimensions(t_machine *machine, t_list *token_lst);
void	get_piece(t_machine *machine);
void	get_piece_dimensions(t_machine *machine, t_list *token_lst);
void	get_player(t_machine *machine);
void	get_word(t_machine *machine, char *input, t_token *token, size_t *pos);
void	init_map_dir(t_map **map_dir, t_map *map);
void	lexer(t_machine *machine);
void	lexer_parser(t_machine *machine);
void	parser(t_machine *machine, t_list *token_lst);
void	path(t_machine *machine, t_map *map);
int		piece_placement(t_machine *machine, t_map *map);
void	play(t_machine *machine, t_list *path_play);
void	play_turn(t_machine *machine);
void	retard_play(t_machine *machine, t_map *map);
void	set_dir(t_machine *machine, t_map *map);
void	set_edges(t_machine *machine, t_map *map, uint64_t *edge);
void	set_objectives(t_machine *machine);
void	set_main_dir(t_machine *machine, t_map *map, t_map **map_dir);
void	sort_objective_lst(t_list **lst1, t_list **lst2, t_list **head);
void	sort_objectives(t_list **lst1, t_list **lst2, t_list **head);
void	sort_len_path(t_list **lst1, t_list **lst2, t_list **head);
void	debug(t_list *lst);
void	debug_map(t_machine *machine, t_map *map);
void	debug_dir(enum e_direction *dir);
void	debug_path(t_list *lst);
void	debug_path_lst(t_list *path_lst);
void	print_path(t_list *lst);
void	debug_objective_lst(t_list *objective_lst);

#endif
