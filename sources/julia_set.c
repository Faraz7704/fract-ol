/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/08 14:03:09 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_julia_set(t_fractolinfo *info, t_vector2 pixel)
{
	int			iteration;
	double		xtemp;
	t_vector2	pixel_scaled;

	// pixel_scaled = get_pixel_zoomed(pixel, info->viewport, info->zoom, info->offset);
	pixel_scaled = get_pixel_scaled(pixel, info->viewport, info->offset);
	iteration = 0;
	while ((pixel_scaled.x * pixel_scaled.x) + (pixel_scaled.y * pixel_scaled.y) <= 4
		&& iteration < info->max_iteration)
	{
		xtemp = (pixel_scaled.x * pixel_scaled.x) - (pixel_scaled.y * pixel_scaled.y) + info->complex.x;
		pixel_scaled.y = (2 * pixel_scaled.x * pixel_scaled.y) + info->complex.y;
		pixel_scaled.x = xtemp;
		iteration++;
	}
	return (iteration);
}
