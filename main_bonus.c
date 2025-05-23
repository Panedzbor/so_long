/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:35:10 by earutiun          #+#    #+#             */
/*   Updated: 2025/04/15 15:35:45 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	parse_map(t_gamedata *gd);
void	launch_game(t_gamedata *gd);

int	main(int argc, char *argv[])
{
	t_gamedata	gd;

	if (argc != 2)
	{
		ft_printf("Error\nProgram expects one argument\n");
		exit(0);
	}
	srand(time(NULL));
	init_gamedata(&gd);
	gd.map_file_name = (const char *)argv[1];
	parse_map(&gd);
	launch_game(&gd);
	return (0);
}

void	launch_game(t_gamedata *gd)
{
	gd->mlx_ptr = mlx_init();
	mlx_get_screen_size(gd->mlx_ptr, &gd->screen_width, &gd->screen_height);
	compare_mapsize_and_screensize(gd);
	gd->win_ptr = mlx_new_window(gd->mlx_ptr, gd->map_width_px,
			gd->map_height_px, "Kolobok's Breakout");
	draw_map(gd);
	display_score(gd);
	display_sprites(gd);
	mlx_key_hook(gd->win_ptr, key_hook, gd);
	mlx_hook(gd->win_ptr, 17, 0, exit_game, gd);
	mlx_loop_hook(gd->mlx_ptr, background_activities, gd);
	mlx_loop(gd->mlx_ptr);
}

void	parse_map(t_gamedata *gd)
{
	int	error;

	extract_map(gd);
	get_map_dimensions(gd);
	gd->player_position = (int)(ft_strchr(gd->map, 'P') - gd->map);
	error = validate_map(gd);
	if (error)
		terminate_game(gd, error);
	place_enemies(gd);
}
