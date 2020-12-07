# Todo Manager
An app written in C made to manage todos *(Made to work on UNIX based systems)*

## Installation
You just have to run the next command in your terminal *(on UNIX based systems)*
`make install`
*(Optional, but recomended)*
`tm -N`

## Make options
`
CC = C compiler (GCC by default)
JSON_PATH = The path in which the JSON will be located
INSTALL_DIR = The path in which the binary will be located
CFLAGS = C compiler flags
`

## Commands
`
tm -n = Create new todo
tm -r = Remove todo
tm -m = Modify todo (completed value)
tm -N = (Modifier) Create new format
`

## Examples
`
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
`

