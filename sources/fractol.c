/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/19 17:06:17 by fkhan            ###   ########.fr       */
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
	info->data_addr = mlx_get_data_addr(
		info->image,
		&info->bits_per_pixel,
		&info->size_line,
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

static void	draw_app(t_appinfo *appinfo, t_fractolinfo *fractolinfo)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			fractolinfo->imageinfo->data_addr[j * i] = 10;
			fractolinfo->imageinfo->data_addr[++j * i] = 20;
			fractolinfo->imageinfo->data_addr[++j * i] = 30;
			fractolinfo->imageinfo->data_addr[++j * i] = 40;
			j++;
		}
		i++;
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
	draw_app(appinfo, fractolinfo);
	mlx_loop(appinfo->mlx);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	start_app("Test");
	return (0);
}
