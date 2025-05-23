/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_enemies_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:52:38 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 18:52:41 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	place_enemies(t_gamedata *gd)
{
	int	pos;

	while (true)
	{
		pos = rand() % (gd->map_width * gd->map_height);
		if (gd->map[pos] == '0')
			break ;
	}
	gd->map[pos] = 'N';
	gd->enemy1_position = pos;
	while (true)
	{
		pos = rand() % (gd->map_width * gd->map_height);
		if (gd->map[pos] == '0')
			break ;
	}
	gd->map[pos] = 'n';
	gd->enemy2_position = pos;
}
