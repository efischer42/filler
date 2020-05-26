/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 13:57:18 by efischer          #+#    #+#             */
/*   Updated: 2020/05/26 14:02:30 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_STRUCT_H
# define FILLER_STRUCT_H

# include "filler.h"

typedef struct	s_objective
{
	struct s_map	*map;
	uint64_t		edge;
	int				dead;
}				t_objective;

typedef struct	s_map
{
	struct s_map	*left;
	struct s_map	*right;
	struct s_map	*up;
	struct s_map	*down;
	uint64_t		data;
	int				x;
	int				y;
	int				*zone;
	uint8_t			dead;
	t_objective		*objective;
}				t_map;

typedef struct	s_path
{
	t_list			*lst;
	size_t			path_len;
	t_objective		*objective;
}				t_path;

typedef struct	s_machine
{
	uint64_t			state;
	uint64_t			opt;
	uint64_t			edge;
	t_map				***mx;
	t_map				*map;
	t_map				*head_map;
	t_map				*piece;
	t_map				*head_piece;
	t_map				*last_play;
	t_list				*token_lst;
	t_list				*objective_lst;
	t_list				*path_lst;
	t_objective			*cur_objective;
	enum e_direction	dir[NB_DIR_TO_OBJ];
	int					map_height;
	int					map_width;
	int					piece_height;
	int					piece_width;
	size_t				dist;
	char				*input;
	char				*player_name;
	int					upl_zone;
	int					upr_zone;
	int					downl_zone;
	int					downr_zone;
	int					up_zone;
	int					down_zone;
	int					left_zone;
	int					right_zone;
	int					play_x;
	int					play_y;
	char				player;
	char				player_last;
	char				opponent;
	char				opponent_last;
}				t_machine;

typedef struct	s_token
{
	enum e_token	type;
	char			*value;
}				t_token;

#endif
