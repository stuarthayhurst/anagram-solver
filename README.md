## anagram-solver
  - Solve anagrams using a simple word list

## Requirements:
  - A compiler supporting `c++-20`
  - Override the default by setting the `CXX` environment variable

## Building:
  - `make`: Builds the solver
  - `make clean`: Removes the compiled solver, if present
  - `DEBUG=[true/false]`: Environment variable to enable debug symbols
  - `FAST=[true/false]`: Environment variable to enable more optimisation flags

## Usage:
  - `./solver [WORD FILE] [CHARACTERS] [--allow-repeat]`
    - For example, `./solver "/usr/share/dict/words" "ananab"`
  - `[WORD FILE]` must be a simple list of words in a text file, separated by new lines
    - `/usr/share/dict/words` is a good example
  - `[CHARACTERS]` must be the anagram to solve
  - `--allow-repeat` allows the solver to use characters more than once
    - This would allow `banana` to be a valid solution for `ban`
