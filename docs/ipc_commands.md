# IPC Command Language

Commands begin with the ^ Character and end with &
Params are seperated by $

Example: `^Solve$NV+EH+SW+WW+E'+2W+NV+EN+SV+WN+2N+2S&`

Would be to solve with the given sequence of Grip Patterns and Rotations

| Command  | Params                | Description |
| -------- | --------------------- | ----------- |
| Solve    | (None OR Encoded Seq) | If None Executes Solve Buffer, if Encoded Seq, Executes the given sequence. Encoding can be found in `docs/encoding.md` |
| BufAdd   | Encoded Seq           | Adds the given sequence to the Solve Buffer |
| ClrBuf   | None                  | Clears the Solve Buffer |