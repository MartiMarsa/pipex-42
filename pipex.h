/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarsa-s <mmarsa-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:05 by mmarsa-s          #+#    #+#             */
/*   Updated: 2024/02/08 19:00:07 by mmarsa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include "./libft/libft.h"

# define ERR_ARG "Incorrect nbr of commands"
# define ERR_ACCESS "Bad access"
# define ERR_PIPE "Error creating pipe"
# define ERR_FORK "Error in fork"


typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths; 
	char	**cmd_args;
	char	*cmd;
}t_pipex;

/***** MAIN FUNCTION ****/
int main(int argc, char **argv, char *envp[]);

/**** ERROR MANAGE ****/
int errors(char *error, int argc);

/**** CHILDS *****/
void	first_child(t_pipex *pipex, char **argv, char *envp[]);
void	second_child(t_pipex *pipex, char **argv, char *envp[]);

/**** FREE && CLOSE ***/
void	free_and_close(t_pipex *pipex);

#endif
