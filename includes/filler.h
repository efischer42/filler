#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define STDIN					0
# define NB_FCT					6
# define ST_GET_PLAYER			0
# define ST_GET_MAP				1
# define ST_GET_PIECE			2
# define ST_OPPONENT_HEAT_MAP	3
# define ST_PLAYER_HEAT_MAP		4
# define ST_PLAY				5
# define ST_END_TURN			6
# define ST_ERROR				7

typedef struct	s_machine
{
	uint64_t	state;
}				t_machine;

typedef	void	(*f)(t_machine *);

void	state_machine(t_machine *machine);
void	get_player(t_machine *machine);
void	get_map(t_machine *machine);
void	get_piece(t_machine *machine);
void	opponent_heat_map(t_machine *machine);
void	player_heat_map(t_machine *machine);
void	play(t_machine *machine);

#endif
