/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 18:01:39 by eduarodr          #+#    #+#             */
/*   Updated: 2023/07/20 19:15:01 by eduarodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	fork_take(t_philo *philo, int condition)
{
	if (condition == 1)
	{
		pthread_mutex_lock(&philo->fork_right.fork_lock);
		print_action(philo, "has taken a fork");
		philo->fork_right.fork_take = 1;
		pthread_mutex_unlock(&philo->fork_right.fork_lock);
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		print_action(philo, "has taken a fork");
		philo->fork_left->fork_take = 1;
		pthread_mutex_unlock(&philo->fork_left->fork_lock);
		return ;
	}
	else
	{
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		print_action(philo, "has taken a fork");
		philo->fork_left->fork_take = 1;
		pthread_mutex_unlock(&philo->fork_left->fork_lock);
		pthread_mutex_lock(&philo->fork_right.fork_lock);
		print_action(philo, "has taken a fork");
		philo->fork_right.fork_take = 1;
		pthread_mutex_unlock(&philo->fork_right.fork_lock);
		return ;
	}
}

void	fork_leave(t_philo *philo, int condition)
{
	if (condition == 1)
	{
		pthread_mutex_lock(&philo->fork_right.fork_lock);
		philo->fork_right.fork_take = 0;
		pthread_mutex_unlock(&philo->fork_right.fork_lock);
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		philo->fork_left->fork_take = 0;
		pthread_mutex_unlock(&philo->fork_left->fork_lock);
		return ;
	}
	else
	{
		pthread_mutex_lock(&philo->fork_left->fork_lock);
		philo->fork_left->fork_take = 0;
		pthread_mutex_unlock(&philo->fork_left->fork_lock);
		pthread_mutex_lock(&philo->fork_right.fork_lock);
		philo->fork_right.fork_take = 0;
		pthread_mutex_unlock(&philo->fork_right.fork_lock);
		return ;
	}
}
