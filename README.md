*This project has been created as part of the 42 curriculum by hchartie, ldeplace.*

<div align="center">
	<h1>MINISHELL</h1>
	<p><em>A small, educational Unix shell implemented in C — inspired by <code>bash</code>.</em></p>
	<p>
		<img alt="language" src="https://img.shields.io/badge/C-language-00599C?style=for-the-badge&logo=c&logoColor=white" />
		<img alt="minishell" src="https://img.shields.io/badge/MINISHELL-42-black?style=for-the-badge&logo=42&logoColor=white" />
	</p>
</div>

---

## Quick Start

| Action | Command |
|---|---|
| Build | `make` |
| Run | `./minishell` |
| Clean | `make fclean` |

## What this project is

MINISHELL is a compact, readable implementation of a Unix shell written in C. It is designed for learning: clear code, focused features, and easy-to-follow behavior.

## Highlights

-  Lightweight and focused implementation
-  Core concepts: `fork`, `execve`, `wait`, pipes, redirections
-  Builtins: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`

## Examples

Run a simple command:

```bash
ls -la
```

Pipe and filter:

```bash
ps aux | grep minishell | wc -l
```

Here-doc example:

```bash
cat << EOF
Hello from heredoc
EOF
```

## Project layout

- `minishell` — generated binary
- `src/` — C source files
- `includes/` — header files
- `libft/` — helper library
- `utils/` — utility and parsing code
- `obj/` — compiled object files
- `test/` — test scripts and examples

## Resources

- POSIX: https://pubs.opengroup.org/onlinepubs/9699919799/
- GNU Coreutils: https://www.gnu.org/software/coreutils/
- Tutorials: search for "write a shell in C" or "minishell project 42"

## Authors

`hchartie`, `ldeplace` — implemented as part of the 42 curriculum.

## AI Disclosure

An AI assistant helped draft and improve this `README.md`. All content was reviewed by the project authors.

---

If you want additional visual badges, a short GIF demo, or a short French version, tell me which assets or text to include and I'll update the layout.
---

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Tests](#tests)
- [Resources](#resources)
- [Authors](#authors)
- [AI Disclosure](#ai-disclosure)

---

## Description

`MINISHELL` is a compact implementation of a Unix command interpreter written in C. It focuses on clarity and pedagogy to illustrate core shell concepts:

- Command parsing and tokenization
- Process creation and management (`fork`, `execve`, `wait`)
- I/O redirections and pipes
- Environment variables and builtins
- Signal handling in interactive mode (SIGINT/CTRL-C, heredoc behavior)

This project aims to reproduce common shell behaviors without implementing every edge case of a production shell.

## Features

- Execute external commands
- Pipes (`|`) and chained pipelines
- Redirections: `>`, `>>`, `<`
- Here-documents (`<<`)
- Builtins: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`

## Usage

Build with the included `Makefile`:

```bash
make
```

Common targets:

- `make` — build the `minishell` binary
- `make clean` — remove object files
- `make fclean` — remove object files and binary
- `make re` — `fclean` then `make`

Run the shell binary:

```bash
./minishell
```

Use standard commands at the prompt. Type `exit` to leave the shell.

## Examples

Simple command:

```bash
ls -la
```

Piping and filtering:

```bash
ps aux | grep minishell | wc -l
```

Redirect output / append:

```bash
echo "hello" > out.txt
echo "more" >> out.txt
```

Here-document:

```bash
cat << EOF
Hello from heredoc
EOF
```

## Resources

- POSIX specifications: https://pubs.opengroup.org/onlinepubs/9699919799/
- `bash`/`sh` manuals for builtin and redirection behavior
- GNU Coreutils: https://www.gnu.org/software/coreutils/
- Tutorials: search for "write a shell in C" or "minishell project 42"


## AI Disclosure

An AI assistant helped draft and improve this `README.md`