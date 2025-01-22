
/* void change_signal_state(char *child_or_parent)
    []if child_or_parent == child
    {
        //stop main/parent signals
        set_signal(SIGINT, SIG_DFL)  // Allow Ctrl+C to interrupt the child
        set_signal(SIGQUIT, SIG_DFL)  // Allow Ctrl+\ to quit the child
        put child signals online
    }
    else if child_or_parent == parent
    {
        stop child signals by ignoring them in the parent process
        set_signal(SIGINT, SIG_IGN)  // Ignore Ctrl+C in the parent
        set_signal(SIGQUIT, SIG_IGN)  // Ignore Ctrl+\ in the parent
        put main signals online
    }

LINUX Signals
//SIGQUIT crtl+\
//SIGINT ctrl+c
//SIG_DFL restores defalut behavio of signal
//SIG_IGN tell the processa to ignore the signal
*/

/* void handle_redirections()
{
    // Parse for redirection (<, >, >>)
    if("<")
        fd_in
    if(">")
        fd_out
}
 */

/* int executer(t_shell tokens after expansion)
{
    child_signal
    pid = fork() // Fork a new process
    if (pid == 0) // Child process
        !Child process
        if ( cmd->fd_in != 0)
        {
            dup2(cmd->fd_in, 0);  // Redirect input
            close(cmd->fd_in);
        }
        if (cmd->output_fd != 1) 
        {
            dup2(cmd->fd_out, 1);  // Redirect output
            close(cmd->fd_out);
        }
        change_signal_state(char *child)
        if execve(cmd->path, cmd->args, shell->env fails) //sem ser built ins
            exit(EXIT_FAILURE);  // Exit if execution fails
    wait pid(pid, status, 0);
    more code for after para built ins 
    echo //done
    cd //doing  it
    pwd //done
    export //done
    unset //done
    env //done
    exit //next
    return (0);
}
        
    wait pid(pid, status, 0) //leva 3 argumentos

    //pid child para espear
    //status variable para guardar o exit code do pid quando morrer << 8 
    //0 sem flags
 */