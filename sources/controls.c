/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:07:19 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/26 20:48:11 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_control(t_event_data *data)
{
	fractol_reset(data->fractolinfo);
	draw_fractol(data->appinfo, data->fractolinfo);
}

void	move_control(int button, t_event_data *data)
{
	t_vector2	offset;
	double		val;

	offset = data->fractolinfo->vp_offset;
	val = 10 * data->fractolinfo->zoom;
	if (button == ON_ARROW_LEFT)
		data->fractolinfo->vp_offset = init_vector2(offset.x - val, offset.y);
	else if (button == ON_ARROW_RIGHT)
		data->fractolinfo->vp_offset = init_vector2(offset.x + val, offset.y);
	else if (button == ON_ARROW_UP)
		data->fractolinfo->vp_offset = init_vector2(offset.x, offset.y - val);
	else if (button == ON_ARROW_DOWN)
		data->fractolinfo->vp_offset = init_vector2(offset.x, offset.y + val);
	draw_fractol(data->appinfo, data->fractolinfo);
}

void	change_max_iteration(int button, t_event_data *data)
{
	if (button == ON_KEY_PLUS || button == ON_NUMPAD_PLUS)
		data->fractolinfo->max_iteration++;
	if (button == ON_KEY_MINUS || button == ON_NUMPAD_MINUS)
		data->fractolinfo->max_iteration--;
	if (data->fractolinfo->max_iteration < 0)
		data->fractolinfo->max_iteration = 0;
	draw_fractol(data->appinfo, data->fractolinfo);
}

void	fix_mouse_movement(t_event_data *data)
{
	data->fractolinfo->is_fixed_mouse = data->fractolinfo->is_fixed_mouse == 0;
	draw_fractol(data->appinfo, data->fractolinfo);
}

void	change_fractol(int button, t_event_data *data)
{
	char	*name;

	name = NULL;
	if (button == ON_KEY_1)
		name = ft_strdup("Mandelbrot");
	else if (button == ON_KEY_2)
		name = ft_strdup("Julia set");
	else if (button == ON_KEY_3)
		name = ft_strdup("Burning ship");
	if (str_equal(data->fractolinfo->name, name))
	{
		free(name);
		return ;
	}
	free(data->fractolinfo->name);
	data->fractolinfo->name = name;
	init_formula(data->fractolinfo);
	reset_control(data);
}
