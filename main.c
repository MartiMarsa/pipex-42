/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:06:12 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/02/07 19:06:14 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int errors(char *error, int argc);
static void	access_checks(t_pipex *pipex, char **argv, int argc);
static void	forking(t_pipex *pipex, char **argv, char *envp[], int argc);
static void	close_pipes(t_pipex *pipex);

int main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		errors(ERR_ARG, argc);
	access_checks(&pipex, argv, argc);
	if (pipe(pipex.tube) < 0)
		errors(ERR_PIPE, argc);
	//pipex.paths = paths(envp);
	//pipex.cmd_paths = ft_split(pipex.paths, ":");
	forking(&pipex, argv, envp, argc);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_and_close(&pipex);
	return (0);
}

int errors(char *error, int argc)
{
	if (argc != 5)
	{
		write (2, error, ft_strlen(error));
		return (1);
	}
	perror(error);
	exit(EXIT_FAILURE);
}

static void	access_checks(t_pipex *pipex, char **argv, int argc)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		errors(ERR_ACCESS, argc);
	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->outfile < 0)
		errors(ERR_ACCESS, argc);
}

static void	forking(t_pipex *pipex, char **argv, char *envp[], int argc)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		errors(ERR_PIPE, argc);
	else if (pipex->pid1 == 0)
		first_child(pipex, argv, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		errors(ERR_PIPE, argc);
	else if (pipex->pid2 == 0)
		second_child(pipex, argv, envp);
}

static void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}