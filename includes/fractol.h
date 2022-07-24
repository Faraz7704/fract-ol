/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/24 22:15:48 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "ft_printf.h"
# include "debug_log.h"
# include <mlx.h>
# include <math.h>
# include <stdint.h>

# define WIDTH			1000
# define HEIGHT			1000
# define ZOOM_FACTOR 	2

typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

typedef struct s_color
{
	int8_t	channel[4];
}	t_color;

typedef struct s_palette
{
	t_color	*colors;
	int		size;
}	t_palette;

typedef struct s_rect
{
	t_vector2		pos;
	t_vector2		size;
}	t_rect;

typedef struct s_imageinfo
{
	void			*image;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_imageinfo;

typedef struct s_fractolinfo
{
	char			*name;
	t_imageinfo		*imageinfo;
	int				max_iteration;
	int				(*formula)(struct s_fractolinfo *, t_vector2);
	t_rect			viewport;
	int				palette_index;
	t_vector2		vp_offset;
	double			zoom;
	t_vector2		zoom_offset;
	t_vector2		complex;
	t_vector2		mouse_pos;
	int				is_fixed_mouse;
	int				is_help;
}	t_fractolinfo;

typedef struct s_appinfo
{
	void	*mlx;
	void	*window;
}	t_appinfo;

typedef struct s_event_data
{
	t_appinfo		*appinfo;
	t_fractolinfo	*fractolinfo;
}	t_event_data;

enum {
	ON_MOUSE_SCROLL_UP = 4,
	ON_MOUSE_SCROLL_DOWN = 5,
	ON_ARROW_LEFT = 123,
	ON_ARROW_RIGHT = 124,
	ON_ARROW_UP = 126,
	ON_ARROW_DOWN = 125,
	ON_KEY_PLUS = 24,
	ON_KEY_MINUS = 27,
	ON_NUMPAD_PLUS = 69,
	ON_NUMPAD_MINUS = 78,
	ON_KEY_ESC = 53,
	ON_KEY_H = 4,
	ON_KEY_R = 15,
	ON_KEY_F = 3,
	ON_KEY_C = 8,
	ON_KEY_1 = 18,
	ON_KEY_2 = 19,
	ON_KEY_3 = 20
};

// fractol
int				exit_app(t_event_data *event_data);

// init
t_appinfo		*init_app(char *name);
t_fractolinfo	*init_fractolinfo(char *name, int max_iteration,
					t_appinfo *appinfo, t_vector2 complex);
t_imageinfo		*init_imageinfo(void *mlx);
void			fractol_reset(t_fractolinfo	*info);
void			init_formula(t_fractolinfo	*info);

// events
t_event_data	init_event_data(t_appinfo *appinfo, t_fractolinfo *fractolinfo);
void			register_events(t_appinfo *appinfo, t_event_data *event_data);

// render
void			draw_fractol(t_appinfo *appinfo, t_fractolinfo *fractolinfo);
t_vector2		get_pixel_scaled(t_vector2 pixel, t_rect viewport,
					t_vector2 offset);
t_vector2		get_pixel_zoomed(t_vector2 pixel, double zoom,
					t_vector2 offset);
void			draw_help(t_appinfo *appinfo, t_fractolinfo *fractolinfo);

// math_utils
t_vector2		init_vector2(double x, double y);
t_rect			init_rect(double x, double y, double w, double h);
double			min(double num1, double num2);

// str_utils
int				str_equal(char *str1, char *str2);

// mandelbrot
int				get_mandelbrot(t_fractolinfo *info, t_vector2 pixel);

// julia_set
int				get_julia_set(t_fractolinfo *info, t_vector2 pixel);

// burning_ship
int				get_burning_ship(t_fractolinfo *info, t_vector2 pixel);

// colors
t_color			create_trgb(int t, int r, int g, int b);
int				get_numcolor(t_color color);
t_color			get_fractol_color( t_fractolinfo *info, t_vector2 pixel,
					int iteration);

// mouse
int				mouse_down_handler(int button, int x, int y,
					t_event_data *data);
int				mouse_move_handler(int x, int y, t_event_data *data);

// keyboard
int				key_down_handler(int button, t_event_data	*data);

// controls
void			reset_control(t_event_data *data);
void			move_control(int button, t_event_data *data);
void			change_max_iteration(int button, t_event_data *data);
void			fix_mouse_movement(t_event_data *data);
void			change_fractol(int button, t_event_data *data);

// palette
t_palette		get_palette(int index);

#endif