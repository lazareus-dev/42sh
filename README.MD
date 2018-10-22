# 42sh
This is the final project of the Unix branch at [Le 101](https://www.le-101.fr/), the culmination of the first year of study.
This project was coded in C, following the Norm used by the school (see [References](#references) below). The program is not allowed to crash, nor leak any memory.

It was designed for MacOS but should work fine on Linux: simply `make` and enjoy!

Made with love and care by Thibault Le Cozanet, Vitor Branco & Vincent Schlumberger

## Mandatory part
* Minimum line acquisition (prompt display, reading of a command line, proper space and tabulations management)
* Builtins with their POSIX options: `cd`, `echo`, `exit`, `env`, `setenv`, `unsetenv`
* Simple execution of simple commands with arguments and path management
* Error and commands' return value management
* Redirections : ">", ">>", "<", "|"
* Logical operators: "&&", "||"
* Separator: ";"

## Bonuses
* Inhibitors: double quote ("), simple quote ('), backslash (\\)
* Advanced redirections: file output aggregation and heredoc (<<)
* Local variables and `unset` and `export` builtin
* Command history, `history` and `!` builtins (including all their features if they have any)
* Dynamic autocompletion with <kbd>Tab</kbd>
* Hash table for binaries, and `hash` command
* Line edition
    * Cursor movement
        * <kbd>Right/Left</kbd> Move letter by letter
        * <kbd>Alt</kbd> + <kbd>Right/Left</kbd> Move word by word
        * <kbd>Home/End</kbd> Get to the beginning/end of the command
    * Cut/copy/paste
        * <kbd>Alt</kbd> + <kbd>A</kbd> Cut the whole command
        * <kbd>Alt</kbd> + <kbd>S/D</kbd> Cut everything before/after the cursor
        * <kbd>Alt</kbd> + <kbd>Z</kbd> Copy the whole command
        * <kbd>Alt</kbd> + <kbd>X/C</kbd> Copy everything before/after the cursor
        * <kbd>Alt</kbd> + <kbd>V</kbd> Paste
* <kbd>Ctrl</kbd> + <kbd>L</kbd> to clear the screen

## References
This a list of ressources we found useful in making this project.
- [PDF of the subject](https://cdn.intra.42.fr/pdf/pdf/845/42sh.en.pdf)
- [PDF of The Norm](https://cdn.intra.42.fr/pdf/pdf/1065/norme.en.pdf)
- [Shell Grammar](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Terminal Capabilities](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_4.html)