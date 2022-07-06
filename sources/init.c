/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/06 18:58:11 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_imageinfo	*init_imageinfo(void *mlx)
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

void	init_formula(t_fractolinfo	*info)
{
	if (str_equal(info->name, "Mandelbrot"))
	{
		// info->viewport = init_rect(-2.25, -1.37, 2.97, 2.74);
		info->viewport = init_rect(-2.00, -1.12, 2.47, 2.24);
		info->formula = &get_mandelbrot;
	}
	else if (str_equal(info->name, "Rectangle"))
	{
		info->viewport = init_rect(0, 0, 50, 35);
		info->formula = &get_rectangle;
	}
	else
		info->formula = NULL;
}

void	fractol_reset(t_fractolinfo	*info)
{
	static int	max = 0;

	if (max == 0)
		max = info->max_iteration;
	else
		info->max_iteration = max;
	info->zoom = 1.0f;
	info->offset = init_vector2(0, 0);
}

t_fractolinfo	*init_fractolinfo(char *name, int max_iteration,
	t_appinfo *appinfo)
{
	t_fractolinfo	*info;

	info = malloc(sizeof(t_fractolinfo));
	if (!info)
		debug_log(ERR_FRACTOL_INIT);
	info->name = name;
	info->imageinfo = init_imageinfo(appinfo->mlx);
	info->max_iteration = max_iteration;
	init_formula(info);
	fractol_reset(info);
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
	return (info);
}
