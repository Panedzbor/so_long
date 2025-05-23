/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:55:31 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 17:55:38 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void		set_sprites(t_gamedata *gd);

void	display_sprites(t_gamedata *gd)
{
	int	i;
	int	j;

	if (!gd->main_character)
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

	gd->main_character = xpm_to_img(gd, "./my_assets/kol.xpm", &dummy);
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
