/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/07 00:46:12 by fkhan            ###   ########.fr       */
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

t_vector2	get_pixel_scaled(t_vector2 pixel, t_rect viewport, t_vector2 offset)
{
	t_vector2	pixel_scaled;
	double		ratio;

	ratio = min(WIDTH / viewport.size.x, HEIGHT / viewport.size.y);
	pixel_scaled.x = ((pixel.x - ((WIDTH - viewport.size.x * ratio) / 2))
			+ viewport.pos.x * ratio) / ratio + (offset.x / ratio);
	pixel_scaled.y = ((pixel.y - ((HEIGHT - viewport.size.y * ratio) / 2))
			+ viewport.pos.y * ratio) / ratio + (offset.y / ratio);
	return (pixel_scaled);
}

t_vector2	get_pixel_zoomed(t_vector2 pixel, t_rect viewport, double zoom, t_vector2 offset)
{
	t_vector2	zoom_size;
	t_vector2	pixel_zoomed;

	(void)offset;
	zoom_size.x = WIDTH / viewport.size.x * zoom;
	zoom_size.y = HEIGHT / viewport.size.y * zoom;
	pixel_zoomed.x = pixel.x * zoom;
	pixel_zoomed.y = pixel.y * zoom;
	return (pixel_zoomed);
}

void	draw_fractol(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
{
	t_vector2	pixel;
	int			iteration;
	t_color		color;

	if (!fractolinfo->formula)
		return ;
	pixel.y = 0;
	while (pixel.y < HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			iteration = fractolinfo->formula(fractolinfo, pixel);
			color = get_fractol_color(fractolinfo, pixel, iteration);
			put_pixel(fractolinfo->imageinfo, pixel, get_numcolor(color));
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(appinfo->mlx, appinfo->window,
		fractolinfo->imageinfo->image, 0, 0);
	mlx_string_put(appinfo->mlx, appinfo->window, 10, 20, 0xCCCCCC,
		"H - Help");
}

void	draw_help(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
{
	ft_bzero(fractolinfo->imageinfo->addr,
		WIDTH * HEIGHT * (fractolinfo->imageinfo->bits_per_pixel / 8));
	mlx_put_image_to_window(appinfo->mlx, appinfo->window,
		fractolinfo->imageinfo->image, 0, 0);
	mlx_string_put(appinfo->mlx, appinfo->window, (WIDTH / 2) - 70,
		(HEIGHT / 2) - 100, 0xCCCCCC, "Controls");
	mlx_string_put(appinfo->mlx, appinfo->window, (WIDTH / 2) - 70,
		(HEIGHT / 2) - 60, 0xCCCCCC, "Reset          - R");
	mlx_string_put(appinfo->mlx, appinfo->window, (WIDTH / 2) - 70,
		(HEIGHT / 2) - 30, 0xCCCCCC, "Color Shift    		- C");
	mlx_string_put(appinfo->mlx, appinfo->window, (WIDTH / 2 - 70),
		(HEIGHT / 2) - 0, 0xCCCCCC, "Move           		- Arrows");
	mlx_string_put(appinfo->mlx, appinfo->window, (WIDTH / 2) - 70,
		(HEIGHT / 2) + 30, 0xCCCCCC, "Zoom           		- Scroll");
	mlx_string_put(appinfo->mlx, appinfo->window, (WIDTH / 2) - 70,
		(HEIGHT / 2) + 60, 0xCCCCCC, "Iterations    		 - +/-");
	mlx_string_put(appinfo->mlx, appinfo->window, (WIDTH / 2) - 70,
		(HEIGHT / 2) + 110, 0xCCCCCC, "Close Help     		- H");
}
