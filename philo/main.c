/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:40:26 by ysachiko          #+#    #+#             */
/*   Updated: 2022/03/22 19:32:03 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_zero(int	**arr, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		*arr[i] = 0;
		i++;
	}
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
		pthread_mutex_init(&data->forks[i], NULL);
		state[i].hungry = 0;
		state[i].eating = 0;
		state[i].thinking = 0;
		state[i].time_die = data->time_die;
		state[i].time_sleep = data->time_sleep;
		state[i].time_eat = data->time_eat;
		state[i].left = (i + data->number) % data->number;
		state[i].right = (i + 1) % data->number;
		state[i].num = i;
		state[i].number_of_times = data->number_of_times;
		pthread_mutex_init(&state[i].left_fork_m, NULL); //need to be destroyed later
		state[i].left_fork_m = data->forks[state[i].left];
		pthread_mutex_init(&state[i].right_fork_m, NULL);
		state[i].right_fork_m = data->forks[state[i].right];
		// printf("hung [%d] = %d\n", i, state[i].hungry);
		// printf("eat [%d] = %d\n", i, state[i].eating);
		// printf("think [%d] = %d\n", i, state[i].thinking);
		printf("left [%d] = %d\n", i, state[i].left);
		printf("right [%d] = %d\n", i, state[i].right);
		i++;
	}
}

void	philo_states(t_data *data)
{
	data->state = malloc(sizeof(t_philo) * data->number + 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number + 1);
	data->array_number_of_times = malloc(sizeof(int) * data->number + 1);
	philo_fill(data->state, data);
}

void	parse(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	data->number_of_times = -1;
	while (i < argc)
	{
		if (i == 1)
			data->number = ft_atoi(argv[i]);
		if (i == 2)
			data->time_die = ft_atoi(argv[i]);
		if (i == 3)
			data->time_eat = ft_atoi(argv[i]);
		if (i == 4)
			data->time_sleep = ft_atoi(argv[i]);
		if (i == 5)
			data->number_of_times = ft_atoi(argv[i]);
		i++;
	}
	philo_states(data);
}

void	take_forks(t_philo *philo)
{
	int	local;

	if (philo->left == philo->right)
		usleep(philo->time_die);
	pthread_mutex_lock(&philo->left_fork_m);
	// printf("philo %d takes left fork\n", philo->num);
	pthread_mutex_lock(&philo->right_fork_m);
	// printf("philo %d takes right fork\n", philo->num);
	local = philo->left;

}

void	eating(t_philo *philo)
{
	gettimeofday(&philo->last_time_eat, NULL);
	printf("philosoph %d eating\n", philo->num);
	usleep(philo->time_eat);
	pthread_mutex_unlock(&philo->left_fork_m);
	pthread_mutex_unlock(&philo->right_fork_m);
}

void	thinking(t_philo *philo)
{
	printf("philosoph %d is thinking\n", philo->num);
	// usleep(100);
}

void	sleeping(t_philo *philo)
{
	printf("philosoph %d is sleeping\n", philo->num);
	usleep(philo->time_sleep);
}

int	time_to_ms(struct timeval first, struct timeval second)
{
	long long	tmp;
	int			res;

	tmp = second.tv_usec - first.tv_usec;
	res = (int)(tmp / 1000);
	return (res);
}

void	*func(void *arg)
{
	t_philo	*args;
	struct timeval	tvalSecond;

	args = arg;
	printf("Philosoph %d is Thinking =)\n", args->num);
	gettimeofday(&args->last_time_eat, NULL);
	gettimeofday(&tvalSecond, NULL);
	while (time_to_ms(tvalSecond, args->last_time_eat) < args->time_die)
	{
		printf("%d\n", time_to_ms(tvalSecond, args->last_time_eat));
		gettimeofday(&tvalSecond, NULL);
		thinking(args);
		take_forks(args);
		eating(args);
		sleeping(args);
	}
	printf("Philosoph %d is dead :(\n", args->num);
	exit (0);
	// printf("%d\n", args->time_die);
	return (NULL);
}

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

int	main(int argc, char **argv)
{
	t_data			*data;
	struct timeval	tvalBefore;
	int				i;

	i = 0;
	gettimeofday(&tvalBefore, NULL);
	printf("Time %ld\n", tvalBefore.tv_sec);
	data = malloc(sizeof(t_data));
	parse(argc, argv, data);
	while (i < data->number)
	{
		pthread_create(&data->state[i].thread, NULL, func, (void *)(&data->state[i]));
		i++;
	}
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
	free(data->forks);
	free(data->state);
	free(data);
}
