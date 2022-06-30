/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/30 21:37:01 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	put_pixel(t_imageinfo *info, t_vector2 pixel, int color)
{
	int	pixel_pos;

	pixel_pos = (pixel.y * info->line_length)
		+ (pixel.x * (info->bits_per_pixel / 8));
	*(unsigned int *)&info->addr[pixel_pos] = color;
}

t_vector2	get_pixel_scaled(t_vector2 pixel, t_rect viewport)
{
	t_vector2	pixel_scaled;
	double		ratio;

	ratio = min(WIDTH / viewport.size.x, HEIGHT / viewport.size.y);
	pixel_scaled.x = ((pixel.x - ((WIDTH - viewport.size.x * ratio) / 2))
			+ viewport.pos.x * ratio) / ratio;
	pixel_scaled.y = ((pixel.y - ((HEIGHT - viewport.size.y * ratio) / 2))
			+ viewport.pos.y * ratio) / ratio;
	return (pixel_scaled);
}

static int	get_fractol_iteration(t_fractolinfo *fractolinfo, t_vector2	pixel)
{
	int			iteration;

	if (!ft_strncmp(fractolinfo->name, "Mandelbrot", 10))
	{
		iteration = get_mandelbrot(pixel,
				init_rect(-2.25, -1.37, 2.97, 2.74),
				fractolinfo->max_iteration);
	}
	else
		iteration = fractolinfo->max_iteration;
	return (iteration);
}

void	draw_app(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
{
	t_vector2	pixel;
	int			iteration;
	t_color		color;

	pixel.y = 0;
	while (pixel.y < HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			iteration = get_fractol_iteration(fractolinfo, pixel);
			color = get_fractol_color(pixel, iteration,
					fractolinfo->max_iteration);
			put_pixel(fractolinfo->imageinfo, pixel, get_numcolor(color));
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(appinfo->mlx, appinfo->window,
		fractolinfo->imageinfo->image, 0, 0);
}
