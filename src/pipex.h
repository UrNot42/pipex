/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulevallo <ulevallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 22:14:57 by ulevallo          #+#    #+#             */
/*   Updated: 2023/09/26 23:15:14 by ulevallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define PATH "PATH="
# define PATH_SIZE 5
# define PATH_ENV_SEPARATOR ':'

/* --==--==--==--==--INCLUDES--==--==--==--==-- */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

/* --==--==--==--==--STRUCTURES--==--==--==--==-- */

typedef struct s_cmd	t_cmd;
typedef struct s_pipex	t_pipex;

struct s_cmd{
	char	*path;
	char	**cmd;
};

struct s_pipex
{
	char	*outfile;
	char	*infile;
	char	**path;
	char	**env;
	int		prev_pipe;
	t_cmd	cmd;
	int		zelda[2];
	int		pids[1024];
	int		size;
};

/* --==--==--==--==--FUNCTIONS--==--==--==--==-- */

void	child_process(t_pipex *pipex, char *cmd, int i);
int		open_fd(t_pipex *pipex, int i);
int		wait_pids(int *pids);
char	*find_path(char **possible_path, char *cmd);
char	**get_env_path(char **env);
char	*build_cmd(char *path, char *cmd);
char	**build_argv(t_pipex *pipex);
void	init_pipex(t_pipex *pipex, int ac, char **av, char **env);
void	free_dstr(char **dstr);

#endif
