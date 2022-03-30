/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:51:58 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/30 18:40:31 by ysachiko         ###   ########.fr       */
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
	int	i;

	i = 0;
	data->state = malloc(sizeof(t_philo) * data->number + 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number + 1);
	data->info = malloc(sizeof(t_info));
	pthread_mutex_init(&data->info->finish_mutex, NULL);
	data->info->finish = 0;

	parse(argc, argv, data);
}

void	philo_fill(t_philo *state, t_data *data)
{
	int	i;


	i = 0;
	while (i < data->number)
		pthread_mutex_init(&data->forks[i++], NULL);
	i = 0;

	while (i < data->number)
	{
		// pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&state[i].check_mutex, NULL);

		state[i].left =  (i + 1) % data->number;
		state[i].right = (i + data->number) % data->number;
		state[i].num = i;
		state[i].finish_total = 0;
		// state[i].last_after_eat = 0;
		state[i].left_fork_m = &data->forks[(state[i].left)];
		state[i].right_fork_m = &data->forks[(state[i].right)];
		state[i].info = data->info;
		state[i].num_of_eats = 0;
		i++;
	}
}
