/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:20:22 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/20 16:01:40 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo (t_philo *philo)
{
	status()->philo = philo;
	init_mutex();
	init_philo();
}

void init_philo(void)
{
	int i;

	i = 0;
	status()->is_dead = 0;
	status()->is_full = 0;
	status()->starting_time = gettime();
	while (i < status()->number_of_philosophers)
	{
		if(pthread_create(&status()->philo[i].philosophers, NULL, (void *)ft_philo, &status()->philo[i]))
			return ;
		i++;
	}
	end_join(status());
	free_all();
}

void init_mutex(void)
{
	int i;

	i = 0;
	status()->philo = malloc(sizeof(t_philo) * status()->number_of_philosophers);
	if (pthread_mutex_init(&status()->life, NULL)
			|| pthread_mutex_init(&status()->food, NULL))
			return ;
	while (i < status()->number_of_philosophers)
	{
		status()->philo[i].num = i + 1;
		status()->philo[i].eat_count = 0;
		status()->philo[i].last_meal = 0;
		if(pthread_mutex_init(&status()->philo[i].fork_right.fork_lock , NULL))
			return ;
		if (i == 0)
			status()->philo[i].fork_left  = &status()->philo[status()->number_of_philosophers - 1].fork_right;
		else
			status()->philo[i].fork_left  = &status()->philo[i - 1].fork_right;
		if (pthread_mutex_init(&status()->philo[i].time, NULL) ||
			pthread_mutex_init(&status()->philo[i].meal, NULL) ||
			pthread_mutex_init(&status()->philo[i].print, NULL))
			return ;
		i++;
	}
}

void end_join(t_status *status)
{
	int i = 0;
	while (i < status->number_of_philosophers)
	{
		if (pthread_join(status->philo[i].philosophers, NULL))
			return ;
		i++;
	}
}

void free_all(void)
{
	int i;

	i = 0;
	free(status()->philo);
	if (i < status()->number_of_philosophers)
	{
		pthread_mutex_destroy(&status()->philo[i].fork_right.fork_lock);
		pthread_mutex_destroy(&status()->philo[i].meal);
		pthread_mutex_destroy(&status()->philo[i].time);
		pthread_mutex_destroy(&status()->philo[i].print);
		i++;
	}
	pthread_mutex_destroy(&status()->food);
	pthread_mutex_destroy(&status()->life);
}
