/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/23 19:17:23 by fkhan            ###   ########.fr       */
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

static t_fractolinfo	*init_fractolinfo(char *name, t_appinfo *appinfo)
{
	t_fractolinfo	*info;

	info = malloc(sizeof(t_fractolinfo));
	if (!info)
		debug_log(ERR_FRACTOL_INIT);
	info->name = name;
	info->imageinfo = init_imageinfo(appinfo->mlx);
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

void	put_pixel(t_imageinfo *info, int x, int y, t_color color)
{
	int		pixel_pos;

	pixel_pos = y * info->line_length + x * (info->bits_per_pixel / 8);
	*(unsigned int *)&info->addr[pixel_pos++] = 1;//color.channel[3];
	// *(unsigned int *)&info->addr[pixel_pos++] = color.channel[2];
	// *(unsigned int *)&info->addr[pixel_pos++] = color.channel[1];
	// *(unsigned int *)&info->addr[pixel_pos] = color.channel[0];
}

t_color	get_color(int iteration, int max_iteration)
{
	t_color	color;
	double	t;

	t = (double)iteration / max_iteration;
	color.channel[0] = 0;
	color.channel[1] = (int8_t)(9 * (1 - t) * pow(t, 3) * 255);
	color.channel[2] = (int8_t)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	color.channel[3] = (int8_t)(8.5 * pow((1 - t), 3) * t * 255);
	return (color);
}

void	put_mandelbrot(t_imageinfo *info, int x, int y)
{
	int		iteration;
	int		max_iteration;
	int		xtemp;
	t_color	color;
	int		x0;
	int		y0;

	x0 =  -2.0 + x * ((2.0 - (-2.0)) / (WIDTH - 1)); 
	y0 = (-2.0 + (2.0 - (-2.0)) * (HEIGHT / WIDTH)) - y * (((-2.0 + (2.0 - -2.0) * (HEIGHT / WIDTH)) - (-2.0)) / (HEIGHT - 1));
	iteration = 0;
	max_iteration = 100;
	while ((x * x) + (y * y) <= 4 && iteration < max_iteration)
	{
		xtemp = (x * x) - (y * y) + x0;
		y = (2 * x * y) + y0;
		x = xtemp;
		iteration++;
	}
	color = get_color(iteration, max_iteration);
	put_pixel(info, x, y, color);
}

static void	draw_app(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_mandelbrot(fractolinfo->imageinfo, x, y);
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
	fractolinfo = init_fractolinfo(name, appinfo);
	draw_app(appinfo, fractolinfo);	mlx_loop(appinfo->mlx);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	start_app("Test");
	return (0);
}
