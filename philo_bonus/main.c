/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:32:39 by chorse            #+#    #+#             */
/*   Updated: 2022/04/23 15:16:58 by ysachiko         ###   ########.fr       */
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

void initProcess(t_data *data)
{
	pid_t pid;

	data->id = 0;
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
			printf("SUCCES\n");
			ft_sit(data);
			ft_action(data);
			break;
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
