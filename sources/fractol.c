/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/21 20:25:23 by fkhan            ###   ########.fr       */
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

void	put_pixel(t_imageinfo *info, int x, int y, int color)
{
	int		pixel_pos;

	pixel_pos = y * info->line_length + x * (info->bits_per_pixel / 8);
	*(unsigned int *)&info->addr[pixel_pos] = color;
}

static void	draw_app(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
{
	int		x;
	int		y;
	int		white_color;

	white_color = 0xFFFFFF;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(fractolinfo->imageinfo, x, y, white_color);
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
