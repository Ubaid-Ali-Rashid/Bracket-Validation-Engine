# Bracket Validation Engine

A C++ console application that validates nested bracket sequences — `()`, `[]`, `{}` — using a custom linked-list-based stack implementation (no STL containers). Beyond simple valid/invalid checking, it pinpoints the **exact type, position, and detail** of every bracket error in a sequence.

## Features

- **Custom stack from scratch** — built on a singly linked list (`Node` struct), no `std::stack` or other STL containers used.
- **Detailed multi-error reporting** — detects and reports *all* errors in a sequence, not just the first one.
- **Three distinct error categories:**
  | Error Type | Meaning |
  |---|---|
  | `EXTRA BRACKET` | A closing bracket appears with no matching opener |
  | `MISPLACED BRACKET` | A closing bracket doesn't match the type of the most recent open bracket |
  | `MISSING BRACKET` | An opening bracket is never closed |
- **Position tracking** — every error reports the 1-indexed position in the original string where it occurred.
- **Interactive loop** — validate multiple sequences in one run; quit anytime with `q`.

## How It Works

1. The input string is scanned character by character.
2. Opening brackets (`(`, `[`, `{`) are pushed onto the stack along with their position.
3. On a closing bracket:
   - If the stack is empty → **EXTRA BRACKET** error (nothing to match against).
   - Otherwise, the top of the stack is popped and compared. If it doesn't match the expected closer → **MISPLACED BRACKET** error.
4. After the full scan, anything still left on the stack never had a closing bracket → **MISSING BRACKET** error(s).
5. All non-bracket characters are ignored, so brackets can appear inside arbitrary text or code.

## Build & Run

```bash
g++ -o bracket_validator bracket_validator.cpp
./bracket_validator
```

## Example

```
Enter sequence (or 'q' to quit): (a[b)c]

Sequence : (a[b)c]
Result   : INVALID - 2 error(s) found.

Error 1:
  Type     : MISPLACED BRACKET
  Bracket  : )
  Position : 5
  Detail   : Found ')' but expected ']' to close '[' opened at position 3

Error 2:
  Type     : MISSING BRACKET
  Bracket  : (
  Position : 1
  Detail   : No closing bracket for '(' opened at position 1
```

```
Enter sequence (or 'q' to quit): {[()]}

Sequence : {[()]}
Result   : VALID - All brackets matched correctly.
```

## Key Concepts Demonstrated

- Linked-list-based stack (manual `push`/`pop`/`peek`, no STL)
- Dynamic memory management (`new`/`delete`)
- String/character parsing
- Structured error reporting with a fixed-size error array
- Edge case handling (empty input, only openers, only closers, unrelated characters)

## Limitations

- Maximum of 100 reported errors per sequence (fixed-size `Error` array).
- Only supports `()`, `[]`, `{}` — not angle brackets `<>` or custom delimiters.

## License

This project was built as an academic exercise in data structures (stacks, linked lists) and is free to use for learning purposes.
