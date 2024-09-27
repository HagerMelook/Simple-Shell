# Simple-Shell

This project is a simple shell implemented in C that can execute basic Linux commands. It mimics a minimal shell environment where users can input commands, and the shell interprets and executes them by forking a new process.

# Features

Basic Command Execution: Executes Linux commands such as ls, pwd, echo, etc.

Process Forking: Utilizes the fork() and exec() system calls to create child processes that run the commands.

Interactive Mode: Allows the user to type commands in an interactive terminal.

Exit Functionality: Type exit to quit the shell.

# Technologies Used

C Programming Language

Linux System Calls (e.g., fork(), execvp(), wait(), etc.)

# How It Works

The shell runs in an infinite loop, waiting for user input.

When a command is entered, the shell parses the input.

A child process is created using fork(), and the command is executed in the child process using execvp().

# Installation and Usage
1- Clone the Repository:

![image](https://github.com/user-attachments/assets/dbad6c53-2b6a-4ace-a323-5b88db614d47)

2- Compile the Project: Navigate to the project directory and compile the source code:

![image](https://github.com/user-attachments/assets/f4d4e6f0-fee1-475d-953d-e151d79d6ad1)

3- Run the Shell

![image](https://github.com/user-attachments/assets/ad36c196-fe2c-4a0a-a512-d6c853efd441)

4- Example

![image](https://github.com/user-attachments/assets/88c02ff4-cf13-41f0-b970-e8d5b9fa3446)



The parent process waits for the child to finish using wait(), then prompts for the next command.
