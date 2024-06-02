#include "../cub3d.h"

static void check_horizontal_walls(t_cub3d *game)
{
    int x;

    for (x = 0; x < game->map_width; x++) {
        if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1') {
            error_exit(game, "Error: Map is not surrounded by walls (horizontal check)");
        }
    }
}

static void check_vertical_walls(t_cub3d *game)
{
    int y;

    for (y = 0; y < game->map_height; y++) {
        if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1') {
            error_exit(game, "Error: Map is not surrounded by walls (vertical check)");
        }
    }
}

static void check_map_width(t_cub3d *game)
{
    int y;
    int width;

    width = ft_strlen(game->map[0]);
    for (y = 1; y < game->map_height; y++) {
        if ((int)ft_strlen(game->map[y]) != width) {
            error_exit(game, "Error: Map rows have inconsistent widths");
        }
    }
    game->map_width = width;
}

void validate_map_walls(t_cub3d *game)
{
    check_map_width(game);
    check_horizontal_walls(game);
    check_vertical_walls(game);
}
