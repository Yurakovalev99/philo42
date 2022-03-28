/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:51:58 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/28 18:04:35 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	data->info->number_of_times = -1;
	while (i < argc)
	{
		if (i == 1)
			data->number = ft_atoi(argv[i]);
		if (i == 2)
			data->info->time_die = ft_atoi(argv[i]);
		if (i == 3)
			data->info->time_eat = ft_atoi(argv[i]);
		if (i == 4)
			data->info->time_sleep = ft_atoi(argv[i]);
		if (i == 5)
			data->info->number_of_times = ft_atoi(argv[i]);
		i++;
	}
	philo_fill(data->state, data);
}

void	init_structures(int argc, char **argv, t_data *data)
{
	data->state = malloc(sizeof(t_philo) * data->number + 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number + 1);
	data->info = malloc(sizeof(t_info));
	parse(argc, argv, data);
}

void	philo_fill(t_philo *state, t_data *data)
{
	int	i;
	struct timeval	tv;

	i = 0;
	while (i < data->number)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;
	gettimeofday(&tv, NULL);
	pthread_mutex_init(&data->finish_m, NULL);
	while (i < data->number)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		state[i].time_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		state[i].left =  (i + 1) % data->number;
		state[i].right = (i + data->number) % data->number;
		state[i].num = i;
		state[i].last_after_eat = state[i].time_start;
		state[i].left_fork_m = &data->forks[(state[i].left)];
		state[i].right_fork_m = &data->forks[(state[i].right)];
		state[i].last_time_eat = state[i].time_start;
		state[i].info = data->info;
		state[i].finish = 0;
		state[i].num_of_eats = 0;
		// printf("%d %d %d %d \n", state[i].info->time_die, state[i].info->time_eat, state[i].info->time_sleep, state[i].info->number_of_times);
		// printf("hung [%d] = %d\n", i, state[i].hungry);
		// printf("eat [%d] = %d\n", i, state[i].eating);
		// printf("think [%d] = %d\n", i, state[i].thinking);
		// printf("left [%d] = %d\n", i, state[i].left);
		// printf("right [%d] = %d\n", i, state[i].right);
		i++;
	}
}


		// state[i].time_die = data->time_die;
		// state[i].time_sleep = data->time_sleep;
		// state[i].time_eat = data->time_eat;
