# comcop [WIP]

*NOTE:* this software is in an embryonic stage of development -- if you would like to contribute please introduce yourself. 

comcop is a Linux based command line history storage and retrieval utility. It is designed to work with Bash and allows for the sharing of command line history across multiple running instances of Bash (and potentially other shell utilities). comcop is designed to be lightweight; written entirely in C and employing a client/server model using UNIX sockets.

## Getting Started
comcop takes advantage of the `PROMPT_COMMAND` Bash function which is called after every command has been issued (and returned). 

## TODO List

- [ ] Randomise the name of the socket created by comcopd; modify comcop to pick up the socket name dynamically
- [ ] Implement logic within comcopd to save its input to a history file
- [ ] Write a bash installation script that binds the `comcop save [..]` command to the `PROMPT_COMMAND` hook
