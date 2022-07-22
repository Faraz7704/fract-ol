/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/22 18:04:40 by fkhan            ###   ########.fr       */
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
	draw_fractol(data->appinfo, data->fractolinfo);
}

static void	zoom_out(int x, int y, double zoom, t_event_data *data)
{
	t_vector2	prev_pos;
	t_vector2	new_pos;
	t_vector2	diff_pos;
	double		offset_x;

	prev_pos = data->fractolinfo->mouse_pos;
	if (prev_pos.x == 0 && prev_pos.y == 0)
		prev_pos = init_vector2(x, y);
	new_pos = data->fractolinfo->zoom_offset;
	if (new_pos.x == 0 && new_pos.y == 0)
		new_pos = init_vector2(x, y);
	diff_pos.x = (prev_pos.x - x);
	diff_pos.y = (prev_pos.y - y);
	offset_x = (diff_pos.x * zoom);
	// printf("diff_pos_x: %f, prev_x: %f, offset_x: %f, zoom: %f\n", diff_pos.x, new_pos.x, offset_x, zoom);
	new_pos.x = new_pos.x - (diff_pos.x * zoom);
	new_pos.y = new_pos.y - (diff_pos.y * zoom);
	data->fractolinfo->zoom_offset = new_pos;
	data->fractolinfo->mouse_pos = init_vector2(new_pos.x, new_pos.y);
	draw_fractol(data->appinfo, data->fractolinfo);
	mlx_string_put(data->appinfo->mlx, data->appinfo->window, new_pos.x, new_pos.y, 0xCCCCCC,
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
		data->fractolinfo->zoom *= ZOOM_FACTOR;
		zoom_out(x, y, data->fractolinfo->zoom, data);
		draw_fractol(data->appinfo, data->fractolinfo);
	}
	else if (button == ON_MOUSE_SCROLL_DOWN)
	{
		data->fractolinfo->max_iteration += 10;
		data->fractolinfo->zoom /= ZOOM_FACTOR;
		zoom_in(x, y, data->fractolinfo->zoom, data);
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
