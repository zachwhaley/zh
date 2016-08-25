# zh

zh is an exercise in writing Unix shells, following [A Unix Shell in Ruby](http://www.jstorimer.com/blogs/workingwithcode/7766107-a-unix-shell-in-ruby).

Each shell should have four stages of development:

1. Running commands
  - Display a prompt
  - Read a command from stdin
  - Run the command as its own process (fork and exec)
2. Builtin commands
  - Change directory using a builtin `cd` command
  - Exit the shell using a builtin `exit` command
3. Environment variables
  - Display current directory in prompt
  - Change your `PATH` using a builtin `set` command
4. Configuration
  - Read simple commands from a config file
5. Pipelines
  - Implement piping, e.g. `ls | grep zh`
