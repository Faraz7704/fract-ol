/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkhan <fkhan@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:59:12 by fkhan             #+#    #+#             */
/*   Updated: 2022/07/26 19:27:33 by fkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	exit_app(t_event_data *event_data)
{
	free(event_data->fractolinfo->name);
	free(event_data->fractolinfo->imageinfo);
	free(event_data->fractolinfo);
	free(event_data->appinfo->mlx);
	free(event_data->appinfo->window);
	free(event_data->appinfo);
	exit(0);
}

static void	start_app(char *name, t_vector2 complex)
{
	t_appinfo		*appinfo;
	t_fractolinfo	*fractolinfo;
	t_event_data	event_data;

	appinfo = init_app(name);
	fractolinfo = init_fractolinfo(name, 50, appinfo, complex);
	event_data = init_event_data(appinfo, fractolinfo);
	register_events(appinfo, &event_data);
	draw_fractol(appinfo, fractolinfo);
	mlx_loop(appinfo->mlx);
}

int	valid_arg(int ac, char **av, t_vector2 *complex)
{
	if (ac == 2 && str_equal(av[1], "Mandelbrot"))
		return (1);
	if (ac >= 2 && str_equal(av[1], "Julia set"))
	{
		if (ac == 4)
		{
			complex->x = ft_atof(av[2]);
			complex->y = ft_atof(av[3]);
			return (1);
		}
		else if (ac == 2)
			return (1);
	}
	if (ac == 2 && str_equal(av[1], "Burning ship"))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_vector2	complex;

	complex = init_vector2(0, 0);
	if (valid_arg(ac, av, &complex))
		start_app(av[1], complex);
	else
		print_help();
	return (0);
}
