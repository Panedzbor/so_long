
#include "so_long.h"

void	launch_game(t_gamedata *gd);
void	compare_mapsize_and_screensize(t_gamedata *gd);
void	parse_map(t_gamedata *gd);
void	get_map_dimensions(t_gamedata *gd);
void	init_gamedata(t_gamedata *gd);
void	open_map(t_gamedata *gd);
void	extract_map(t_gamedata *gd);
int	count_map_size(t_gamedata *gd);
void	save_map(t_gamedata *gd, int map_size);
void	allocate_memory_for_map(t_gamedata *gd, int map_size);
void	read_map(t_gamedata *gd, int map_size);
void	draw_map(t_gamedata *gd);
void	set_tiles(t_gamedata *gd);
void	choose_tile_to_display(t_gamedata *gd, int i, int j);
void	display_sprites(t_gamedata *gd);
void	choose_sprite_to_display(t_gamedata *gd, int i, int j);
void	set_sprites(t_gamedata *gd);
void	display_without_background(void *sprite, t_gamedata *gd, int i, int j);
int key_hook(int keycode, void *gd);
void	recalculate_map(t_gamedata *gd, int move);
int	set_move(int keycode, t_gamedata *gd);
bool	valid_move(int move, t_gamedata *gd);
int	exit_game(t_gamedata *gd);
void	terminate_game(t_gamedata *gd, int error);
int	validate_map(t_gamedata *gd);
bool	valid_path(t_gamedata *gd, int pos);
void	move(int offset, int pos, t_gamedata *gd, bool *completed);
bool	check_if_completed(char *map);
bool	valid_walls(t_gamedata *gd);
bool	valid_shape(t_gamedata *gd);
int	valid_amount(t_gamedata *gd);
void	sl_init_ints(int *a, int *b, int *c, int *d);
bool	valid_chars(t_gamedata *gd);
void	win_game(t_gamedata *gd);
int	background_animation(t_gamedata *gd);

int main(int argc, char *argv[])
{
	t_gamedata	gd;
	
	if (argc != 2)
	{
		ft_printf("Error\nProgram expects one argument\n");
		exit(0);
	}
	init_gamedata(&gd);
	gd.map_file_name = (const char*)argv[1];
	parse_map(&gd);
	launch_game(&gd);
	return (0);
}

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
	gd->collectible = NULL;
	gd->exit = NULL;
	gd->exitopen = NULL;
	gd->main_character.sprite_frames[0] = NULL;
	gd->player_position = 0;
	gd->movements = 0;
}

void	launch_game(t_gamedata *gd)
{
	gd->mlx_ptr = mlx_init();
	mlx_get_screen_size(gd->mlx_ptr, &gd->screen_width, &gd->screen_height);
	compare_mapsize_and_screensize(gd);
	gd->win_ptr = mlx_new_window(gd->mlx_ptr, gd->map_width_px, gd->map_height_px, "Kolobok's Breakout");
	draw_map(gd);
	display_sprites(gd);
	mlx_key_hook(gd->win_ptr, key_hook, gd);
	//mlx_mouse_hook(gd->win_ptr, mouse_hook, gd);
	mlx_hook(gd->win_ptr, 17, 0, exit_game, gd);
	mlx_loop_hook(gd->mlx_ptr, background_animation, gd);
	mlx_loop(gd->mlx_ptr);

}

int	background_animation(t_gamedata *gd)
{
	static int counter;

	if (counter == 3000)
	{
		ft_printf("animation\n");
		draw_map(gd);
		display_sprites(gd);
		counter = 0;
	}
	counter++;
	return (0);
}

int	exit_game(t_gamedata *gd)
{
	if (gd->main_character.sprite_frames[0])
	{
		mlx_destroy_image(gd->mlx_ptr, gd->main_character.sprite_frames[0]);
		mlx_destroy_image(gd->mlx_ptr, gd->wall);
		mlx_destroy_image(gd->mlx_ptr, gd->wall_hor);
		mlx_destroy_image(gd->mlx_ptr, gd->free_space);
		mlx_destroy_image(gd->mlx_ptr, gd->collectible);
		mlx_destroy_image(gd->mlx_ptr, gd->exit);
		mlx_destroy_image(gd->mlx_ptr, gd->exitopen);
		mlx_destroy_window(gd->mlx_ptr, gd->win_ptr);
	}
	if (gd->mlx_ptr)
		mlx_destroy_display(gd->mlx_ptr);
	free(gd->map);
	free(gd->map_copy);
	gd->map = NULL;
	gd->map_copy = NULL;
	exit(0);
	return (0);
}

int key_hook(int keycode, void *gd)
{
	int	move;

	move = set_move(keycode, gd);
	if (move)
	{
		if (!valid_move(move, gd))
			return (0);
		recalculate_map(gd, move);
		draw_map(gd);
		display_sprites(gd);
		((t_gamedata*)gd)->movements++;
		ft_printf("Current number of movements: %d\n", ((t_gamedata*)gd)->movements);
		if (check_if_completed(((t_gamedata*)gd)->map))
			win_game(gd);
	}
	if (keycode == 0xff1b)
		exit_game(gd);
	return (0);
}

void	win_game(t_gamedata *gd)
{
	char	*score_str;
	char	*score;
	
	mlx_string_put(gd->mlx_ptr, gd->win_ptr, 100, 100, 0xFFFFFF, "YOU WIN!");
	score = ft_itoa(gd->movements);
	score_str = ft_strjoin("Score: ", score);
	mlx_string_put(gd->mlx_ptr, gd->win_ptr, 100, 110, 0xFFFFFF, score_str);
	free(score);
	free(score_str);
	exit_game(gd);
}

bool	valid_move(int move, t_gamedata *gd)
{
	if (gd->map[gd->player_position + move] == '1')
		return (false);
	return (true);
}

void	recalculate_map(t_gamedata *gd, int move)
{
	if (!ft_strchr(gd->map, 'E'))
		gd->map[gd->player_position] = 'E';
	else
		gd->map[gd->player_position] = '0';
	gd->player_position += move;
	gd->map[gd->player_position] = 'P';
}

int	set_move(int keycode, t_gamedata *gd)
{
	if (keycode == 0x0061 || keycode == 0x0041)
		return (-1);
	if (keycode == 0x0064 || keycode == 0x0044)
		return (1);
	if (keycode == 0x0077 || keycode == 0x0057)
		return (-(gd->map_width + 1));
	if (keycode == 0x0073 || keycode == 0x0053)
		return (gd->map_width + 1);
	return (0);
}

void	display_sprites(t_gamedata *gd)
{
	int	i;
	int	j;

	if (!gd->main_character.sprite_frames[0])
		set_sprites(gd);
	i = 0;
	while (i < gd->map_height)
	{
		j = 0;
		while (j < gd->map_width)
		{
			choose_sprite_to_display(gd, i, j);
			j++;
		}
		i++;
	}
}

void	choose_sprite_to_display(t_gamedata *gd, int i, int j)
{
	int	offset;
	static int	dir;
	static int counter;
	
	/* coordinates[0] = i;
	coordinates[1] = j; */
	offset = j + i * (gd->map_width + 1);
	if (gd->map[offset] == 'P')
		{display_without_background(gd->main_character.sprite_frames[counter], gd, i, j);//background color not needed
			ft_printf("counter %d\n", counter);
			if (!dir)
		counter++;
	else
		counter--;
	if (counter == 4)
		dir = 1;
	if (counter == 0)
		dir = 0;
		}
}

void	display_without_background(void *sprite, t_gamedata *gd, int i, int j)
{
	int	x;
	int	y;
	unsigned int	color;
	unsigned int background_color;
	t_imagedata	id;

	//background_color = mlx_get_color_value(gd->mlx_ptr, background_color);
	id.data = mlx_get_data_addr(sprite, &id.bpp, &id.size_line, &id.endian);
	background_color = *(unsigned int*)id.data;
	y = 0;
	while (y < TILE_WDTH)
	{
		x = 0;
		while (x < TILE_WDTH)
		{
			color = *(unsigned int *)(id.data + y * id.size_line + x * (id.bpp / 8));
			if (color != background_color)
				mlx_pixel_put(gd->mlx_ptr, gd->win_ptr, j * TILE_WDTH + x, i * TILE_WDTH + y, color);
			x++;
		}
		y++;
	}
}

void	set_sprites(t_gamedata *gd)
{
	static int		dummy;

	gd->main_character.sprite_frames[0] = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/kol(2).xpm", &dummy, &dummy);
	gd->main_character.sprite_frames[1] = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/kol(1).xpm", &dummy, &dummy);
	gd->main_character.sprite_frames[2] = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/kol.xpm", &dummy, &dummy);
	gd->main_character.sprite_frames[3] = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/kol(3).xpm", &dummy, &dummy);
	gd->main_character.sprite_frames[4] = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/kol(4).xpm", &dummy, &dummy);
}

void	draw_map(t_gamedata *gd)
{
	int	i;
	int	j;

	if (!gd->main_character.sprite_frames[0])
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

void	choose_tile_to_display(t_gamedata *gd, int i, int j)
{
	mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->free_space, j * TILE_WDTH, i * TILE_WDTH);
	if (gd->map[j + i * (gd->map_width + 1)] == '1' && (i == 0 || i == gd->map_height - 1))
		mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->wall_hor, j * TILE_WDTH, i * TILE_WDTH);
	else if(gd->map[j + i * (gd->map_width + 1)] == '1')
		mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->wall, j * TILE_WDTH, i * TILE_WDTH);
	else if (gd->map[j + i * (gd->map_width + 1)] == 'C')
		//mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->collectible, j * TILE_WDTH, i * TILE_WDTH);
		display_without_background(gd->collectible, gd, i, j);
	else if (gd->map[j + i * (gd->map_width + 1)] == 'E' && ft_strchr(gd->map, 'C'))
		//mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->exit, j * TILE_WDTH, i * TILE_WDTH);
		display_without_background(gd->exit, gd, i, j);
	else if (gd->map[j + i * (gd->map_width + 1)] == 'E')
		display_without_background(gd->exitopen, gd, i, j);
	else if (!ft_strchr(gd->map, 'E') && gd->map[j + i * (gd->map_width + 1)] == 'P')
		display_without_background(gd->exit, gd, i, j);
}

void	set_tiles(t_gamedata *gd)
{
	static int		dummy;

	gd->free_space = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/floor3.xpm", &dummy, &dummy);
	gd->wall = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/wall.xpm", &dummy, &dummy);
	gd->wall_hor = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/wall-hor.xpm", &dummy, &dummy);
	gd->collectible = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/flour2.xpm", &dummy, &dummy);
	gd->exit = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/door-closed.xpm", &dummy, &dummy);
	gd->exitopen = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/door-open.xpm", &dummy, &dummy);
}

void	compare_mapsize_and_screensize(t_gamedata *gd)
{
	if (gd->map_width_px > gd->screen_width || gd->map_height_px > gd->screen_height)
	{
		ft_printf("Error\nMap dimensions exceed the current screen characteristics. Please use a smaller map or buy a new screen\n");
		exit_game(gd);
	}
}

void	parse_map(t_gamedata *gd)
{
	int	error;

	extract_map(gd);
	get_map_dimensions(gd);
	error = validate_map(gd);
	if (error)
		terminate_game(gd,error);
}

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

int	validate_map(t_gamedata *gd)
{
	int		ammount_error;

	if (!valid_chars(gd))
		return (1);
	ammount_error = valid_amount(gd);
	if (ammount_error)
		return (ammount_error);
	if (!valid_shape(gd))
		return (5);
	if (!valid_walls(gd))
		return (6);
	gd->player_position = (int)(ft_strchr(gd->map, 'P') - gd->map);
	if (!valid_path(gd, gd->player_position))
		return (7);
	return (0);
}

bool	valid_path(t_gamedata *gd, int pos)
{
	int	up;
	int	right;
	int	down;
	int	left;
	static bool completed;
	
	up = -(gd->map_width + 1);
	right = 1;
	down = gd->map_width + 1;
	left = -1;
	if (!completed)
		move(up, pos, gd, &completed);
	if (!completed)
		move(right, pos, gd, &completed);
	if (!completed)
		move(down, pos, gd, &completed);
	if (!completed)
		move(left, pos, gd, &completed);
	return (completed);
}

void	move(int offset, int pos, t_gamedata *gd, bool *completed)
{
	if (gd->map_copy[pos + offset] != '1' && gd->map_copy[pos + offset] != 'P')
	{
		gd->map_copy[pos + offset] = 'P';
		*completed = check_if_completed(gd->map_copy);
		valid_path(gd, pos + offset);
	}
}

bool	check_if_completed(char *map)
{
	if (ft_strchr(map, 'C') || ft_strchr(map, 'E'))
		return (false);
	return (true);
}

bool	valid_walls(t_gamedata *gd)
{
	int i;
	char	ch;

	while (gd->map[i])
	{
		ch = gd->map[i];
		if (i < gd->map_width && ch != '1')
			return (false);
		if (i >= (gd->map_width + 1) * (gd->map_height - 1) && ch != '1')
			return (false);
		if (i % (gd->map_width + 1) == 0 && ch != '1')
			return (false);
		if ((i + 2) % (gd->map_width + 1) == 0 && ch != '1')
			return (false);
		i++;
	}
	return (true);
}

bool	valid_shape(t_gamedata *gd)
{
	int	row_len;
	int	i;

	row_len = 0;
	i = 0;
	while (gd->map[i])
	{
		if (gd->map[i] == '\n')
		{
			if (row_len != gd->map_width)
					return (false);
			row_len = 0;
		}
		else
			row_len++;
		i++;
	}
	if (row_len != gd->map_width)
		return (false);
	return (true);
}

int	valid_amount(t_gamedata *gd)
{
	int	i;
	int c;
	int e;
	int p;
	char ch;

	sl_init_ints(&i, &c, &e, &p);
	while (gd->map[i])
	{
		ch = gd->map[i];
		if (ch == 'C')
			c++;
		else if (ch == 'E')
			e++;
		else if (ch == 'P')
			p++;
		i++;
	}
	if (c <= 0)
		return (2);
	if (e != 1)
		return (3);
	if (p != 1)
		return (4);
	return (0);
}

void	sl_init_ints(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

bool	valid_chars(t_gamedata *gd)
{
	const char	*allowed_chars;
	int	i;

	allowed_chars = "01CEP\n";
	while (gd->map[i])
	{
		if (!ft_strchr(allowed_chars, gd->map[i]))
			return (false);
		i++;
	}
	return (true);
}

void	extract_map(t_gamedata *gd)
{
	int	map_size;

	map_size = count_map_size(gd);
	save_map(gd, map_size);
	gd->map_copy = ft_strdup(gd->map);
}

int	count_map_size(t_gamedata *gd)
{
	int	count;
	char	buf[1];
	int	read_check;
	
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

void	save_map(t_gamedata *gd, int map_size)
{
	open_map(gd);
	allocate_memory_for_map(gd, map_size);
	read_map(gd, map_size);
	close(gd->map_fd);
}

void	open_map(t_gamedata *gd)
{
	gd->map_fd = open(gd->map_file_name, 0);
	if (gd->map_fd == -1)
	{
		ft_printf("Error\nError opening the map\n");
		exit(0);
	}
}

void	allocate_memory_for_map(t_gamedata *gd, int map_size)
{
	gd->map = (char *)ft_calloc(map_size + 1, sizeof(char));
	if (!gd->map)
	{
		ft_printf("Error\nError allocating memory for the map\n");
		exit(0);
	}
}

void	read_map(t_gamedata *gd, int map_size)
{
	if (read(gd->map_fd, gd->map, map_size) != map_size)
	{
		ft_printf("Error\nError reading the map\n");
		free(gd->map);
		gd->map = NULL;
		exit(0);	
	}
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
	gd->map_height++;
	gd->map_width_px = gd->map_width * TILE_WDTH;
	gd->map_height_px = gd->map_height * TILE_WDTH;
}

