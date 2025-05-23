/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_termination_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:36:46 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 18:36:50 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	destroy_frames(t_gamedata *gd, void **sprite, int frames);
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
	display_score(gd);
	display_sprites(gd);
	mlx_set_font(gd->mlx_ptr, gd->win_ptr, "10x20");
	mlx_string_put(gd->mlx_ptr, gd->win_ptr, (gd->map_width_px / 2)
		- (ft_strlen("YOU WIN!") / 2), 30, 0xFF0000, "YOU WIN!");
	mlx_do_sync(gd->mlx_ptr);
	sleep(3);
	mlx_loop_end(gd->mlx_ptr);
	exit_game(gd);
}

int	exit_game(t_gamedata *gd)
{
	if (gd->main_character[0])
	{
		destroy_frames(gd, gd->main_character, 5);
		destroy_frames(gd, gd->enemy1, 5);
		destroy_frames(gd, gd->enemy2, 5);
		mlx_destroy_image(gd->mlx_ptr, gd->wall);
		mlx_destroy_image(gd->mlx_ptr, gd->wall_hor);
		mlx_destroy_image(gd->mlx_ptr, gd->free_space);
		destroy_frames(gd, gd->collectible, 5);
		mlx_destroy_image(gd->mlx_ptr, gd->exit);
		destroy_frames(gd, gd->exitopen, 5);
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
	gd->map = NULL;
	gd->map_copy = NULL;
	gd->win_ptr = NULL;
	gd->mlx_ptr = NULL;
}

static void	destroy_frames(t_gamedata *gd, void **sprite, int frames)
{
	int	i;

	i = 0;
	while (i < frames)
	{
		mlx_destroy_image(gd->mlx_ptr, sprite[i]);
		sprite[i] = NULL;
		i++;
	}
}
