/* ***********************
*************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:09:19 by bde-luce          #+#    #+#             */
/*   Updated: 2025/02/12 15:45:48 by bde-luce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "executer.h"
#include "minishell.h"

void	manage_hd(t_shell *shell)
{
	t_shell	*temp;
	int		i;
	int		j;
	int		fd_hd;

	temp = shell;
	i = 0;
	while (temp->cmd[i])
	{
		j = 0;
		fd_hd = 0;
		while (temp->cmd[i]->red[j])
		{
			if (temp->cmd[i]->red[j]->type == HERE_DOC)
			{
				if (fd_hd != 0)
					close(fd_hd);
				fd_hd = hereDoc(temp->cmd[i]->red[j]->str);
			}
			j++;
		}
		temp->cmd[i]->fd_in = fd_hd;
		//printf("hd_fd_in: %d\n", temp->cmd[i]->fd_in);
		i++;
	}
}

int	last_is_infile(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;
	int		b;

	temp = cmd;
	i = 0;
	b = 1;
	while (temp->red[i])
	{
		if (temp->red[i]->type == INFILE)
			b = 0;
		else if (temp->red[i]->type == HERE_DOC)
			b = 1;
		i++;
	}
	return (b);
}

void	manage_redir(t_shell **shell)
{
	t_shell	*temp;
	int		i;
	int		j;
	char	*last_in;
	int		fd_outfile;
	int		error;

	temp = *shell;
	i = 0;
	while (temp->cmd[i])
	{
		j = 0;
		fd_outfile = 1;
		error = 0;
		while (temp->cmd[i]->red[j])
		{
			if (temp->cmd[i]->red[j]->type == INFILE)
			{
				if (access(temp->cmd[i]->red[j]->str, F_OK) == -1)
				{
					printf("Error: %s: No such file or directory\n", temp->cmd[i]->red[j]->str);
					(*shell)->exit_status = 1;
					error = 1;
					break;
				}
				else
					last_in = temp->cmd[i]->red[j]->str;
			}
			else if (temp->cmd[i]->red[j]->type == OUTFILE)
			{
				if (fd_outfile != 1)
					close(fd_outfile);
				fd_outfile = open(temp->cmd[i]->red[j]->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			}
			else if (temp->cmd[i]->red[j]->type == APPEND)
			{
				if (fd_outfile != 1)
					close(fd_outfile);
				fd_outfile = open(temp->cmd[i]->red[j]->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
			}
			j++;
		}
		if (error != 1)
		{
			if (last_is_infile(temp->cmd[i]) == 0)
			{
				if (temp->cmd[i]->fd_in != 0)
					close(temp->cmd[i]->fd_in);
				temp->cmd[i]->fd_in = get_fd_infile(last_in);
			}
		}
		//printf("redir_fd_in: %d\n", temp->cmd[i]->fd_in);
		temp->cmd[i]->fd_out = fd_outfile; //posso por isto dentro do if de erro
		//printf("redir_fd_out: %d\n", temp->cmd[i]->fd_out); 
		i++;
	}
}

int	is_build_in(t_cmd *cmd)
{
	if (!cmd || !cmd->arg || !cmd->arg[0])
		return (0);
	else if (ft_strncmp(cmd->arg[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->arg[0], "exit", 5) == 0)
		return (1);
	return (0);
}


void	executer()
{
	t_shell	*shell;
	int		i = 0;
	int		pid[4];
	int		prev_pipe0;
	int		orig_stdout;

	shell = get_shell();
	manage_hd(shell);
	manage_redir(&shell);
	prev_pipe0 = 0;
	while (shell->cmd[i])
	{
		printf("cmd: %s has fd_in[%d]: %d\n", shell->cmd[i]->arg[0], i, shell->cmd[i]->fd_in);
		printf("cmd: %s has fd_out[%d]: %d\n", shell->cmd[i]->arg[0], i, shell->cmd[i]->fd_out);

		if (shell->cmd[i + 1])
			pipe(shell->cmd[i]->pipe);

		if (!is_build_in(shell->cmd[i]))
		{
			pid[i] = fork();
			if (pid[i] == -1)
				perror("Error fork");
			if (pid[i] == 0)
			{
				if (shell->cmd[i]->fd_in != 0)
				{
					if (prev_pipe0)
						close(prev_pipe0);
					dup2(shell->cmd[i]->fd_in, STDIN_FILENO);
					close(shell->cmd[i]->fd_in);
				}
				else if (prev_pipe0)
				{
					dup2(prev_pipe0, STDIN_FILENO);
					close(prev_pipe0);
				}
				if (shell->cmd[i]->fd_out != 1)
				{
					dup2(shell->cmd[i]->fd_out, STDOUT_FILENO);
					close(shell->cmd[i]->fd_out);
				}
				else if (shell->cmd[i + 1])
					dup2(shell->cmd[i]->pipe[1], STDOUT_FILENO);
				if (shell->cmd[i + 1])
				{
					close(shell->cmd[i]->pipe[0]);
					close(shell->cmd[i]->pipe[1]);
				}
				exec_command(shell->cmd[i]->arg, make_env_arr(shell->env));
			}
			waitpid(pid[i], NULL, 0);
		}
		else
		{
			orig_stdout = dup(STDOUT_FILENO);
			if (shell->cmd[i]->fd_out != 1)
			{
				dup2(shell->cmd[i]->fd_out, STDOUT_FILENO);
				close(shell->cmd[i]->fd_out);
			}
			else if (shell->cmd[i + 1])
				dup2(shell->cmd[i]->pipe[1], STDOUT_FILENO);
			build_ins(shell->cmd[i]);
			dup2(orig_stdout, STDOUT_FILENO);
			close(orig_stdout);
		}

		if (prev_pipe0)
		{
			close(prev_pipe0);
			prev_pipe0 = 0;
		}
		if (shell->cmd[i + 1])
		{
			if (shell->cmd[i]->fd_out != 1)
				close(shell->cmd[i]->pipe[0]);
			else
				prev_pipe0 = shell->cmd[i]->pipe[0];
			close(shell->cmd[i]->pipe[1]);
		}

		if (shell->cmd[i]->fd_in != 0)
			close(shell->cmd[i]->fd_in);
		if (shell->cmd[i]->fd_out != 1)
			close(shell->cmd[i]->fd_out);
		i++;
	}	
}

//função que recebe o nome do último infile e o abre para poder retornar o fd correspondente

int	get_fd_infile(char *infile)
{
	int		fd_infile;

	fd_infile = open(infile, O_RDONLY);
	if (fd_infile == -1)
	{
		printf("Error opening infile: %s\n", infile);
		return (-1);
	}
	return (fd_infile);
}

//função de erro de open de outfile

int	error_open_outfile(int fd_outfile, char *name_outfile)
{
	if (fd_outfile == -1)
	{
		printf("Error opening outfile: %s\n", name_outfile);
		return (-1);
	}
	return (0);
}

char	**find_path(char **envp)
{
	int		i;
	char	*path_trim;
	char	**path_env;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", sizeof(char) * 5) == 0)
		{
			path_trim = trim_beggining(envp[i], "PATH=");
			path_env = ft_split(path_trim, ':');
			free(path_trim);
			return (path_env);
		}
		i++;
	}
	return (NULL);
}

char	*create_path(char *function, char **envp)
{
	int		i;
	char	**path_env;
	char	*path_join;
	char	*path;

	path_env = find_path(envp);
	i = 0;
	while (path_env && path_env[i])
	{
		path_join = ft_strjoin(path_env[i], "/");
		path = ft_strjoin(path_join, function);
		free(path_join);
		if (access(path, X_OK) == 0)
		{
			free_arr(path_env);
			return (path);
		}
		free(path);
		i++;
	}
	write(2, "Error not able to execute or find function\n", 43);
	free_arr(path_env);
	return (NULL);
}

void	error_exec(char *path, char **arr_arg, char **envp)
{
	t_shell	*shell;
	
	shell = get_shell();
	if (path)
		free(path);
	free_arr(arr_arg);
	free_arr(envp);
	free_atributes();
	free(shell->readline);
	free_lst(shell->env);
    free_lst(shell->exp);
	exit(1);
}

void	exec_command(char **args, char **envp)
{
	char	*path;

	path = create_path(args[0], envp);
	if (!path)
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 20);
	}
	else if (execve(path, args, envp) == -1)
		perror("execve error");
	error_exec(path, args, envp);
}

char	**make_env_arr(t_list *env)
{
	t_list	*temp;
	char	**env_arr;
	int		i;

	temp = env;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	env_arr = malloc(sizeof(char *) * (i + 1));
	if (!env_arr)
		return (NULL);
	temp = env;
	i = 0;
	while (temp != NULL)
	{
		env_arr[i] = ft_strdup(temp->content);
		if (!env_arr[i])
		{
			free_arr(env_arr);
			return (NULL);
		}
		i++;
		temp = temp->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}







/*pid[i] = fork();
		if (pid[i] == -1)
			perror("Error fork");
		if (pid[i] == 0)
		{
			if (shell->cmd[i]->fd_in != 0)
			{
				if (prev_pipe0)
					close(prev_pipe0);
				dup2(shell->cmd[i]->fd_in, STDIN_FILENO);
				close(shell->cmd[i]->fd_in);
			}
			else if (prev_pipe0)
			{
				dup2(prev_pipe0, STDIN_FILENO);
				close(prev_pipe0);
			
			if (shell->cmd[i]->fd_out != 1)
			{
				dup2(shell->cmd[i]->fd_out, STDOUT_FILENO);
				close(shell->cmd[i]->fd_out);
			}
			else if (shell->cmd[i + 1])
				dup2(shell->cmd[i]->pipe[1], STDOUT_FILENO);
			if (shell->cmd[i + 1])
			{
				close(shell->cmd[i]->pipe[0]);
				close(shell->cmd[i]->pipe[1]);
			}
			//if (!build_ins(shell->cmd[i]))
				exec_command(shell->cmd[i]->arg, make_env_arr(shell->env)); //verificar se houve erro para executar ou nao a funcao
			//free_all();
			//exit(shell->exit_status);
		}*/