/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:03:12 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 19:03:16 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	open_map(t_gamedata *gd);
static void	allocate_memory_for_map(t_gamedata *gd, int map_size);
static void	read_map(t_gamedata *gd, int map_size);

void	save_map(t_gamedata *gd, int map_size)
{
	open_map(gd);
	allocate_memory_for_map(gd, map_size);
	read_map(gd, map_size);
	close(gd->map_fd);
}

static void	open_map(t_gamedata *gd)
{
	gd->map_fd = open(gd->map_file_name, 0);
	if (gd->map_fd == -1)
	{
		ft_printf("Error\nError opening the map\n");
		exit(0);
	}
}

static void	allocate_memory_for_map(t_gamedata *gd, int map_size)
{
	gd->map = (char *)ft_calloc(map_size + 1, sizeof(char));
	if (!gd->map)
	{
		ft_printf("Error\nError allocating memory for the map\n");
		exit(0);
	}
}

static void	read_map(t_gamedata *gd, int map_size)
{
	if (read(gd->map_fd, gd->map, map_size) != map_size)
	{
		ft_printf("Error\nError reading the map\n");
		free(gd->map);
		gd->map = NULL;
		exit(0);
	}
}
