# Style
### clang-format
Sylph uses a custom [clang-format](.././.clang-format) based on stroustrup style. Differences include:
- empty braces may occupy a single line
- some indentation stuff i don't actually remember, oops

To run clang-format recursively over the directory, the following scripts may be used:

**Windows terminal (cmd)**
	`for /r %f in (*.hpp *.cpp) do clang-format -i %f`

**Bash**
	`find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;`

**PowerShell**
	`TODO`

Please view [the documentation for clang-format](https://clang.llvm.org/docs/ClangFormat.html) if necessary.

### Capitalization
- Capitalized_Snake_Case for types
- lower_snake_case for variables, local constants, and lambdas
- UPPER_SNAKE for global constants
- lowerCamelCase() for all functions, including std::function objects but excluding lambdas