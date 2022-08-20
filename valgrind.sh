#!/usr/bin/env sh

# --trace-children=yes

/bin/valgrind --read-var-info=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes  --trace-children=yes --suppressions=minimal.supp ./minishell
