/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:04:05 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 19:04:08 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_gamedata(t_gamedata *gd)
{
	gd->map_file_name = NULL;
	gd->map = NULL;
	gd->map_copy = NULL;
	gd->map_fd = 0;
	gd->map_height = 0;
	gd->map_width = 0;
	gd->map_height_px = 0;
	gd->map_width_px = 0;
	gd->screen_height = 0;
	gd->screen_width = 0;
	gd->mlx_ptr = NULL;
	gd->win_ptr = NULL;
	gd->free_space = NULL;
	gd->wall = NULL;
	gd->wall_hor = NULL;
	ft_bzero(&gd->collectible, sizeof(gd->collectible));
	gd->exit = NULL;
	ft_bzero(&gd->exitopen, sizeof(gd->exitopen));
	ft_bzero(&gd->main_character, sizeof(gd->main_character));
	ft_bzero(&gd->enemy1, sizeof(gd->enemy1));
	ft_bzero(&gd->enemy2, sizeof(gd->enemy2));
	gd->player_position = 0;
	gd->enemy1_position = 0;
	gd->enemy2_position = 0;
	gd->movements = 0;
}

void	sl_init_ints(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

int	count_collectibles(t_gamedata *gd)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (gd->map[i])
	{
		if (gd->map[i] == 'C')
			amount++;
		i++;
	}
	return (amount);
}

void	*xpm_to_img(t_gamedata *gd, char *path, int *dummy)
{
	return (mlx_xpm_file_to_image(gd->mlx_ptr, path, dummy, dummy));
}
