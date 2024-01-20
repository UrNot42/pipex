# ULEVALLO'S PIPEX

This is my pipex project from the 42 Common Core

The main goal of this project is to get acquainted
with file descriptions, the pipe idea, and the execution of functions
You also see the c function fork(), a function you will explore
further in the Philosophers project, about parallelization

## A quick description

Pipex is mainly about mimicking 
the [pipe](https://www.gnu.org/software/bash/manual/html_node/Pipelines.html) `|` operator from shell
The idea being that you redirect the output
of a certain command to be the input of the next one

like so:

`cmd1 | cmd2` => cmd2 takes the result of cmd1 as input

example `(cmd1) ls | (cmd2) cat`:
```bash
$> ls | cat
```

where `ls` prints the content present in your directory like that:
```bash
$> ls
$> file1 file2 file3 directory
```

and `cat` basically repeats what it is given (or the content of a given file) like so
```bash
$> echo "one" "two" | cat
one
two
```

## How it works

The basic principle of the pipe:

creates two file descriptors inside a `int[2]`
```c
int fd[2];
```
- `fd[1]` for writing intput
- `fd[0]` for reading output

so you create a `pipe` in which you duplicate the commands input / output


The way I built my pipex was,
that the default function would handle as many redirections as needed
So that `cmd1 | cmd2` would be the same as `cmd1 | cmd2 | ... cmdn`

### Inside the build

So with that direction in mind

(...)
the general case is simple:
