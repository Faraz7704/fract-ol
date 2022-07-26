/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/26 20:49:44 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_burning_ship(t_fractolinfo *info, t_vector2 pixel)
{
	int			iteration;
	double		xtemp;
	t_vector2	pixel_scaled;

	pixel_scaled = get_pixel_scaled(pixel, info->viewport,
			info->vp_offset);
	pixel_scaled = get_pixel_zoomed(pixel_scaled, info->zoom, info->viewport,
			info->zoom_offset);
	pixel.x = pixel_scaled.x;
	pixel.y = pixel_scaled.y;
	iteration = 0;
	while ((pixel.x * pixel.x) + (pixel.y * pixel.y) < 4
		&& iteration < info->max_iteration)
	{
		xtemp = (pixel.x * pixel.x) - (pixel.y * pixel.y) + pixel_scaled.x;
		pixel.y = fabs(2 * pixel.x * pixel.y) + pixel_scaled.y;
		pixel.x = xtemp;
		iteration++;
	}
	return (iteration);
}
