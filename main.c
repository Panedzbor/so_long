
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
}

void	launch_game(t_gamedata *gd)
{
	gd->mlx_ptr = mlx_init();
	mlx_get_screen_size(gd->mlx_ptr, &gd->screen_width, &gd->screen_height);
	compare_mapsize_and_screensize(*gd);
	gd->win_ptr = mlx_new_window(gd->mlx_ptr, gd->map_width_px, gd->map_height_px, "Kolobok's Breakout");
	draw_map(gd);

	
	mlx_loop(gd->mlx_ptr);

}

void	draw_map(t_gamedata *gd)
{
	static int	i;
	static int	j;

	set_tiles(gd);

	while (i < gd->map_height)
	{
		j = 0;
		while (j < gd->map_width)
		{
			if (gd->map_content[j + i * (gd->map_width + 1)] == '1')
				mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->wall, j * TILE_WDTH, i * TILE_WDTH);
			else
				mlx_put_image_to_window(gd->mlx_ptr, gd->win_ptr, gd->free_space, j * TILE_WDTH, i * TILE_WDTH);
			j++;
		}
		i++;
	}
}

void	set_tiles(t_gamedata *gd)
{
	static int		dummy;

	gd->free_space = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/free_space.xpm", &dummy, &dummy);
	gd->wall = mlx_xpm_file_to_image(gd->mlx_ptr, "./my_assets/rock2.xpm", &dummy, &dummy);
}

void	compare_mapsize_and_screensize(t_gamedata gd)
{
	if (gd.map_width_px > gd.screen_width || gd.map_height_px > gd.screen_height)
		exit(0);
}

void	parse_map(t_gamedata *gd)
{
	extract_map(gd);
	get_map_dimensions(gd);
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
	gd->map_content = (char *)ft_calloc(map_size, sizeof(char));
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

