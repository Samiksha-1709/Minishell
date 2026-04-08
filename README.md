# 🐚 MiniShell – Custom Linux Command-Line Interpreter

## 📌 Project Description

MiniShell is a simplified implementation of a Linux command-line shell developed in C using UNIX system calls. It mimics the basic behavior of standard shells like bash by supporting command execution, job control, signal handling, piping, and output redirection.

This project demonstrates core operating system concepts such as process creation, inter-process communication, and signal handling through hands-on implementation.

---

## 🎯 Features

* Custom shell prompt (`minishell$`)
* Built-in commands:

  * `cd` – Change directory
  * `pwd` – Print working directory
  * `echo` – Display text and special variables (`$$`, `$?`, `$SHELL`)
  * `exit` – Exit shell
* External command execution using `fork()` and `execvp()`
* Job control:

  * `jobs` – List stopped jobs
  * `fg` – Bring job to foreground
  * `bg` – Run job in background
* Signal handling:

  * `Ctrl+C` (SIGINT)
  * `Ctrl+Z` (SIGTSTP)
* Pipe support (`|`)
* Output redirection (`>`)

---

## 🛠️ Technologies Used

* **Programming Language:** C
* **Operating System:** Linux
* **System Calls:**
  `fork()`, `execvp()`, `waitpid()`, `signal()`, `kill()`, `pipe()`, `dup2()`, `open()`, `read()`, `chdir()`, `getcwd()`
* **Concepts:**
  Process Management, Signal Handling, Job Control, Inter-Process Communication (IPC)
* **Data Structures:**
  Linked List (for job management)

---

## ⚙️ Project Structure

```
MiniShell/
│
├── msh.c
├── scan.c
├── execute_internal_cmd.c
├── execute_external_cmd.c
├── signal_handler.c
├── linked_list_structure.c
├── pipe.c
├── msh.h
├── external_command.txt
└── README.md
```

---

## 🚀 How to Run

### 🔹 Compile the Project

```
gcc *.c -o minishell
```

### 🔹 Run the Shell

```
./minishell
```

---

## 📷 Sample Execution

```
minishell$ sleep 10
^Z
[1] Stopped sleep 10

minishell$ jobs
[1] Stopped sleep 10

minishell$ bg
minishell$

minishell$ fg
```

---

## 🧠 Learning Outcomes

* Understanding of process creation using `fork()`
* Execution of programs using `execvp()`
* Process synchronization using `waitpid()`
* Signal handling and job control
* Pipe implementation using `pipe()` and `dup2()`
* File descriptor manipulation and redirection

---

## ⚠️ Challenges Faced

* Handling signals without terminating the shell
* Implementing job control using linked lists
* Debugging zombie processes
* Managing multiple processes in pipe implementation
* Parsing commands with multiple spaces and arguments

---

## 📌 Future Improvements

* Support for input redirection (`<`)
* Support for multiple pipes with advanced parsing
* Command history feature
* Tab auto-completion
* Better error handling and UI improvements

---

## 👩‍💻 Author

**Samiksha T. Mane**

