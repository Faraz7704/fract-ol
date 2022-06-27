/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/27 16:20:29 by fkhan            ###   ########.fr       */
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
	t_color	color;
	double	t;

	if (iteration == max_iteration)
		return (create_trgb(0, 0, 0, 0));
	t = iteration / max_iteration;
	color.channel[0] = ft_ler
	return (color);
}

t_vector2	init_vector2(double x, double y)
{
	t_vector2	vector2;

	vector2.x = x;
	vector2.y = y;
	return (vector2);
}

int	put_mandelbrot(t_vector2 pixel, int max_iteration)
{
	int		iteration;
	int		xtemp;
	int		x;
	int		y;

	x = 0;
	y = 0;
	iteration = 0;
	while ((x * x) + (y * y) <= 4 && iteration < max_iteration)
	{
		xtemp = (x * x) - (y * y) + pixel.x;
		y = (2 * x * y) + pixel.y;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

static void	draw_app(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
{
	int			x;
	int			y;
	int			iteration;
	t_color		color;
	t_vector2	pixel;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// pixel = init_vector2(x * ((1.2 - (-2.05)) / WIDTH) + (-2.05), y * ((1.2 - (-1.3)) / HEIGHT) + (-1.3));
			pixel = init_vector2(x, y);
			iteration = put_mandelbrot(pixel, fractolinfo->max_iteration);
			color = get_color(pixel, iteration, fractolinfo->max_iteration);
			put_pixel(fractolinfo->imageinfo, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(appinfo->mlx, appinfo->window,
		fractolinfo->imageinfo->image, 0, 0);
}

void	start_app(char *name)
{
	t_appinfo		*appinfo;
	t_fractolinfo	*fractolinfo;

	appinfo = init_app(name);
	fractolinfo = init_fractolinfo(name, 100, appinfo);
	draw_app(appinfo, fractolinfo);	mlx_loop(appinfo->mlx);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	start_app("Test");
	return (0);
}
