#include <mlx.h>

int main(void)
{
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 640, 640, "the game muzafucka");
    //unsigned int display_color = mlx_get_color_value(ptr, 0xFF0000);
    //mlx_pixel_put(ptr, win_ptr, 10, 10, display_color);
    //mlx_string_put(ptr, win_ptr, 30, 30, display_color, "string blah blah blah very long!!!");

    //void *free_space = mlx_new_image(mlx_ptr, 48, 48);
    int free_space_w, free_space_h;
    void *free_space = mlx_xpm_file_to_image(mlx_ptr, "./my_assets/free_space.xpm", &free_space_w, &free_space_h);
    /*int bpp;      // You create an empty variable
    int sl;       // You create another empty variable
    int end;      // And another
    char *data = mlx_get_data_addr(img_ptr, &bpp, &sl, &end);*/
    //int pixel_offset = 639 * (bpp / 8) + 639 * sl;
    //display_color = mlx_get_color_value(ptr, 0x0000FF);
    //*((unsigned int *)(data + pixel_offset)) = display_color;
    //pixel_offset = 0 * (bpp / 8) + 0 * sl;
    //*((unsigned int *)(data + pixel_offset)) = display_color;
    //pixel_offset = 639 * (bpp / 8) + 0 * sl;
    //*((unsigned int *)(data + pixel_offset)) = display_color;
    //pixel_offset = 0 * (bpp / 8) + 639 * sl;
    //*((unsigned int *)(data + pixel_offset)) = display_color;
    //mlx_put_image_to_window(mlx_ptr, win_ptr, free_space, 0, 0);

    int wall_w, wall_h;
    void *wall = mlx_xpm_file_to_image(mlx_ptr, "./my_assets/rock.xpm", &wall_w, &wall_h);
    //mlx_put_image_to_window(mlx_ptr, win_ptr, wall, 10, 10);

    // Create a new image for the composite result
    void *composite = mlx_new_image(mlx_ptr, 48, 48);

    // Get data addresses for all images
    int free_bpp, free_sl, free_endian;
    int wall_bpp, wall_sl, wall_endian;
    int comp_bpp, comp_sl, comp_endian;

    char *free_data = mlx_get_data_addr(free_space, &free_bpp, &free_sl, &free_endian);
    char *wall_data = mlx_get_data_addr(wall, &wall_bpp, &wall_sl, &wall_endian);
    char *comp_data = mlx_get_data_addr(composite, &comp_bpp, &comp_sl, &comp_endian);

    // First copy all of free_space to the composite
    for (int y = 0; y < free_space_h; y++) {
        for (int x = 0; x < free_space_w; x++) {
            int offset = y * comp_sl + x * (comp_bpp / 8);
            *(unsigned int*)(comp_data + offset) = *(unsigned int*)(free_data + y * free_sl + x * (free_bpp / 8));
        }
    }

    // Calculate center position to overlay rock image
    int start_x = (free_space_w - wall_w) / 2;
    int start_y = (free_space_h - wall_h) / 2;

    // Then overlay wall on top, respecting transparency
    for (int y = 0; y < wall_h; y++) {
        for (int x = 0; x < wall_w; x++) {
            // Make sure we're within bounds of the composite
            if (start_y + y >= 0 && start_y + y < free_space_h &&
                start_x + x >= 0 && start_x + x < free_space_w) {

                // Get color from wall image
                int wall_offset = y * wall_sl + x * (wall_bpp / 8);
                unsigned int color = *(unsigned int*)(wall_data + wall_offset);

                // Skip transparent pixels (better check for transparency)
                if ((color & 0xFF000000) == 0) {
                    // Put color in composite at the centered position
                    int comp_offset = (start_y + y) * comp_sl + (start_x + x) * (comp_bpp / 8);
                    *(unsigned int*)(comp_data + comp_offset) = color;
                }
            }
        }
    }

    // Place the composite image at (0,0)
    mlx_put_image_to_window(mlx_ptr, win_ptr, composite, 0, 0);
    //int width, height;
    //void *img_ptr2 = mlx_xpm_file_to_image(ptr, "/home/earutiun/Downloads/sample.xpm", &width, &height);
    //mlx_put_image_to_window(ptr, win_ptr, img_ptr2, 100, 100);

    mlx_loop(mlx_ptr);
    return (0);
}
