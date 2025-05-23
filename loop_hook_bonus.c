/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:41:36 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 18:41:40 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	enemy_move(char enemy, t_gamedata *gd);
static void	assign_values(int *move_dir, t_gamedata *gd, int *random,
				int *move);
static void	change_pos(char enemy, t_gamedata *gd, int *move);

int	background_activities(t_gamedata *gd)
{
	static int	counter;
	static int	counter2;

	if (counter2 == 40000)
	{
		enemy_move('N', gd);
		check_if_lost(gd);
		enemy_move('n', gd);
		check_if_lost(gd);
		counter2 = 0;
	}
	if (counter == 7000)
	{
		draw_map(gd);
		display_score(gd);
		display_sprites(gd);
		counter = 0;
	}
	counter++;
	counter2++;
	return (0);
}

static void	enemy_move(char enemy, t_gamedata *gd)
{
	static int	move[2];
	int			move_dir[4];
	int			random;
	int			next_position;

	random = 0;
	assign_values(move_dir, gd, &random, move);
	if (enemy == 'N')
		next_position = gd->enemy1_position + move[0];
	else
		next_position = gd->enemy2_position + move[1];
	if (gd->map[next_position] == '0' || gd->map[next_position] == 'P')
		change_pos(enemy, gd, move);
	else
	{
		if (enemy == 'N')
			move[0] = move_dir[random];
		else
			move[1] = move_dir[random];
	}
}

static void	change_pos(char enemy, t_gamedata *gd, int *move)
{
	if (enemy == 'N')
	{
		gd->map[gd->enemy1_position + move[0]] = enemy;
		gd->map[gd->enemy1_position] = '0';
		gd->enemy1_position += move[0];
	}
	else
	{
		gd->map[gd->enemy2_position + move[1]] = enemy;
		gd->map[gd->enemy2_position] = '0';
		gd->enemy2_position += move[1];
	}
}

static void	assign_values(int *move_dir, t_gamedata *gd, int *random, int *move)
{
	move_dir[0] = -(gd->map_width + 1);
	move_dir[1] = 1;
	move_dir[2] = (gd->map_width + 1);
	move_dir[3] = -1;
	*random = rand() % 4;
	if (!move[0])
		move[0] = move_dir[*random];
	if (!move[1])
		move[1] = move_dir[*random];
}
