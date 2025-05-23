/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:48:22 by earutiun          #+#    #+#             */
/*   Updated: 2025/05/21 14:48:27 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include <X11/keysymdef.h>
# include <math.h>
# include <time.h>

# define TILE_WDTH 48

typedef struct s_gamedata
{
	const char	*map_file_name;
	char		*map;
	char		*map_copy;
	int			map_fd;
	int			map_width;
	int			map_height;
	int			map_width_px;
	int			map_height_px;
	int			screen_width;
	int			screen_height;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*wall;
	void		*wall_hor;
	void		*free_space;
	void		*collectible[5];
	void		*exit;
	void		*exitopen[5];
	void		*main_character[5];
	void		*enemy1[5];
	void		*enemy2[5];
	int			player_position;
	int			enemy1_position;
	int			enemy2_position;
	int			movements;
}	t_gamedata;

typedef struct s_imagedata
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*data;
}	t_imagedata;

void	save_map(t_gamedata *gd, int map_size);
void	extract_map(t_gamedata *gd);
void	get_map_dimensions(t_gamedata *gd);
int		validate_map(t_gamedata *gd);
bool	valid_chars(t_gamedata *gd);
int		valid_amount(t_gamedata *gd);
bool	valid_shape(t_gamedata *gd);
bool	valid_walls(t_gamedata *gd);
bool	valid_path(t_gamedata *gd, int pos);
void	place_enemies(t_gamedata *gd);
void	draw_map(t_gamedata *gd);
void	display_score(t_gamedata *gd);
void	display_sprites(t_gamedata *gd);
void	display_current_sprite(t_gamedata *gd, int i, int j);
void	display_without_background(void *sprite, t_gamedata *gd, int i, int j);
bool	check_if_completed(char *map);
void	check_if_lost(t_gamedata *gd);
void	move_check(int offset, int pos, t_gamedata *gd, bool *completed);
void	compare_mapsize_and_screensize(t_gamedata *gd);
void	terminate_game(t_gamedata *gd, int error);
void	win_game(t_gamedata *gd);
int		exit_game(t_gamedata *gd);
void	init_gamedata(t_gamedata *gd);
void	sl_init_ints(int *a, int *b, int *c, int *d);
int		count_collectibles(t_gamedata *gd);
void	*xpm_to_img(t_gamedata *gd, char *path, int *dummy);
int		key_hook(int keycode, void *gd);
int		background_activities(t_gamedata *gd);

#endif
