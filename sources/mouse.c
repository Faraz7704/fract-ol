/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/24 22:37:48 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_in(int x, int y, double zoom, t_event_data *data)
{
	t_vector2	pos;

	pos = data->fractolinfo->zoom_offset;
	if (pos.x == 0 && pos.y == 0)
		pos = init_vector2(x, y);
	pos.x = pos.x + ((x - pos.x) * zoom);
	pos.y = pos.y + ((y - pos.y) * zoom);
	data->fractolinfo->zoom_offset = pos;
	mlx_string_put(data->appinfo->mlx, data->appinfo->window, pos.x, pos.y, 0xCCCCCC,
		"-");
}

static void	zoom_out(int x, int y, double zoom, t_event_data *data)
{
	t_vector2	pos;

	pos = data->fractolinfo->zoom_offset;
	if (pos.x == 0 && pos.y == 0)
		pos = init_vector2(x, y);
	pos.x = pos.x - ((x - pos.x) * zoom);
	pos.y = pos.y - ((y - pos.y) * zoom);
	data->fractolinfo->zoom_offset = pos;
	mlx_string_put(data->appinfo->mlx, data->appinfo->window, pos.x, pos.y, 0xCCCCCC,
		"-");
}

static void	julia_motion(int x, int y, t_event_data *data)
{
	data->fractolinfo->complex = init_vector2(
			4 * ((double)x / WIDTH - 0.5),
			4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
	draw_fractol(data->appinfo, data->fractolinfo);
}

int	mouse_down_handler(int button, int x, int y, t_event_data *data)
{
	if (data->fractolinfo->is_help)
		return (0);
	if (button == ON_MOUSE_SCROLL_UP)
	{
		if (data->fractolinfo->max_iteration > 50)
			data->fractolinfo->max_iteration -= 10;
		zoom_out(x, y, data->fractolinfo->zoom, data);
		data->fractolinfo->zoom *= ZOOM_FACTOR;
		draw_fractol(data->appinfo, data->fractolinfo);
	}
	else if (button == ON_MOUSE_SCROLL_DOWN)
	{
		data->fractolinfo->max_iteration += 10;
		data->fractolinfo->zoom /= ZOOM_FACTOR;
		zoom_in(x, y, data->fractolinfo->zoom, data);
		draw_fractol(data->appinfo, data->fractolinfo);
	}
	return (0);
}

int	mouse_move_handler(int x, int y, t_event_data *data)
{
	if (data->fractolinfo->is_help)
		return (0);
	if (data->fractolinfo->is_fixed_mouse)
		return (0);
	if (str_equal(data->fractolinfo->name, "Julia set"))
		julia_motion(x, y, data);
	return (0);
}
