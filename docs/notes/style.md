# Style

[Return to docs](../docs.md)

### clang-format
Sylph uses a custom [clang-format](.././.clang-format) based on Stroustrup style.

To run clang-format recursively over the directory, the following scripts may be used:

**Command Prompt (Windows cmd)**
	`for /r %f in (*.hpp *.cpp) do clang-format -i %f`

**PowerShell**
	`TODO`

**Bash**
	`find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;`

Please view [the documentation for clang-format](https://clang.llvm.org/docs/ClangFormat.html) if necessary.

### Braces
- Opening braces go on the same line as the preceding statement, with the exception of non-inline function definitions
- Closing braces may occupy the same line as its opening partner if the block is empty.
- If the block is not empty, the closing braces should occupy its own line, to be shared only with a semicolon or do...while closing statement.
- Exception: empty or one-line lambda function definitions may occupy a single line.
- Braces MUST be present for all control flow and loop statements.

### Capitalization and Typing
- Capitalized_Snake_Case for types such as classes, structs, and aliases
- lower_snake_case for variables, local constants, and lambdas
- UPPER_SNAKE for global constants or enumeration values
- lowerCamelCase() for all functions, including std::function objects but excluding lambdas
(TODO double check std::function object nomenclature)

### Initializer Lists
Initializer lists are always indented one more than its preceding function definition. They are not to be included in declarations which are not also definitions. Each initialization statement should occupy its own line, starting with the colon or comma.

```
Some_Class::Some_Class(Type& object1, Type& object2)
	: object1 { object2 }
	, object2 { object2 }
{
	// ...
}
```

---

[Return to Docs](../docs.md)