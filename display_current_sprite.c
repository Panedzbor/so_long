/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_current_sprite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:00:34 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 16:00:40 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_if_sprite_exists(t_gamedata *gd, bool *redrawn);
static void	choose_sprite(t_gamedata *gd, int offset, bool *redrawn,
				void ***sprite);
static void	check_if_all_collectibles_drawn(int *drawn_collectibles,
				bool *redrawn, t_gamedata *gd);

void	display_current_sprite(t_gamedata *gd, int i, int j)
{
	void		**sprite;
	static bool	redrawn[3];
	static int	drawn_collectibles;
	int			offset;

	sprite = NULL;
	offset = j + i * (gd->map_width + 1);
	if (gd->map[offset] != '0' && gd->map[offset] != '1')
	{
		check_if_sprite_exists(gd, redrawn);
		choose_sprite(gd, offset, redrawn, &sprite);
		if (sprite)
			display_without_background(sprite, gd, i, j);
		if (gd->map[offset] == 'C')
			check_if_all_collectibles_drawn(&drawn_collectibles, redrawn, gd);
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
