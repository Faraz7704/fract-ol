/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/06/30 21:36:35 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	create_trgb(int t, int r, int g, int b)
{
	t_color	color;

	color.channel[0] = t;
	color.channel[1] = r;
	color.channel[2] = g;
	color.channel[3] = b;
	return (color);
}

int	get_numcolor(t_color color)
{
	return (color.channel[0] << 24 | color.channel[1] << 16
		| color.channel[2] << 8 | color.channel[3]);
}

t_color	get_fractol_color(t_vector2 pixel, int iteration, int max_iteration)
{
	double	t;

	(void)pixel;
	if (iteration == max_iteration)
		return (create_trgb(0, 0, 0, 0));
	t = iteration / max_iteration;
	return (create_trgb(0, 235, 64, 52));
}
