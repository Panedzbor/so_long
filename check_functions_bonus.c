/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:41:06 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 15:41:39 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	move_check(int offset, int pos, t_gamedata *gd, bool *completed)
{
	if (gd->map_copy[pos + offset] != '1' && gd->map_copy[pos + offset] != 'P')
	{
		gd->map_copy[pos + offset] = 'P';
		*completed = check_if_completed(gd->map_copy);
		valid_path(gd, pos + offset);
	}
}

void	compare_mapsize_and_screensize(t_gamedata *gd)
{
	if (gd->map_width_px > gd->screen_width
		|| gd->map_height_px > gd->screen_height)
	{
		ft_printf("Error\n");
		ft_printf("Map dimensions exceed the current screen characteristics.");
		ft_printf("Please use a smaller map or buy a new screen\n");
		exit_game(gd);
	}
}

bool	check_if_completed(char *map)
{
	if (ft_strchr(map, 'C') || ft_strchr(map, 'E'))
		return (false);
	return (true);
}

void	check_if_lost(t_gamedata *gd)
{
	if (!ft_strchr(gd->map, 'P'))
	{
		ft_printf("YOU LOSE!\n");
		draw_map(gd);
		display_score(gd);
		display_sprites(gd);
		mlx_set_font(gd->mlx_ptr, gd->win_ptr, "10x20");
		mlx_string_put(gd->mlx_ptr, gd->win_ptr, (gd->map_width_px / 2)
			- (ft_strlen("YOU LOSE!") / 2), 30, 0xFF0000, "YOU LOSE!");
		mlx_do_sync(gd->mlx_ptr);
		sleep(3);
		mlx_loop_end(gd->mlx_ptr);
		exit_game(gd);
	}
}
