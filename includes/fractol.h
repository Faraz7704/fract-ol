/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/02 15:43:13 by fkhan            ###   ########.fr       */
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

# define WIDTH		800
# define HEIGHT		800

typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

typedef struct s_color
{
	int8_t	channel[4];
}	t_color;

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
	t_rect			viewport;
	int				(*formula)(struct s_fractolinfo *, t_vector2);
}	t_fractolinfo;

typedef struct s_appinfo
{
	void	*mlx;
	void	*window;
}	t_appinfo;

// init
t_appinfo		*init_app(char *name);
t_fractolinfo	*init_fractolinfo(char *name, int max_iteration,
					t_appinfo *appinfo);
t_imageinfo		*init_imageinfo(void *mlx);

// render
void			draw_fractol(t_appinfo *appinfo, t_fractolinfo *fractolinfo);
t_vector2		get_pixel_scaled(t_vector2 pixel, t_rect viewport);

// math_utils
t_vector2		init_vector2(double x, double y);
t_rect			init_rect(double x, double y, double w, double h);
double			min(double num1, double num2);

// str_utils
int				str_equal(char *str1, char *str2);

// mandelbrot
int				get_mandelbrot(t_fractolinfo *info, t_vector2 pixel);

// rectangle
int				get_rectangle(t_fractolinfo *info, t_vector2 pixel);

// colors
t_color			create_trgb(int t, int r, int g, int b);
int				get_numcolor(t_color color);
t_color			get_fractol_color( t_fractolinfo *info, t_vector2 pixel,
					int iteration);

#endif