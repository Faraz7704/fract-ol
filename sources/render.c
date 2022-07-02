/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/02 15:42:54 by fkhan            ###   ########.fr       */
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

void	draw_fractol(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
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
			if (fractolinfo->formula)
				iteration = fractolinfo->formula(fractolinfo, pixel);
			else
				iteration = fractolinfo->max_iteration;
			color = get_fractol_color(fractolinfo, pixel, iteration);
			put_pixel(fractolinfo->imageinfo, pixel, get_numcolor(color));
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(appinfo->mlx, appinfo->window,
		fractolinfo->imageinfo->image, 0, 0);
}
