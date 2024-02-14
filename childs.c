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

static void	free_childs(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
		free(pipex->cmd_args[i++]);
	free(pipex->cmd_args);
	//if (pipex->cmd)
	//	free(pipex->cmd);
}

static char	*get_command(t_pipex *pipex, int argc)
{
	char	*tmp;
	char	*command;
	int		i;

	tmp = NULL;
	command = NULL;
	i = 0;
	while (pipex->cmd_paths[i])
	{
		tmp = ft_strjoin(pipex->cmd_paths[i], "/");
		if (!tmp)
			errors(ERR_MALLOC, argc);
		command = ft_strjoin(tmp, pipex->cmd_args[0]);
		free(tmp);
		if (!command)
			errors(ERR_MALLOC, argc);
		if (!access(command, F_OK | R_OK))
		{
			//printf("%s\n", command);
			return (command);
		}
		free(command);
		i++;
	}
	return (command);
}


void	first_child(t_pipex *pipex, char **argv, char *envp[], int argc)
{
	if (0 > close(pipex->tube[0]))
		errors(ERR_CLS, argc);
	if (0 > dup2(pipex->tube[1], STDOUT_FILENO))
		errors(ERR_DUP2, argc);
	if (0 > close(pipex->tube[1]))
		errors(ERR_CLS, argc);
	if (0 > dup2(pipex->infile, STDIN_FILENO))
		errors(ERR_DUP2, argc);	
	pipex->cmd_args = ft_split(argv[2], ' ');
	pipex->cmd = get_command(pipex, argc);
	if (!pipex->cmd)
	{
		free_childs(pipex);
		errors(ERR_CMD, argc);
	}
	if (0 > execve(pipex->cmd, pipex->cmd_args, envp))
	{
		free_childs(pipex);
		errors(ERR_EXC, argc);
	}
}

void	second_child(t_pipex *pipex, char **argv, char *envp[], int argc)
{
	if (0 > close(pipex->tube[1]))
		errors(ERR_CLS, argc);
	if (0 > dup2(pipex->tube[0], STDIN_FILENO))
		errors(ERR_DUP2, argc);
	if (0 > close(pipex->tube[0]))
		errors(ERR_CLS, argc);
	if (0 > dup2(pipex->outfile, STDOUT_FILENO))
		errors(ERR_DUP2, argc);
	pipex->cmd_args = ft_split(argv[3], ' ');
	pipex->cmd = get_command(pipex, argc);
	if (!pipex->cmd)
	{
		free_childs(pipex);
		errors(ERR_CMD, argc);
	}
	if (0 > execve(pipex->cmd, pipex->cmd_args, envp))
	{
		free_childs(pipex);
		errors(ERR_EXC, argc);
	}
}