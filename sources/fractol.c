/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/28 20:36:18 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	exit_app(void *param)
{
	(void)param;
	exit(0);
}

static t_imageinfo	*init_imageinfo(void *mlx)
{
	t_imageinfo	*info;

	info = malloc(sizeof(t_imageinfo));
	if (!info)
		debug_log(ERR_IMAGE_INIT);
	info->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!info->image)
		debug_log(ERR_IMAGE_INIT);
	info->addr = mlx_get_data_addr(
		info->image,
		&info->bits_per_pixel,
		&info->line_length,
		&info->endian);
	return (info);
}

static t_fractolinfo	*init_fractolinfo(char *name, int max_iteration, t_appinfo *appinfo)
{
	t_fractolinfo	*info;

	info = malloc(sizeof(t_fractolinfo));
	if (!info)
		debug_log(ERR_FRACTOL_INIT);
	info->name = name;
	info->imageinfo = init_imageinfo(appinfo->mlx);
	info->max_iteration = max_iteration;
	return (info);
}

t_appinfo	*init_app(char *name)
{
	t_appinfo	*info;

	info = malloc(sizeof(t_appinfo));
	if (!info)
		debug_log(ERR_APP_INIT);
	info->mlx = mlx_init();
	info->window = mlx_new_window(info->mlx, WIDTH, HEIGHT, name);
	if (!info->window)
		debug_log(ERR_WINDOW_INIT);
	mlx_hook(info->window, 17, 0, exit_app, NULL);
	return (info);
}

void	put_pixel(t_imageinfo *info, t_vector2 pixel, t_color color)
{
	int		pixel_pos;

	pixel_pos = (pixel.y * info->line_length)
		+ (pixel.x * (info->bits_per_pixel / 8));
	*(unsigned int *)&info->addr[pixel_pos] = color.channel[3];
	*(unsigned int *)&info->addr[++pixel_pos] = color.channel[2];
	*(unsigned int *)&info->addr[++pixel_pos] = color.channel[1];
	*(unsigned int *)&info->addr[++pixel_pos] = color.channel[0];
}

t_color	get_color(t_vector2 pixel, int iteration, int max_iteration)
{
	double	t;

	(void)pixel;
	if (iteration == max_iteration)
		return (create_trgb(0, 0, 0, 0));
	t = iteration;// / max_iteration;
	return (create_trgb(0, t * 255, t * 255, t * 255));
}

t_vector2	init_vector2(double x, double y)
{
	t_vector2	vector2;

	vector2.x = x;
	vector2.y = y;
	return (vector2);
}

t_rect	init_rect(double x, double y, double w, double h)
{
	t_rect	rect;

	rect.pos = init_vector2(x, y);
	rect.size = init_vector2(w, h);
	return (rect);
}

static t_vector2	get_pixel_scaled(t_vector2 pixel, t_rect viewport)
{
	t_vector2	pixel_scaled;
	int			scale_factor;
	int			viewport_ratio;
	int			screen_ratio;

	viewport_ratio = viewport.size.x / viewport.size.y;
	screen_ratio = WIDTH / HEIGHT;
	if (screen_ratio > viewport_ratio)
		scale_factor = HEIGHT / viewport.size.y;
	else
		scale_factor = WIDTH / viewport.size.x;
	pixel_scaled.x = (pixel.x / scale_factor) + viewport.pos.x;
	pixel_scaled.y = (pixel.y / scale_factor) + viewport.pos.y;
	return (pixel_scaled);
}

int	put_rectangle(t_vector2 pixel, t_rect viewport, int max_iteration)
{
	t_vector2	pixel_scaled;

	pixel_scaled = get_pixel_scaled(pixel, viewport);
	if (pixel_scaled.x >= 0 && pixel_scaled.x < viewport.size.x
		&& pixel_scaled.y >= 0 && pixel_scaled.y < viewport.size.y)
		return (max_iteration);
	return (1);
}

int	put_mandelbrot(t_vector2 pixel, t_rect viewport, int max_iteration)
{
	int			iteration;
	double		xtemp;
	t_vector2	pixel_scaled;

	pixel_scaled = get_pixel_scaled(pixel, viewport);
	pixel.x = 0;
	pixel.y = 0;
	iteration = 0;
	while ((pixel.x * pixel.x) + (pixel.y * pixel.y) <= 4
		&& iteration < max_iteration)
	{
		xtemp = (pixel.x * pixel.x) - (pixel.y * pixel.y) + pixel_scaled.x;
		pixel.y = (2 * pixel.x * pixel.y) + pixel_scaled.y;
		pixel.x = xtemp;
		iteration++;
	}
	return (iteration);
}

static void	draw_app(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
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
			iteration = put_rectangle(pixel, init_rect(0, 0, 1, 1), fractolinfo->max_iteration);
			// iteration = put_mandelbrot(pixel, init_rect(0, 0, 1.53, 2.24), fractolinfo->max_iteration);
			color = get_color(pixel, iteration, fractolinfo->max_iteration);
			put_pixel(fractolinfo->imageinfo, pixel, color);
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(appinfo->mlx, appinfo->window,
		fractolinfo->imageinfo->image, 0, 0);
}

void	start_app(char *name)
{
	t_appinfo		*appinfo;
	t_fractolinfo	*fractolinfo;

	appinfo = init_app(name);
	fractolinfo = init_fractolinfo(name, 1000, appinfo);
	draw_app(appinfo, fractolinfo);	mlx_loop(appinfo->mlx);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	start_app("Test");
	return (0);
}
