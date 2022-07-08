/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/06 23:51:47 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_down_handler(int button, int x, int y, t_event_data *data)
{
	if (button == ON_MOUSE_SCROLL_UP)
	{
		data->fractolinfo->zoom *= ZOOM_FACTOR;
		data->fractolinfo->mouse_pos = init_vector2(x * -1, y * -1);
		draw_fractol(data->appinfo, data->fractolinfo);
	}
	else if (button == ON_MOUSE_SCROLL_DOWN)
	{
		data->fractolinfo->zoom /= ZOOM_FACTOR;
		data->fractolinfo->mouse_pos = init_vector2(x * -1, y * -1);
		draw_fractol(data->appinfo, data->fractolinfo);
	}
	return (0);
}
