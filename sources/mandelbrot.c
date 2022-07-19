/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/19 21:13:05 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_mandelbrot(t_fractolinfo *info, t_vector2 pixel)
{
	int			iteration;
	double		xtemp;
	t_vector2	pixel_scaled;

	pixel_scaled = get_pixel_zoomed(pixel, info->zoom, info->zoom_offset);
	pixel_scaled = get_pixel_scaled(pixel_scaled, info->viewport, info->vp_offset);
	pixel.x = 0;
	pixel.y = 0;
	iteration = 0;
	while ((pixel.x * pixel.x) + (pixel.y * pixel.y) <= 4
		&& iteration < info->max_iteration)
	{
		xtemp = (pixel.x * pixel.x) - (pixel.y * pixel.y) + pixel_scaled.x;
		pixel.y = (2 * pixel.x * pixel.y) + pixel_scaled.y;
		pixel.x = xtemp;
		iteration++;
	}
	return (iteration);
}
