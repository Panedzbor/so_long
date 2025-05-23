/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:27:51 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 18:27:55 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_tiles(t_gamedata *gd);
static void	choose_tile_to_display(t_gamedata *gd, int i, int j);

void	draw_map(t_gamedata *gd)
{
	int	i;
	int	j;

	if (!gd->main_character)
		set_tiles(gd);
	i = 0;
	while (i < gd->map_height)
	{
		j = 0;
		while (j < gd->map_width)
		{
			choose_tile_to_display(gd, i, j);
			j++;
		}
		i++;
	}
}

static void	set_tiles(t_gamedata *gd)
{
	static int		dummy;

	gd->free_space = xpm_to_img(gd, "./my_assets/floor3.xpm", &dummy);
	gd->wall = xpm_to_img(gd, "./my_assets/wall.xpm", &dummy);
	gd->wall_hor = xpm_to_img(gd, "./my_assets/wall-hor.xpm", &dummy);
	gd->collectible = xpm_to_img(gd, "./my_assets/flour2.xpm", &dummy);
	gd->exit = xpm_to_img(gd, "./my_assets/door-closed.xpm", &dummy);
	gd->exitopen = xpm_to_img(gd, "./my_assets/door-open.xpm", &dummy);
}

static void	choose_tile_to_display(t_gamedata *gd, int i, int j)
{
	int	offset;

	mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->free_space,
		j * TILE_WDTH, i * TILE_WDTH);
	offset = j + i * (gd->map_width + 1);
	if (gd->map[offset] == '1' && (i == 0 || i == gd->map_height - 1))
		mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->wall_hor,
			j * TILE_WDTH, i * TILE_WDTH);
	else if (gd->map[offset] == '1')
		mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->wall,
			j * TILE_WDTH, i * TILE_WDTH);
	else if (gd->map[offset] == 'E' && ft_strchr(gd->map, 'C'))
		display_without_background(gd->exit, gd, i, j);
	else if (!ft_strchr(gd->map, 'E') && gd->map[offset] == 'P')
		display_without_background(gd->exit, gd, i, j);
}
