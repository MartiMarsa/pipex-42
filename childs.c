/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:10:21 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/02/13 12:10:23 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *pipex, char **argv, char *envp[])
{
	(void)argv;
    (void)envp;
	
	close(pipex->tube[0]);
	dup2(pipex->tube[1], STDOUT_FILENO);
	close(pipex->tube[1]);
	write(STDOUT_FILENO, "hola desde 1er hijo\n", 20);
	exit(EXIT_SUCCESS);
}

void	second_child(t_pipex *pipex, char **argv, char *envp[])
{
	(void)argv;
    (void)envp;

	close(pipex->tube[1]);
	dup2(pipex->tube[0], STDIN_FILENO);
	close(pipex->tube[0]);
	write(STDIN_FILENO, "mensaje recibido desde 2o hijo\n", 31);
	exit(EXIT_SUCCESS);
}