# Unleash-Shell
An interactive command interpreter for MINIX operating system supporting basic shell functionalities.

Unleash is a interactive command interpreter for the minix operating system. At the very basic level of understandign, the shell takes a list of commands and runs them. The start of the shell supports the setup of initial configuration required to run the commands the user intents to without overriding the environment variables of the parent Ash shell. With a support for the basic unix command execution, the shell also supports a few additional features alongside.

Basic Operations:

The basic operations supported by the shell includes

1. Invoking from the Ash shell – the default shell provided by the minix operating system.

2. Executing the default utilities supported by the Ash interpreter – ls, cd, pwd, echo, etc.

3. Display of current directory name as prompt.

4. Precedence based command execution for the command input in the format:
< command1 > < args > ; (< command1 > < args > ; < command1 > < args >)
This is supported by splitting of commands based on the delimiters: ‘,’ ‘;’ ‘|’ ‘&’

5. Prioritizing the command execution for a nested parenthesized command input – deeply nested commands within parenthesis should be executed prior to lower nested commands.Commands with the same priority are executed in a sequent order as given by the user.
 
6. Providing a persistent aliasing of a command – allowing the user to type the name of the alias for an already defined command and allow to use the alias for executing the command.

7. Terminating the shell with a confirmation prompt “Are you sure?” provided to the user. The shell shall terminate based on the user input to the prompt. This is in addition to the default behaviour of the Ash shell – to terminate with an “exit” command.
