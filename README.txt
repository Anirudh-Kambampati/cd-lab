CD LAB EXAM - VERIFIED CODES (Q2, Q3, Q4, Q8, Q9, Q12)

Every program in this folder was compiled and test-run before packaging.

Q2  - lexical_analyzer.l   : lexical analyzer for identifiers, constants,
                              comments, operators, keywords
Q3  - lexical_analyzer.l   : lexical analyzer using lex (numbers,
                              identifiers, operators, parens, symbols)
Q4  - YACC programs:
      4a_arithmetic_expression -> calc.l + calc.y   (validates +,-,*,/ expr)
      4b_valid_variable        -> variable.l + variable.y
      4c_calculator            -> calculator.l + calculator.y (evaluates result)
Q8  - count.l              : counts words and lines in input
Q9  - lexical_analyzer.c   : lexical analyzer written in plain C (no lex),
                              handles keywords, identifiers, constants,
                              two-char operators (==, !=, <=, >=), symbols
Q12 - first.c              : computes FIRST() sets for a grammar; safely
                              handles LEFT RECURSION (e.g. E->E+T) and
                              multi-character terminals (e.g. id)

--------------------------------------------------------------------
BUILD & RUN
--------------------------------------------------------------------

LEX only (Q2, Q3, Q8):
  flex filename.l
  gcc lex.yy.c -o output -lfl
  ./output

YACC + LEX (Q4a, Q4b, Q4c):
  bison -d -y filename.y
  flex filename.l
  gcc y.tab.c lex.yy.c -o output -lfl
  ./output

Plain C (Q9, Q12):
  gcc filename.c -o output
  ./output

--------------------------------------------------------------------
Q12 SAMPLE INPUT (matches the grammar in the question)
--------------------------------------------------------------------
Enter number of productions: 6
E->E+T
E->T
T->T*F
T->F
F->(E)
F->id

Expected output:
FIRST(E) = { ( id }
FIRST(T) = { ( id }
FIRST(F) = { ( id }

Use '#' for epsilon in a production if you ever need it, e.g. A->#

--------------------------------------------------------------------
WHAT WAS FIXED FROM THE ORIGINAL VERSION
--------------------------------------------------------------------
- Q12 (first.c) previously crashed (segmentation fault) on left-recursive
  grammars such as E->E+T, and could not handle multi-character terminals
  like "id". It has been rewritten to tokenize full right-hand sides and
  to guard against infinite recursion on left-recursive productions.
- Q9 (lexical_analyzer.c) previously printed two-character operators like
  == and != as two separate lines ("Operator: =" twice). It now merges
  them into a single "Operator: ==" style token.
