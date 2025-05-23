/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:39:06 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 18:39:09 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	set_move(int keycode, t_gamedata *gd);
static bool	valid_move(int move, t_gamedata *gd);
static void	recalculate_map(t_gamedata *gd, int move);

int	key_hook(int keycode, void *gd)
{
	int	move;

	move = set_move(keycode, gd);
	if (move)
	{
		if (!valid_move(move, gd))
			return (0);
		recalculate_map(gd, move);
		((t_gamedata *)gd)->movements++;
		ft_printf("Current number of movements: %d\n",
			((t_gamedata *)gd)->movements);
		if (check_if_completed(((t_gamedata *)gd)->map))
			win_game(gd);
	}
	if (keycode == 0xff1b)
		exit_game(gd);
	return (0);
}

static int	set_move(int keycode, t_gamedata *gd)
{
	if (keycode == 0x0061 || keycode == 0x0041)
		return (-1);
	if (keycode == 0x0064 || keycode == 0x0044)
		return (1);
	if (keycode == 0x0077 || keycode == 0x0057)
		return (-(gd->map_width + 1));
	if (keycode == 0x0073 || keycode == 0x0053)
		return (gd->map_width + 1);
	return (0);
}

static bool	valid_move(int move, t_gamedata *gd)
{
	if (gd->map[gd->player_position + move] == '1')
		return (false);
	return (true);
}

static void	recalculate_map(t_gamedata *gd, int move)
{
	if (!ft_strchr(gd->map, 'E'))
		gd->map[gd->player_position] = 'E';
	else
		gd->map[gd->player_position] = '0';
	gd->player_position += move;
	gd->map[gd->player_position] = 'P';
}
