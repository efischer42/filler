/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_enum.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 13:59:16 by efischer          #+#    #+#             */
/*   Updated: 2020/05/27 13:23:08 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_ENUM_H
# define FILLER_ENUM_H

enum	e_state
{
	ST_GET_PLAYER,
	ST_GET_PLATEAU,
	ST_GET_MAP,
	ST_GET_PIECE_DIMENSIONS,
	ST_GET_PIECE
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

enum	e_token
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
	MAP_LINE,
	PIECE_LINE
};

#endif
