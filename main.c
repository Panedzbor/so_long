
#include "so_long.h"

#define TILE_WDTH 48

void	launch_game(t_gamedata *gd);
void	compare_mapsize_and_screensize(t_gamedata gd);
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
void	display_without_background(void *sprite, unsigned int background_color, t_gamedata *gd, int *coordinates);
int key_hook(int keycode, void *gd);
void	recalculate_map(t_gamedata *gd, int move);
int	set_move(int keycode, t_gamedata *gd);
bool	valid_move(int move, t_gamedata *gd);
int	exit_game(t_gamedata *gd);


int main(int argc, char *argv[])
{
	t_gamedata	gd;
	
	if (argc != 2)
		exit(0);
	init_gamedata(&gd);
	gd.map_file_name = (const char*)argv[1];
	parse_map(&gd);
	launch_game(&gd);
	return (0);
}

void	init_gamedata(t_gamedata *gd)
{
	gd->map_file_name = NULL;
	gd->map_content = NULL;
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
	gd->collectible = NULL;
	gd->exit = NULL;
	gd->main_character = NULL;
	gd->player_position = 0;
	gd->movements = 0;
}

void	launch_game(t_gamedata *gd)
{
	gd->mlx_ptr = mlx_init();
	mlx_get_screen_size(gd->mlx_ptr, &gd->screen_width, &gd->screen_height);
	compare_mapsize_and_screensize(*gd);
	gd->win_ptr = mlx_new_window(gd->mlx_ptr, gd->map_width_px, gd->map_height_px, "Kolobok's Breakout");
	draw_map(gd);
	display_sprites(gd);
	mlx_key_hook(gd->win_ptr, key_hook, gd);
	//mlx_mouse_hook(gd->win_ptr, mouse_hook, gd);
	mlx_hook(gd->win_ptr, 17, 0, exit_game, gd);
	mlx_loop(gd->mlx_ptr);

}

/* int mouse_hook(int button, int x, int y, void *gd)
{

} */

int	exit_game(t_gamedata *gd)
{
	mlx_destroy_image(gd->mlx_ptr, gd->main_character);
	mlx_destroy_image(gd->mlx_ptr, gd->wall);
	mlx_destroy_image(gd->mlx_ptr, gd->free_space);
	mlx_destroy_image(gd->mlx_ptr, gd->collectible);
	mlx_destroy_image(gd->mlx_ptr, gd->exit);
	mlx_destroy_window(gd->mlx_ptr, gd->win_ptr);
	mlx_destroy_display(gd->mlx_ptr);
	free(gd->map_content);
	gd->map_content = NULL;
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
	}
	if (keycode == 0xff1b)
		exit_game(gd);
	return (0);
}

bool	valid_move(int move, t_gamedata *gd)
{
	if (gd->map_content[gd->player_position + move] == '1')
		return (false);
	return (true);
}

void	recalculate_map(t_gamedata *gd, int move)
{
	gd->map_content[gd->player_position] = '0';
	gd->player_position += move;
	gd->map_content[gd->player_position] = 'P';
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

	if (!gd->main_character)
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
	int	coordinates[2];
	int	offset;

	coordinates[0] = i;
	coordinates[1] = j;
	offset = j + i * (gd->map_width + 1);
	if (gd->map_content[offset] == 'P')
	{
		display_without_background(gd->main_character, 0x000000, gd, coordinates);
		gd->player_position = offset;
	}
}

void	display_without_background(void *sprite, unsigned int background_color, t_gamedata *gd, int *coordinates)
{
	int	x;
	int	y;
	unsigned int	color;
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
				mlx_pixel_put(gd->mlx_ptr, gd->win_ptr, coordinates[1] * TILE_WDTH + x, coordinates[0] * TILE_WDTH + y, color);
			x++;
		}
		y++;
	}
}

void	set_sprites(t_gamedata *gd)
{
	static int		dummy;

	gd->main_character = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/kol.xpm", &dummy, &dummy);
}

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

void	choose_tile_to_display(t_gamedata *gd, int i, int j)
{
	if (gd->map_content[j + i * (gd->map_width + 1)] == '1')
		mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->wall, j * TILE_WDTH, i * TILE_WDTH);
	else if (gd->map_content[j + i * (gd->map_width + 1)] == 'C')
		mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->collectible, j * TILE_WDTH, i * TILE_WDTH);
	else if (gd->map_content[j + i * (gd->map_width + 1)] == 'E')
		mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->exit, j * TILE_WDTH, i * TILE_WDTH);
	else
		mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->free_space, j * TILE_WDTH, i * TILE_WDTH);
}

void	set_tiles(t_gamedata *gd)
{
	static int		dummy;

	gd->free_space = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/free_space.xpm", &dummy, &dummy);
	gd->wall = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/rock2.xpm", &dummy, &dummy);
	gd->collectible = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/collectible2.xpm", &dummy, &dummy);
	gd->exit = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/Hole.xpm", &dummy, &dummy);
}

void	compare_mapsize_and_screensize(t_gamedata gd)
{
	if (gd.map_width_px > gd.screen_width || gd.map_height_px > gd.screen_height)
		exit(0);
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
}

bool	valid_walls(t_gamedata *gd)
{
	int i;
	char	ch;

	while (gd->map_content[i])
	{
		ch = gd->map_content[i];
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
	while (gd->map_content[i])
	{
		if (gd->map_content[i] == '\n')
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

	init_ints(&i, &c, &e, &p);
	while (gd->map_content[i])
	{
		ch = gd->map_content[i];
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

void	init_ints(int *a, int *b, int *c, int *d)
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
	while (gd->map_content[i])
	{
		if (!ft_strchr(allowed_chars, gd->map_content[i]))
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
}

int	count_map_size(t_gamedata *gd)
{
	int	count;
	char	buf[1];
	int	read_check;
	
	gd->map_fd = open(gd->map_file_name, 0);
	if (gd->map_fd == -1)
		exit(0);
	count = 0;
	read_check = 1;
	while (read_check > 0)
	{
		read_check = read(gd->map_fd, buf, 1);
		if (read_check > 0)
			count++;
	}
	if (read_check == -1)
		exit(0);
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
		exit(0);
}

void	allocate_memory_for_map(t_gamedata *gd, int map_size)
{
	gd->map_content = (char *)ft_calloc(map_size + 1, sizeof(char));
	if (!gd->map_content)
		exit(0);
}

void	read_map(t_gamedata *gd, int map_size)
{
	if (read(gd->map_fd, gd->map_content, map_size) != map_size)
		exit(0);	
}

void	get_map_dimensions(t_gamedata *gd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (gd->map_content[i])
	{
		if (gd->map_width == 0 && gd->map_content[i] != '\n')
			count++;
		if (gd->map_width == 0 && gd->map_content[i] == '\n')
			gd->map_width = count;
		if (gd->map_content[i] == '\n')
			gd->map_height = ++count - gd->map_width;
		i++;
	}
	gd->map_height++;
	gd->map_width_px = gd->map_width * TILE_WDTH;
	gd->map_height_px = gd->map_height * TILE_WDTH;
}

