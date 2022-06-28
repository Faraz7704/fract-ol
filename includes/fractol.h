/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/28 20:15:07 by fkhan            ###   ########.fr       */
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

# define WIDTH		1000
# define HEIGHT		1000

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
}	t_fractolinfo;

typedef struct s_appinfo
{
	void	*mlx;
	void	*window;
}	t_appinfo;

// Colors
t_color	create_trgb(int t, int r, int g, int b);

#endif