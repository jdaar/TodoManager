# Todo Manager

An app written in C made to manage todos _(Made to work on UNIX based systems)_

## Installation

You just have to run the next command in your terminal _(on UNIX based systems)_ *(This assuming you have the dependency json-c installed already)*

```bash
make install
```

_(Optional, but recommended)_

```bash
tm -N
```

## Make options

```makefile
CC = C compiler (GCC by default)
JSON_PATH = The path in which the JSON will be located
INSTALL_DIR = The path in which the binary will be located
CFLAGS = C compiler flags
```

## Commands

```makefile
tm -n = Create new todo
tm -r = Remove todo
tm -m = Modify todo (completed value)
tm -N = (Modifier) Create new format
```

## Examples

```bash
tm -n -N "New todo"
> Created new format
> Finished creating todo named New todo

tm -n
> Name > Todo
> Finished creating todo named Todo

tm -r 0
> Finished removing todo with index 0

tm -m 1
> Finished modifying todo with index 1

tm
> 0 > Todo ~ Uncompleted
> 1 > New todo ~ Completed
```
