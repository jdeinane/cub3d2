/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubaldo <jubaldo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:17:11 by jubaldo           #+#    #+#             */
/*   Updated: 2024/07/22 16:09:05 by jubaldo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <ctype.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define NUM_TEXTURES 4

# define KEY_ESC 65307
# define KEY_W 'w'
# define KEY_A 'a'
# define KEY_S 's'
# define KEY_D 'd'
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_texture {
	char	*path;
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_keys {
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_ray {
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_draw_params
{
	int		draw_start;
	int		draw_end;
	int		texture_x;
	int		texture_index;
	int		color;
	double	texture_pos;
	double	step;
	double	wall_x;
}	t_draw_params;

typedef struct s_parse_state {
	int		parsing_map;
	int		textures_parsed[4];
	int		colors_parsed[2];
}	t_parse_state;

typedef struct s_map_info
{
	char	**map_lines;
	int		map_height;
	int		player_count;
	bool	map_ended;
}	t_map_info;

typedef struct s_cub3d {
	void		*mlx;
	void		*win;
	void		*img;
	int			*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	int			win_width;
	int			win_height;
	t_player	player;
	t_texture	textures[NUM_TEXTURES];
	t_color		floor_color;
	t_color		ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	t_keys		keys;
}	t_cub3d;

// INIT
void	init_game(t_cub3d *game);
void	init_cub3d(t_cub3d *game);

// PARSING
void	parse_file(t_cub3d *game, const char *filename);
void	parse_textures(t_cub3d *game, char *line);
void	parse_color(t_cub3d *game, char *line);
void	parse_map(t_cub3d *game, char *line);
void	parse_args(int ac, char **av);
void	validate_map(t_cub3d *game);
void	add_line_to_map(t_cub3d *game, char **map_lines,
			char *line, int map_height);
char	**allocate_new_map_lines(t_cub3d *game, char **map_lines,
			int map_height);
bool	is_valid_map_line(const char *line, int *player_count);
void	initialize_static_variables(t_map_info *map_info);
void	handle_map_line(t_cub3d *game, char *line, t_map_info *map_info);

// CHECK MAP
void	check_vertical_boundaries(t_cub3d *game);
void	check_player_position_surroundings(t_cub3d *game);
void	check_zeroes_below_in_second_to_last_row(t_cub3d *game);
void	check_extended_row_enclosures(t_cub3d *game);
void	check_horizontal_boundaries(t_cub3d *game);
bool	is_row_completely_empty(const char *row);
void	check_left_boundary2(t_cub3d *game, int y);
void	check_right_boundary2(t_cub3d *game, int y);
void	check_top_bottom_boundary2(t_cub3d *game, int y, int len);
void	validate_section(t_cub3d *game, int start, int end);
void	process_section(t_cub3d *game, bool *in_section,
			int *current_section_start, int y);
void	start_new_section(bool *in_section,
			int *current_section_start, int y);
void	check_for_multiple_sections(t_cub3d *game);
void	check_left_space(t_cub3d *game, int y, int x);
void	check_right_space(t_cub3d *game, int y, int x, int length);

// EVENTS
int		handle_keypress(int keycode, t_cub3d *game);
int		handle_keyrelease(int keycode, t_cub3d *game);

// RAYCASTING
void	calc_perp_wall_dist(t_cub3d *game, t_ray *ray);
void	calc_line_height(t_cub3d *game, t_ray *ray);
double	calculate_wall_x(t_cub3d *game, t_ray *ray);
int		calculate_texture_x(double wall_x, t_ray *ray);
void	init_draw_params(t_cub3d *game, t_ray *ray, t_draw_params *params);
void	draw_line(t_cub3d *game, int x, t_ray *ray);
void	draw_floor_and_ceiling(t_cub3d *game);
void	init_ray(t_cub3d *game, t_ray *ray, int x);
void	perform_dda(t_cub3d *game, t_ray *ray);
void	perform_raycasting(t_cub3d *game);

// PLAYER
void	rotate_left(t_cub3d *game, double rot_speed);
void	rotate_right(t_cub3d *game, double rot_speed);
void	move_forward(t_cub3d *game, double move_speed);
void	move_backward(t_cub3d *game, double move_speed);
void	move_left(t_cub3d *game, double move_speed);
void	move_right(t_cub3d *game, double move_speed);
void	update_player(t_cub3d *game);

// UTILS
void	error_exit(t_cub3d *game, const char *msg);
void	error_exit2(t_cub3d *game, const char *msg, char *line_to_free);
int		handle_exit(t_cub3d *game);
void	clean_exit(t_cub3d *game);
void	free_tokens(char **tokens);
void	free_resources(t_cub3d *game);
int		is_within_bounds(t_cub3d *game, double x, double y);
bool	is_enclosed(char c);
bool	is_valid_surrounding(char c);
void	set_parsing_map_flag(int *parsing_map, char *line);
void	handle_texture_parsing(t_cub3d *game, char *line, \
		t_parse_state *state, int index);
void	handle_color_parsing(t_cub3d *game, char *line, \
		t_parse_state *state, int index);
void	check_missing_definitions(t_cub3d *game, t_parse_state *state);
void	handle_parsing(t_cub3d *game, char *line, t_parse_state *state);
void	process_line(t_cub3d *game, char *line, t_parse_state *state);
void	process_remaining_line(t_cub3d *game, char *line, t_parse_state *state);
void	process_file_lines(t_cub3d *game, int fd, t_parse_state *state);
void	set_north_direction(t_cub3d *game);
void	set_south_direction(t_cub3d *game);
void	set_east_direction(t_cub3d *game);
void	set_west_direction(t_cub3d *game);
void	set_player_direction(t_cub3d *game, char direction);
void	set_player_position(t_cub3d *game, int x, int y, char direction);
int		find_initial_position(t_cub3d *game, int *x, int *y);
void	init_player_position(t_cub3d *game);
void	parse_line(t_cub3d *game, char *line, t_parse_state *state);
char	*trim_leading_whitespace(char *line);
void	open_file(t_cub3d *game, const char *filename, int *fd);

// GNL
int		get_next_line(int fd, char **line);

// LIBFT
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_atoi(const char *str);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	*ft_strdup(const char *s);
int		ft_strlen(char const *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strtok_r(char *str, const char *delim, char **saveptr);
long	ft_strtol(const char *str, char **endptr, int base);
int		ft_isspace(char c);

#endif