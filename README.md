# PSU_42sh_2018

**Group members:**  
  - [@Kilio22](https://github.com/Kilio22)
  - [@HeyShafty](https://github.com/HeyShafty)
  - [@antoinegosselin](https://github.com/antoinegosselin)
  - [@rodolphedps](https://github.com/rodolphedps)
  - [@Zoujoko](https://github.com/Zoujoko)

Reproduction of the tcsh shell in C.
Passes 87.5% of tests

You must write a Unix SHELL.  
The project consists of two sections:  
- a mandatory section, which MUST be completed: display a prompt, parse and execute some commands (see below),  
- an optional section, which will only be evaluated if the mandatory section is fully functionnal.  
> :warning: Authorized functions: all functions included in the libC or the ncurses library.

# MANDATORY SECTION
This section must be COMPLETELY FUNCTIONAL. Otherwise your grade will be 0.  
Concerning command parsing and execution, you must handle:  
- spaces and tabs,
- $PATH and environment,
- errors and return value,
- redirections (‘<’, ‘>’, ‘<<’ and ‘>>’),
- pipes (‘|’),
- builtins: cd, echo, exit, setenv, unsetenv,
- separators: ‘;’, ‘&&’, ‘||’

# OPTIONAL SECTION

Here is a list of desired extras:  
- inhibitors (‘\’),
- globbings (‘*’, ‘?’, ‘[’, ’]’),
- job control (‘&’, fg),
- backticks (“’),
- parentheses (‘(’ and ‘)’),
- variables (local and env),
- special variables (term, precmd, cwdcmd, cwd, ignoreof for instance),
- history (‘!’),
- aliases,
- line edition (multiline, dynamic rebinding, auto-completion dynamic,
- scripting (a bit harsh though).

# How to use it ?
make && ./42sh, then use this program like a normal shell.
