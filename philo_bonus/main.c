/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:32:39 by chorse            #+#    #+#             */
/*   Updated: 2022/04/25 18:02:59 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	ft_sit(t_data *data)
{
	long long curTime;

	curTime = ft_time();
	while (curTime < data->zero_time + 200)
	{
		usleep(10);
		curTime = ft_time();
	}
}

void	exit_all(t_data *data)
{
	int	i;

	i = 0;
	sem_close(data->print);
	sem_close(data->general);
	kill(0, SIGKILL);
}

void	*moni(void *arg)
{
	t_data *data;

	data = arg;
	usleep(1000);
	while (1)
	{
		if (ft_time() - data->last_meal > data->die_time)
		{
			printf("\n\n%lld %lld %lld %lld %d",ft_time(), data->last_meal, ft_time() - data->zero_time, data->zero_time, data->die_time);
			printf("CHECK\n\n\n");
			// exit_all(data);
			break ;
		}
	}
	return (NULL);
}

void	monitoring(t_data *data)
{
	pthread_t	monitoring;

	pthread_create(&monitoring, NULL, moni, &data);
	pthread_detach(monitoring);
}

void	update_time(t_data *data)
{
	data->zero_time = ft_time();
	data->last_meal = data->zero_time;
}

void initProcess(t_data *data)
{
	pid_t pid;

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
			update_time(data);
			ft_sit(data);
			update_time(data);
			monitoring(data);
			ft_action(data);
			// break;
		}
		data->children_pids[data->id] = pid;
		data->id++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int				i;
	// pthread_t		monitoring;

	i = 0;
	// monitoring = NULL;
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
	initProcess(&data);
	sleep(1000);
	return (0);
	// for (int i = 0; i < 5; i++) {
	// 	printf("pid = %d \n", data->children_pids[i]);
	// }
	// free(data->children_pids);
	// free(data);
}
