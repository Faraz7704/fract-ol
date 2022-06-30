/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/30 21:35:05 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_rectangle(t_vector2 pixel, t_rect viewport, int max_iteration)
{
	t_vector2	pixel_scaled;

	pixel_scaled = get_pixel_scaled(pixel, viewport);
	if (pixel_scaled.x >= 0 && pixel_scaled.x < viewport.size.x
		&& pixel_scaled.y >= 0 && pixel_scaled.y < viewport.size.y)
		return (max_iteration);
	return (1);
}
