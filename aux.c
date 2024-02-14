/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:12 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/02/13 16:24:13 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*paths(char *envp[])
{
	char	*paths;
	int		i;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", ft_strlen("PATH")))
			i++;
		else
		{
			paths = envp[i] + ft_strlen("PATH") + 1;
			return (paths);
		}
	}
	return (paths);
}
