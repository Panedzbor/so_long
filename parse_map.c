/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:51:51 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 18:51:54 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_map_size(t_gamedata *gd);

void	extract_map(t_gamedata *gd)
{
	int	map_size;

	map_size = count_map_size(gd);
	save_map(gd, map_size);
	gd->map_copy = ft_strdup(gd->map);
}

static int	count_map_size(t_gamedata *gd)
{
	int		count;
	char	buf[1];
	int		read_check;

	gd->map_fd = open(gd->map_file_name, 0);
	if (gd->map_fd == -1)
	{
		ft_printf("Error\nError opening the map\n");
		exit(0);
	}
	count = 0;
	read_check = 1;
	while (read_check > 0)
	{
		read_check = read(gd->map_fd, buf, 1);
		if (read_check > 0)
			count++;
	}
	if (read_check == -1)
	{
		ft_printf("Error\nError reading the map\n");
		exit(0);
	}
	close(gd->map_fd);
	return (count);
}

void	get_map_dimensions(t_gamedata *gd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (gd->map[i])
	{
		if (gd->map_width == 0 && gd->map[i] != '\n')
			count++;
		if (gd->map_width == 0 && gd->map[i] == '\n')
			gd->map_width = count;
		if (gd->map[i] == '\n')
			gd->map_height = ++count - gd->map_width;
		i++;
	}
	if (gd->map[i - 1] != '\n')
		gd->map_height++;
	gd->map_width_px = gd->map_width * TILE_WDTH;
	gd->map_height_px = gd->map_height * TILE_WDTH;
}

int	validate_map(t_gamedata *gd)
{
	int	ammount_error;

	if (!valid_chars(gd))
		return (1);
	ammount_error = valid_amount(gd);
	if (ammount_error)
		return (ammount_error);
	if (!valid_shape(gd))
		return (5);
	if (!valid_walls(gd))
		return (6);
	if (!valid_path(gd, gd->player_position))
		return (7);
	return (0);
}
