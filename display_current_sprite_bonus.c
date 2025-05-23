/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_current_sprite_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:00:34 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 16:00:40 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_if_sprite_exists(t_gamedata *gd, bool *redrawn);
static void	choose_sprite(t_gamedata *gd, int offset, bool *redrawn,
				void ***sprite);
static void	check_if_all_collectibles_drawn(int *drawn_collectibles,
				bool *redrawn, t_gamedata *gd);
static void	change_counter(int *counter, bool *redrawn);

void	display_current_sprite(t_gamedata *gd, int i, int j)
{
	void		**sprite;
	static int	counter;
	static bool	redrawn[5];
	static int	drawn_collectibles;
	int			offset;

	sprite = NULL;
	offset = j + i * (gd->map_width + 1);
	if (gd->map[offset] != '0' && gd->map[offset] != '1')
	{
		check_if_sprite_exists(gd, redrawn);
		choose_sprite(gd, offset, redrawn, &sprite);
		if (sprite)
			display_without_background(sprite[counter], gd, i, j);
		if (gd->map[offset] == 'C')
			check_if_all_collectibles_drawn(&drawn_collectibles, redrawn, gd);
		change_counter(&counter, redrawn);
	}
}

static void	check_if_sprite_exists(t_gamedata *gd, bool *redrawn)
{
	if (!ft_strchr(gd->map, 'C'))
		redrawn[1] = true;
	else
		redrawn[2] = true;
}

static void	choose_sprite(t_gamedata *gd, int offset, bool *redrawn,
	void ***sprite)
{
	if (gd->map[offset] == 'P')
	{
		*sprite = gd->main_character;
		redrawn[0] = true;
	}
	else if (gd->map[offset] == 'N')
	{
		*sprite = gd->enemy1;
		redrawn[3] = true;
	}
	else if (gd->map[offset] == 'n')
	{
		*sprite = gd->enemy2;
		redrawn[4] = true;
	}
	else if (gd->map[offset] == 'E' && !ft_strchr(gd->map, 'C'))
	{
		*sprite = gd->exitopen;
		redrawn[2] = true;
	}
	else if (gd->map[offset] == 'C')
	{
		*sprite = gd->collectible;
		redrawn[1] = true;
	}
}

static void	check_if_all_collectibles_drawn(int *drawn_collectibles,
	bool *redrawn, t_gamedata *gd)
{
	(*drawn_collectibles)++;
	if (*drawn_collectibles == count_collectibles(gd))
	{
		redrawn[1] = true;
		*drawn_collectibles = 0;
	}
}

static void	change_counter(int *counter, bool *redrawn)
{
	bool		all_redrawn;
	static int	frame_dir;

	all_redrawn = false;
	if (redrawn[0] && redrawn[1] && redrawn[2] && redrawn[3] && redrawn[4])
		all_redrawn = true;
	if (all_redrawn)
	{
		if (!frame_dir)
			(*counter)++;
		else if (frame_dir)
			(*counter)--;
		ft_bzero(redrawn, sizeof(redrawn));
	}
	if (*counter == 4)
		frame_dir = 1;
	if (*counter == 0)
		frame_dir = 0;
}
