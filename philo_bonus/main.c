/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:22:58 by ysachiko          #+#    #+#             */
/*   Updated: 2022/04/25 19:23:01 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sit(t_data *data)
{
	long long	cur_time;

	cur_time = ft_time();
	while (cur_time < data->zero_time + 200)
	{
		usleep(10);
		cur_time = ft_time();
	}
}

void	update_time(t_data *data)
{
	data->zero_time = ft_time();
	data->last_meal = data->zero_time;
}

void	init_process(t_data *data)
{
	pid_t	pid;

	data->id = 0;
	update_time(data);
	while (data->id < data->number)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("ERROR_PROCESS INIT");
			exit (0);
		}
		if (pid == 0)
		{
			ft_sit(data);
			update_time(data);
			monitoring(data);
			update_time(data);
			ft_action(data);
		}
		data->children_pids[data->id] = pid;
		data->id++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (ft_init_data(argc, argv, &data))
	{
		write(2, "invalid value\n", 15);
		return (1);
	}
	if (ft_init_philo(argv, &data))
	{
		write(2, "invalid value\n", 15);
		return (1);
	}
	init_process(&data);
	sleep(1000);
	return (0);
}
