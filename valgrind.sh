#!/usr/bin/env sh

# --trace-children=yes

valgrind --read-var-info=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes ./minishell
