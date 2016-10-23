# comcop [WIP]

comcop is a Linux based command line history storage and retrieval utility. It is designed to work with Bash and allows for the sharing of command line history across multiple running instances of Bash (and potentially other shell programs). comcop is designed to be lightweight; written entirely in C and employing a client/server model using UNIX sockets.

## Getting Started
comcop takes advantage of the `PROMPT_COMMAND` Bash function which is called after every command has been issued (and returned). 
