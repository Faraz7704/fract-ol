/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/21 02:14:48 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mouse_scroll(int x, int y, t_event_data *data)
{
	static t_vector2	prev_pos;
	static t_vector2	new_pos;
	t_vector2			diff_pos;
	double				zoom;

	zoom = data->fractolinfo->zoom;
	if (prev_pos.x == 0 && prev_pos.y == 0)
		prev_pos = init_vector2(x, y);
	if (new_pos.x == 0 && new_pos.y == 0)
		new_pos = init_vector2(x, y);
	printf("diff world_x: %f, zoom_x: %f zoom: %f\n", diff_pos.x, diff_pos.x * zoom, zoom);
	diff_pos.x = (x - prev_pos.x);
	diff_pos.y = (y - prev_pos.y);
	new_pos.x = new_pos.x + (diff_pos.x / (WIDTH * zoom));
	new_pos.y = new_pos.y + (diff_pos.y * zoom);
	data->fractolinfo->zoom_offset = new_pos;
	draw_fractol(data->appinfo, data->fractolinfo);
	mlx_string_put(data->appinfo->mlx, data->appinfo->window, new_pos.x, new_pos.y, 0x34f235,
		"|");
	mlx_string_put(data->appinfo->mlx, data->appinfo->window, 125, HEIGHT / 2, 0xCCCCCC,
		"-");
	prev_pos.x = x;
	prev_pos.y = y;
}

int	mouse_down_handler(int button, int x, int y, t_event_data *data)
{
	(void)x;
	(void)y;
	if (button == ON_MOUSE_SCROLL_UP)
	{
		data->fractolinfo->zoom /= ZOOM_FACTOR;
		mouse_scroll(125, 250, data);
	}
	else if (button == ON_MOUSE_SCROLL_DOWN)
	{
		data->fractolinfo->zoom /= ZOOM_FACTOR;
		mouse_scroll(0, 250, data);
	}
	return (0);
}
