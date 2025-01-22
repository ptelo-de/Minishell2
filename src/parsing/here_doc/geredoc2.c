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