/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprites_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:55:31 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 17:55:38 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void		set_sprites(t_gamedata *gd);

void	display_sprites(t_gamedata *gd)
{
	int	i;
	int	j;

	if (!gd->main_character[0])
		set_sprites(gd);
	i = 0;
	while (i < gd->map_height)
	{
		j = 0;
		while (j < gd->map_width)
		{
			display_current_sprite(gd, i, j);
			j++;
		}
		i++;
	}
}

static void	set_sprites(t_gamedata *gd)
{
	static int	dummy;

	gd->main_character[0] = xpm_to_img(gd, "./my_assets/kol(2).xpm", &dummy);
	gd->main_character[1] = xpm_to_img(gd, "./my_assets/kol(1).xpm", &dummy);
	gd->main_character[2] = xpm_to_img(gd, "./my_assets/kol.xpm", &dummy);
	gd->main_character[3] = xpm_to_img(gd, "./my_assets/kol(3).xpm", &dummy);
	gd->main_character[4] = xpm_to_img(gd, "./my_assets/kol(4).xpm", &dummy);
	gd->enemy1[0] = xpm_to_img(gd, "./my_assets/ded0.xpm", &dummy);
	gd->enemy1[1] = xpm_to_img(gd, "./my_assets/ded1.xpm", &dummy);
	gd->enemy1[2] = xpm_to_img(gd, "./my_assets/ded2.xpm", &dummy);
	gd->enemy1[3] = xpm_to_img(gd, "./my_assets/ded3.xpm", &dummy);
	gd->enemy1[4] = xpm_to_img(gd, "./my_assets/ded4.xpm", &dummy);
	gd->enemy2[0] = xpm_to_img(gd, "./my_assets/baba.xpm", &dummy);
	gd->enemy2[1] = xpm_to_img(gd, "./my_assets/baba1.xpm", &dummy);
	gd->enemy2[2] = xpm_to_img(gd, "./my_assets/baba2.xpm", &dummy);
	gd->enemy2[3] = xpm_to_img(gd, "./my_assets/baba3.xpm", &dummy);
	gd->enemy2[4] = xpm_to_img(gd, "./my_assets/baba4.xpm", &dummy);
}

void	display_without_background(void *sprite, t_gamedata *gd, int i, int j)
{
	int				x;
	int				y;
	unsigned int	color;
	unsigned int	background_color;
	t_imagedata		id;

	id.data = mlx_get_data_addr(sprite, &id.bpp, &id.size_line, &id.endian);
	background_color = *(unsigned int *)id.data;
	y = 0;
	while (y < TILE_WDTH)
	{
		x = 0;
		while (x < TILE_WDTH)
		{
			color = *(unsigned int *)
				(id.data + y * id.size_line + x * (id.bpp / 8));
			if (color != background_color)
				mlx_pixel_put(gd->mlx_ptr, gd->win_ptr, j * TILE_WDTH + x,
					i * TILE_WDTH + y, color);
			x++;
		}
		y++;
	}
}
