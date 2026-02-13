*This project has been created as part of the 42 curriculum by gcassi-d, xwu.*

# Minishell

## Description

**Minishell** is a project from the 42 curriculum whose goal is to recreate a simplified version of a Unix shell, inspired by Bash.

The objective is to understand in depth how a shell works by implementing one from scratch in C. This includes parsing user input, handling environment variables, managing processes, implementing built-in commands, and correctly dealing with signals and file descriptors.

Our minishell reproduces core behaviors of Bash, such as:

* Displaying a prompt and reading user input
* Executing external commands
* Managing environment variables
* Handling pipes (`|`)
* Handling input/output redirections (`<`, `>`, `>>`, `<<`)
* Implementing built-in commands
* Managing signals (e.g. `Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

This project emphasizes process control (`fork`, `execve`, `wait`), file descriptor manipulation, parsing logic, and memory management.

---

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

This will generate the executable:

```bash
./minishell
```

### Execution

To start the shell:

```bash
./minishell
```

You will then be able to execute commands similarly to Bash.

### Cleaning

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To recompile everything:

```bash
make re
```

---

## Features

### Built-in Commands

Our minishell implements the following built-ins:

* `echo`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

### Pipes

Supports chaining multiple commands:

```bash
ls -l | grep .c | wc -l
```

### Redirections

* Input redirection: `<`
* Output redirection: `>`
* Append output: `>>`
* Heredoc: `<<`

### Environment Variables

* Expansion of `$VARIABLE`
* Proper handling of `$?`

---

## Technical Overview

* Language: C
* System calls used: `fork`, `execve`, `pipe`, `dup2`, `wait`, `signal`, etc.
* Custom parsing logic to tokenize and structure commands
* Careful memory management to avoid leaks
* Signal handling adapted to interactive shell behavior

---

## Resources

The following resources were used to understand shell behavior and Unix process management:

* Bash Manual
  [https://www.gnu.org/software/bash/manual/](https://www.gnu.org/software/bash/manual/)

* Linux man pages
  [https://man7.org/linux/man-pages/](https://man7.org/linux/man-pages/)

* Advanced Programming in the UNIX Environment – W. Richard Stevens

* The Open Group Base Specifications (POSIX)
  [https://pubs.opengroup.org/onlinepubs/9699919799/](https://pubs.opengroup.org/onlinepubs/9699919799/)

* 42 subject and documentation

### AI Usage

Artificial Intelligence was used **only for writing and structuring this README file**.

AI was not used for:

* Designing the architecture
* Implementing parsing
* Writing the execution logic
* Implementing built-ins
* Debugging
* Writing any part of the source code

All code was designed and implemented entirely by **gcassi-d** and **xwu** as part of the 42 Minishell project.

---

## About the Project

Minishell is a fundamental systems programming project within the 42 curriculum. It strengthens understanding of:

* Operating system fundamentals
* Process management
* Inter-process communication
* Signals
* Low-level file descriptor handling

It serves as a strong foundation for more advanced Unix and system-level programming projects.
