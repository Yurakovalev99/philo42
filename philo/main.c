/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:40:26 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/29 16:23:49 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

int	ft_isdigit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	else
		return (0);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
		return (1);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// void	*monitor(void *arg)
// {
// 	t_philo	*philo;
// 	long long	ms;

// 	philo = arg;
// 	while(!philo->info->finish)
// 	{
// 		usleep(150);
// 		pthread_mutex_lock(&philo->check_mutex);
// 		pthread_mutex_lock(&philo->info->finish_m);
// 		ms = philo->last_time_eat - philo->last_after_eat;
// 		if ((ms > philo->info->time_die) && philo->info->finish == 0)
// 		{
// 			pthread_mutex_unlock(philo->right_fork_m);
// 			pthread_mutex_unlock(philo->left_fork_m);
// 			printf("Philosoph %d is dead :(\n", philo->num + 1);
// 			pthread_mutex_lock(&philo->info->finish_m);
// 			philo->info->finish = 1;
// 			pthread_mutex_unlock(&philo->info->finish_m);
// 		}
// 		pthread_mutex_unlock(&philo->info->finish_m);
// 		pthread_mutex_unlock(&philo->check_mutex);
// 	}
// 	return (NULL);
// }


void	create_philo(t_data *data)
{
	int			i;
	// pthread_t	thread;

	i = 0;
	while (i < data->number)
	{
		pthread_create(&data->state[i].thread, NULL, func, (void *)(&data->state[i]));
		// pthread_create(&thread, NULL, monitor, (void *)(&data->state[i]));
		// pthread_detach(thread);
		i++;
	}

	// if (data->info->number_of_times != 0)
	// {
	// 	pthread_create(thread, NULL, monitor_of_eats, (void *)(&data->info));
	// 	pthread_detach(thread);
	// }
}

int	main(int argc, char **argv)
{
	t_data			*data;
	int				i;

	i = 0;
	if(ft_check_args(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	init_structures(argc, argv, data);
	create_philo(data);
	i = 0;
	while (i < data->number)
	{
		pthread_join(data->state[i].thread, NULL);
		i++;
	}

	// printf("numbers of philo = %d\n", data->number);
	// printf("t_die of philo = %d\n", data->time_die);
	// printf("t_eat of philo = %d\n", data->time_eat);
	// printf("t_sleep of philo = %d\n", data->time_sleep);
	// printf("number_of_times_each_philosopher_must_eat = %d\n", data->number_of_times);
	// printf("forks: = %d\n", data->forks); //CHECHS FOR VALUE
	destroy_mutex(data);
	// free(data->array_number_of_times);
	free(data->info);
	free(data->forks);
	free(data->state);
	free(data);
}
