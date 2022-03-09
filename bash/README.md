This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Notes

`wip` means "work-in-progress".


# Shellcheck

Use the `shellcheck` static code analyzer to analyze your bash scripts for errors before running them. Learn a little bit more about `shellcheck` in this answer which helped me here: [Stack Overflow: How to write bash function to print and run command when the command has arguments with spaces or things to be expanded](https://stackoverflow.com/a/71118015/4561887).

```bash
# Install shellcheck
sudo apt update && sudo apt install shellcheck 

# Use it to scan a bash .sh program
shellcheck path/to/my_script.sh
```

If you ever need to disable a shellcheck warning or error, see here: https://github.com/koalaman/shellcheck/wiki/Ignore. The syntax would look like this. The `# shellcheck disable=SC2059` syntax is what disables that `shellcheck` error code on the line immediately following it. 

```bash
hexToAscii() {
  # shellcheck disable=SC2059
  printf "\x$1"
}
```

For a info. on the shellcheck "check" errors, per their codes, see here: https://github.com/koalaman/shellcheck/wiki/Checks  
A full list is here: https://gist.github.com/nicerobot/53cee11ee0abbdc997661e65b348f375
Example page: https://github.com/koalaman/shellcheck/wiki/SC1000


# bash script generic templates:

_For an excellent bash script template, see these files as a starting points:_

1. [BEST] [argument_parsing__3_advanced__gen_prog_template.sh](argument_parsing__3_advanced__gen_prog_template.sh)
1. https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/git-disable-repos.sh
1. Another good example: my `pdf2searchablepdf` bash script:
    1. Repo: https://github.com/ElectricRCAircraftGuy/PDF2SearchablePDF
    1. Exact bash script file: https://github.com/ElectricRCAircraftGuy/PDF2SearchablePDF/blob/master/pdf2searchablepdf.sh
1. [`git-blametool.sh`](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/blob/master/useful_scripts/git-blametool.sh)
