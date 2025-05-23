/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_termination.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:36:46 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 18:36:50 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	reset_ptrs(t_gamedata *gd);

void	terminate_game(t_gamedata *gd, int error)
{
	if (error == 1)
		ft_printf("Error\nInvalid characters in the map\n");
	else if (error == 2)
		ft_printf("Error\nNo collectibles on the map\n");
	else if (error == 3 && !ft_strchr(gd->map, 'E'))
		ft_printf("Error\nNo exits on the map\n");
	else if (error == 3 && ft_strchr(gd->map, 'E'))
		ft_printf("Error\nMore than one exit on the map\n");
	else if (error == 4 && !ft_strchr(gd->map, 'P'))
		ft_printf("Error\nNo player starting position on the map\n");
	else if (error == 4 && ft_strchr(gd->map, 'P'))
		ft_printf("Error\nMore than one player starting position on the map\n");
	else if (error == 5)
		ft_printf("Error\nThe map is not rectangular\n");
	else if (error == 6)
		ft_printf("Error\nThe map is not enclosed with walls\n");
	else if (error == 7)
		ft_printf("Error\nNo valid path to win the game\n");
	exit_game(gd);
}

void	win_game(t_gamedata *gd)
{
	draw_map(gd);
	display_sprites(gd);
	mlx_set_font(gd->mlx_ptr, gd->win_ptr, "10x20");
	mlx_do_sync(gd->mlx_ptr);
	sleep(3);
	mlx_loop_end(gd->mlx_ptr);
	exit_game(gd);
}

int	exit_game(t_gamedata *gd)
{
	if (gd->main_character)
	{
		mlx_destroy_image(gd->mlx_ptr, gd->main_character);
		mlx_destroy_image(gd->mlx_ptr, gd->wall);
		mlx_destroy_image(gd->mlx_ptr, gd->wall_hor);
		mlx_destroy_image(gd->mlx_ptr, gd->free_space);
		mlx_destroy_image(gd->mlx_ptr, gd->collectible);
		mlx_destroy_image(gd->mlx_ptr, gd->exit);
		mlx_destroy_image(gd->mlx_ptr, gd->exitopen);
	}
	if (gd->win_ptr)
		mlx_destroy_window(gd->mlx_ptr, gd->win_ptr);
	if (gd->mlx_ptr)
	{
		mlx_destroy_display(gd->mlx_ptr);
		free(gd->mlx_ptr);
	}
	free(gd->map);
	free(gd->map_copy);
	reset_ptrs(gd);
	exit(0);
	return (0);
}

static void	reset_ptrs(t_gamedata *gd)
{
	gd->wall = NULL;
	gd->wall_hor = NULL;
	gd->exit = NULL;
	gd->free_space = NULL;
	gd->main_character = NULL;
	gd->collectible = NULL;
	gd->exitopen = NULL;
	gd->map = NULL;
	gd->map_copy = NULL;
	gd->win_ptr = NULL;
	gd->mlx_ptr = NULL;
}
