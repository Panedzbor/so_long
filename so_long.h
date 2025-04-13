
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include <X11/keysymdef.h>
# include <math.h>

# define TILE_WDTH 48

typedef struct  s_spite_frames
{
    void    *sprite_frames[5];
    int     current;
} t_frames;

typedef struct s_gamedata
{
    const char  *map_file_name;
    char  *map;
    char  *map_copy;
    int         map_fd;
    int         map_width;
    int         map_height;
    int         map_width_px;
    int         map_height_px;
    int         screen_width;
    int         screen_height;
    void    *mlx_ptr;
    void    *win_ptr;
    void    *wall;
    void    *wall_hor;
    void    *free_space;
    void    *collectible;
    void    *exit;
    void    *exitopen;
    t_frames    main_character;
    int     player_position;
    int     movements;
} t_gamedata;

typedef struct s_imagedata
{
    int bpp;          
    int size_line;    
    int endian;       
    char *data;  
} t_imagedata;
