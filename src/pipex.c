/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:03:56 by ulevallo          #+#    #+#             */
/*   Updated: 2023/10/02 14:08:41 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_fd(t_pipex *pipex, int i)
{
	int	fd;

	fd = -1;
	if (i == 0)
	{
		fd = open(pipex->infile, O_RDONLY);
		if (fd == -1)
			return (perror(pipex->infile), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		dup2(pipex->prev_pipe, STDIN_FILENO);
	if (i == pipex->size - 1)
	{
		fd = open(pipex->outfile, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (fd == -1)
			return (perror(pipex->outfile), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		dup2(pipex->zelda[1], STDOUT_FILENO);
	return (0);
}

char	*find_path(char **possible_path, char *cmd)
{
	char	*tmp;
	int		i;

	if (!access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '/')
			return (write(2, cmd, ft_strlen(cmd)),
				write(2, ": No such file or directory\n", 28), NULL);
		i++;
	}
	i = 0;
	while (possible_path && possible_path[i])
	{
		tmp = build_cmd(possible_path[i], cmd);
		if (tmp && !access(tmp, F_OK | X_OK))
			return (tmp);
		if (tmp)
			free(tmp);
		i++;
	}
	return (write(2, "Command '", 9), write(2, cmd, ft_strlen(cmd)),
		write(2, "' not found\n", 12), NULL);
}

char	*build_cmd(char *path, char *cmd)
{
	char	*full_cmd;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_cmd = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_cmd)
		return (NULL);
	return (full_cmd);
}

char	**build_argv(t_pipex *pipex)
{
	int		nbword;
	char	**argv;

	nbword = 1;
	while (pipex->cmd.cmd[nbword])
		nbword++;
	argv = ft_calloc(nbword + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(pipex->cmd.path);
	if (!(argv[0]))
		return (free_dstr(argv), NULL);
	nbword = 1;
	while (pipex->cmd.cmd[nbword])
	{
		argv[nbword] = ft_strdup(pipex->cmd.cmd[nbword]);
		if (!argv[nbword])
			return (free_dstr(argv), NULL);
		nbword++;
	}
	free_dstr(pipex->cmd.cmd);
	pipex->cmd.cmd = argv;
	return (argv);
}

void	child_process(t_pipex *pipex, char *cmd, int i)
{
	if (open_fd(pipex, i))
	{
		(free_dstr(pipex->path), close(pipex->prev_pipe),
			close(pipex->zelda[0]), close(pipex->zelda[1]));
		exit(127);
	}
	close(pipex->zelda[0]);
	close(pipex->zelda[1]);
	pipex->cmd.cmd = ft_split(cmd, ' ');
	if (!pipex->cmd.cmd)
		exit(1);
	pipex->cmd.path = find_path(pipex->path, pipex->cmd.cmd[0]);
	free_dstr(pipex->path);
	if (!pipex->cmd.path)
		(free_dstr(pipex->cmd.cmd), exit(127));
	if (!build_argv(pipex))
		(free_dstr(pipex->cmd.cmd), exit(1));
	execve(pipex->cmd.path, pipex->cmd.cmd, pipex->env);
	(free(pipex->cmd.path), free_dstr(pipex->cmd.cmd), perror("execve"));
	exit(1);
}
