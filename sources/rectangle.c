/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/02 15:40:58 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_rectangle(t_fractolinfo *info, t_vector2 pixel)
{
	t_vector2	pixel_scaled;

	pixel_scaled = get_pixel_scaled(pixel, info->viewport);
	if (pixel_scaled.x >= 0 && pixel_scaled.x < info->viewport.size.x
		&& pixel_scaled.y >= 0 && pixel_scaled.y < info->viewport.size.y)
		return (info->max_iteration);
	return (1);
}
