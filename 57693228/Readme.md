# StackOverflow answer code to question

This code corresponds to StackOverflow question answered
[here](https://stackoverflow.com/a/57693228/3899431).

The program is called with option parameters as:

```
pru -i abc -i cde -i -p -i fgh -p -d fgh
```
where each

1. `-i` _key_ parameter sequence indicates that the next key (`char *`,
not `int` as in question, to avoid integer conversion) means to
_insert key_ in the list (keys are inserted, not appended, to
avoid iterating all the list to search for the end).
2. `-d` _key_ parameter is to use the answer function to delete a key by
searching it on the list, the first key found is deleted from
the list.
This calls the function described in the answer.
3. `-p` just prints the whole list as it is as options
are parsed.
Options are parsed and executed as they are found in the command
line.

To build the program, just execute:
```
$ make
```
in the directory where the sources are located.
