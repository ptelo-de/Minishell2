#include "minishell.h"

//void	here_no_doc(t_redir	*redir)
//{
//	pid_t pid;
//	int	pipefd[2];
	
//	pid = fork();
//}

//void	find_here(t_cmd *cmd)
//{
//	int i;
//	int num;
//	int	j;

//	i = 0;
//	num = 0;
//	while (cmd->red_in[i])
//	{
//		if (cmd->red_in[i++]->type == HERE_DOC)
//			num++;
//	}
//	i = 0;
//	while (cmd->red_in[i])
//	{
//		if (cmd->red_in[i]->type == HERE_DOC && j != num)
//		{
//			here_no_doc;
//			j++;
//		}
//		else if(cmd->red_in[i]->type == HERE_DOC && j == num)
//		{

//			//here_doc;
//		}
//		i++;
//	}

//}
//void	init_here(void)
//{
//	t_shell	*shell;
//	int	i;
//	int j;

//	shell = get_shell();
//	i = 0;
//	while (shell->cmd && shell->cmd[i])
//	{
//		j = 0;
//		find_here(&shell->cmd[i]);	
//		i++;
//	}
//}
/* 
 [] fazer uma struct para o here_doc
          [] char fd[2]]
	        struct s_heredoc	*next;
	        char				*delimiter;
	int					fd[2];
	int					quotes;
	int					id;

 [] criava um pipe

 */
// [] percorrer a link list
//  [x] nao expandir o eof - flag
//  [x] pipe
//  [x] fork
//       [x] child
//          [] write to pipe
//              [] ler o promp
//              [] ler ate encontrar o eof
//              [] write no pipe e fechar o fd de escrever
//              [] deixar aberto o fd de leitura
//           [] se NAO aspas - flag
//              [] expandir as variaveis todas( sem excepcoes de quotes) dentro do pipe
//              [] //TODO  NAO remove quotes
//           [] se aspas - flag
//              [] NAO expandir as variaveis 
//              [] //TODO  NAO remove quotes
//        [] parent
//              [] read from pipe (xuxu)
//              [] waitpid;
// signals