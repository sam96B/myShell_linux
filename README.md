# myShell_linux
The Shell or Command Line Interpreter is the fundamental User interface to an
operating system. shell—myshell—that has the following properties:
1. The shell support the following internal commands:
    - cd <directory>—Change the current default directory to <directory>. If the <directory> argument is not present, report the current directory. If the directory does not exist, an appropriate error should be reported. This command should also change the PWD environment variable.
    - clr—Clear the screen.
    - dir <directory>—List the contents of directory <directory>.
    - environ—List all the environment strings.
    - echo <comment>—Display <comment> on the display followed by a new line (multiple spaces/tabs may be reduced to a single space).
    - help—Display the user manual using the more filter.
    - pause—Pause operation of the shell until “Enter” is pressed.
    - quit—Quit the shell.
    - The shell environment should contain shell=<pathname>/myshell where <pathname>/myshell is the full path for the shell executable (not a hardwired path back to your directory, but the one from which it was executed).
2. All other command line input is interpreted as program invocation, which
should be done by the shell forking and execing the programs as its own child
processes. The programs should be executed with an environment that contains
the entry: parent=<pathname>/myshell where <pathname>/myshell
is as described in 1.ix above.
3. The shell is be able to take its command line input from a file. That is, if the
shell is invoked with a command line argument:
myshell batchfile
then batchfile is assumed to contain a set of command lines for the shell to
process. When the end-of-file is reached, the shell should exit. Obviously, if the
shell is invoked without a command line argument, it solicits input from the user
via a prompt on the display.
4. The shell support I/O redirection on either or both stdin and/or stdout.
That is, the command line
programname arg1 arg2 < inputfile > outputfile
will execute the program programname with arguments arg1 and arg2, the
stdin FILE stream replaced by inputfile and the stdout FILE stream
replaced by outputfile.
5. The shell support Arthimitic operation plus, minus, multiply, and divide.

  
## manual 

1. clone the repo
2. cd into the repo
3. run the command `make`
4. enjoy
  
## Image from the starting point. 
![alt text](https://github.com/sam96B/myShell_linux/blob/main/Screenshot%20from%202022-03-06%2017-31-04.png?raw=true)
