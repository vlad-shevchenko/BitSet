BitSet
=====

This repository is a set of tools and Qt libraries for performing operations on binary data. Made for school project.

---

Qt library
-------------

Provides classes for operations on individual bitsets as well as evaluating bitset expressions.

`bitset` command-line tool
------------------------------------

Provides command-line interface for parsing bitset expressions. Expects a single argument - expression to parse. Returns string representation of resulting bitset if expression is correct and parsing error message otherwise.

Expressions
-----------------

Expression evaluator supports following symbols:

* Bitset as is -- a string of `0`\`s and `1`\`s
* Bitset read from file -- `file@<filepath>@` will read a bitset from file at `<filepath>`. File must exist, be accessible, be text and contain nothing except `0` and `1`. Error is thrown otherwise.
* `(` and `)` -- parenthesis for changing evaluation order.
* `!`, `&`, `|`, `^` -- bitwise negation, AND, OR, XOR. Ordered from high-priority to low-priority. Both left and right operand must be bitsets.
* `>>` and `<<` -- right and left shift. Left operand must be bitset and right one must be a number.
* `+` -- concatenation. Both left and right operand must be bitsets.

> * The higher operator is in the list the higher priority it has.
> * Be aware that string representation of bitsets are written from least-significant-bits on the left to MSB on the right. So `0100` is `2`, not `4`.
> * If bitwise operation is performed on bitsets of different length, the shorter one gets filled with `0`\`s at the end to match the length of the longer one.
> * All operands and operators may be separated by one number of whitespace characters. However, no whitespaces allowed inside bitset, number, file operator (including file path), shift operators.

Some examples of valid expressions and their results:

* `101 + 01` is `10101`.
* `110 + 101 ^ 110 & 010` is `110000`. `&` has higher priority than `^`, and `^` is higher than `+`.
* `10001 | 1011 ^ file@operator.txt@` `operator.txt` is a text file in the working directory which contains string `101`. So the expression is equivalent to `00001 | 1011 ^ 100` and is equal to `10001` since the sorted operand is filled by `0`\`s on the right side.
* `10    + 01|1&    1001`. Whitespaces are ok.
* `!101` is `10`. Trailing zeros are omitted.

Some incorrect expressions:

* `101 &`
* `+101` -- it's concatenation operator, not unary plus. So must have both operands.
* `file@new folder/operand.txt@` -- no whitespaces allowed in file path.