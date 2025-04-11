
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_gamedata
{
    const char  *map_file_name;
    char  *map_content;
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
    void    *free_space;
    void    *collectible;
} t_gamedata;