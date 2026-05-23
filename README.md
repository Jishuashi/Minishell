*This project has been created as part of the 42 curriculum by hchartie, ldeplace.*

<h1 align="center">MINISHELL</h1>

<p align="center">
	<em>A minimalist Unix shell project inspired by bash.</em>
</p>

<p align="center">
	<img src="https://img.shields.io/badge/%20-LANGUAGE-6C757D?style=for-the-badge&labelColor=00599C&logo=c&logoColor=white" alt="LANGUAGE C badge" />
	&nbsp;&nbsp;
	<img src="https://img.shields.io/badge/%20-Minishell-6C757D?style=for-the-badge&labelColor=000000&logo=42&logoColor=white" alt="42 Minishell" />
	&nbsp;&nbsp;
	<img src="https://img.shields.io/badge/%20-v0.1.0-6C757D?style=for-the-badge&labelColor=4B5563" alt="version" />
</p>

<p align="center">
	<img src="https://img.shields.io/badge/Target-Unix%20Shell-6C757D?style=for-the-badge&labelColor=00599C" alt="Target Unix Shell" />
</p>


<p align="center">
	<sub>
		<code>make</code> &nbsp;•&nbsp; <code>./minishell</code>
	</sub>
</p>

---
## Description

MINISHELL is a compact, readable implementation of a Unix command interpreter. The project focuses on demonstrating core shell concepts in a clear and pedagogical way:

- Command parsing and tokenization
- Process creation and management (`fork`, `execve`, `wait`)
- I/O redirections and pipes
- Environment variable handling and builtins
- Basic signal handling (SIGINT / CTRL-C, heredoc behavior)

## Instructions

Compilation (requirements: Unix-like OS, `cc`, `make`):

```bash
make
```

Common make targets:

- `make` — compile and produce the `minishell` binary
- `make clean` — remove object files
- `make fclean` — remove object files and binary
- `make re` — `fclean` then `make`

Run:

```bash
./minishell
```

Examples:

```bash
ls -la
ps aux | grep minishell | wc -l
echo "hello" > out.txt
cat << EOF
Hello from heredoc
EOF
```

## Resources

Classic references and useful links:

- POSIX specifications: https://pubs.opengroup.org/onlinepubs/9699919799/
- `bash`/`sh` manuals for builtin and redirection behavior
- GNU Coreutils (for command behavior comparisons): https://www.gnu.org/software/coreutils/

## AI usage:

An AI assistant was used to help draft and organize parts of this `README.md`