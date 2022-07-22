/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/22 17:58:12 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	exit_app(t_event_data *event_data)
{
	free(event_data->fractolinfo->imageinfo);
	free(event_data->fractolinfo);
	free(event_data->appinfo->mlx);
	free(event_data->appinfo->window);
	free(event_data->appinfo);
	exit(0);
}

t_event_data	init_event_data(t_appinfo *appinfo,
						t_fractolinfo *fractolinfo)
{
	t_event_data	data;

	data.appinfo = appinfo;
	data.fractolinfo = fractolinfo;
	return (data);
}

static void	register_events(t_appinfo *appinfo, t_event_data *event_data)
{	
	mlx_hook(appinfo->window, 17, 0, exit_app, event_data);
	mlx_hook(appinfo->window, 4, 0, mouse_down_handler, event_data);
	mlx_hook(appinfo->window, 6, 0, mouse_move_handler, event_data);
	mlx_hook(appinfo->window, 2, 0, key_down_handler, event_data);
}

void	start_app(char *name)
{
	t_appinfo		*appinfo;
	t_fractolinfo	*fractolinfo;
	t_event_data	event_data;

	appinfo = init_app(name);
	fractolinfo = init_fractolinfo(name, 50, appinfo);
	event_data = init_event_data(appinfo, fractolinfo);
	register_events(appinfo, &event_data);
	draw_fractol(appinfo, fractolinfo);
	mlx_loop(appinfo->mlx);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (str_equal(av[1], "Mandelbrot")
			|| str_equal(av[1], "Julia set")
			|| str_equal(av[1], "Burning ship"))
			start_app(av[1]);
	}
	print_help();
	return (0);
}
