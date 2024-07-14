/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adshafee <adshafee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:39:14 by adshafee          #+#    #+#             */
/*   Updated: 2024/07/14 11:50:56 by adshafee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_pipe(char *av, char **env)
{
	char **cmd;
	char *path;

	cmd = ft_split(av, ' ');
	path = find_path(cmd[0], env);
	if (execve(path, cmd, env) == -1)
	{
		ft_printf("ERROR\n", STDERR_FILENO);
		ft_putendl_fd(cmd[0], STDERR_FILENO);
		free(path);
		ft_free_array(cmd);
		exit(1);
	}
}

void	pipe_parent_process(char **av, int *fd, char **env)
{
	int	fd2;

	fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd2 == -1)
	{
		ft_printf("Opening fd2 Failed\n");
		exit(1);
	}
	close(fd[1]);
	dup2(fd2, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	execute_pipe(av[3], env);
}

void	pipe_child_process(char **av, int *fd, char **env)
{
	int	fd1;

	fd1 = open(av[1], O_RDONLY);
	if (fd1 == -1)
	{
		ft_printf("Opening fd1 Failed\n");
		exit(1);
	}
	close(fd[0]);
	dup2(fd1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execute_pipe(av[2], env);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	pid;

	if (!(ac == 5))
	{
		ft_printf("Give 5 Arguments ");
		ft_printf("'./pipex file1 cmd1 cmd2 file2'");
		exit(1);
	}
	if (pipe(fd) == -1)
	{
		ft_printf("Pipe failed to open\n");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf("process Failed\n");
		exit(1);
	}
	if (pid == 0)
		pipe_child_process(av, fd, env);
	else
		pipe_parent_process(av, fd, env);	
}
