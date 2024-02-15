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
static void	free_and_close(t_pipex *pipex, int argc);

void	print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		printf("elemento %i: %s\n", i, str[i]);
		i++;
	}
}

int main(int argc, char **argv, char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
	{
		errors(ERR_ARG, argc);
		return (1);
	}
	access_checks(&pipex, argv, argc);
	/*if (pipe(tube) < 0)
		errors(ERR_PIPE, argc);*/
	pipex.paths = paths(envp);
	if (!pipex.paths)
		errors(ERR_PATH, argc);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	if (!pipex.cmd_paths)
		errors(ERR_PATH, argc);
	//print(pipex.cmd_paths);
	forking(&pipex, argv, envp, argc);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_and_close(&pipex, argc);
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
	{
		close(pipex->infile);
		errors(ERR_ACCESS, argc);
	}
	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		close(pipex->outfile);
		errors(ERR_ACCESS, argc);
	}
}

static void	forking(t_pipex *pipex, char **argv, char *envp[], int argc)
{	
	if (pipe(pipex->tube) < 0)
		errors(ERR_PIPE, argc);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		errors(ERR_PIPE, argc);
	else if (pipex->pid1 == 0)
	{
		if (0 > close(pipex->tube[0]))
			errors(ERR_CLS, argc);
		//write(STDOUT_FILENO, "HOLA PRIMERO\n", 13);
		first_child(pipex, argv, envp, argc);
	}
	else 
	{	
		if (0 > close(pipex->tube[1]))
			errors(ERR_CLS, argc);
		//printf("pid1: %i\n", pipex->pid1);
		pipex->pid2 = fork();
		//printf("pid2: %i\n", pipex->pid2);
		if (pipex->pid2 < 0)
			errors(ERR_PIPE, argc);
		else if (pipex->pid2 == 0)
		{
			//write(STDOUT_FILENO, "HOLA SEGUNDO\n", 13);
			second_child(pipex, argv, envp, argc);
		}
		/*if (0 > close(fd[0]))
			errors(ERR_CLS, argc);*/
	}
}

static void	free_and_close(t_pipex *pipex, int argc)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	/*if (0 > close(fd[0]))
		errors(ERR_CLS, argc);
	if (0 > close(fd[1]))
		errors(ERR_CLS, argc);*/
	if (0 > close(pipex->infile))
		errors(ERR_CLS, argc);	
	if (0 > close(pipex->outfile))
		errors(ERR_CLS, argc);
	//printf("%i\n%i\n%i\n%i\n", pipex->tube[0], pipex->tube[1], pipex->infile, pipex->outfile);
}