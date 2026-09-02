## Gramática libre de contexto para la sintaxis concreta de LIS
Utilizando precedencia para desambiguar. También se resuelven recursiones a
izquierda. Se muestra en forma factorizada.

digit    ::= '0' | '1' | ... | '9'
letter   ::= 'a' | ... | 'Z'
nat      ::= digit | digit nat
var      ::= letter | letter var

intexp   ::= term ('+' intexp | '-' intexp | e)

term     ::= factor ('*' term | '\\' term | e)

factor   ::= '(' intexp ')' 
         |   nat 
         |   var 
         |   '-' intexp 
         |   '++' var
         |   '--' var


boolexp  ::= boolatom ('&&' boolexp | '||' boolexp | e)

boolatom ::= 'true' | 'false'
         |   intexp '==' intexp
         |   intexp '!=' intexp
         |   intexp '<' intexp
         |   intexp '>' intexp
         |   '(' boolexp ')'
         |   '!' boolexp

comm     ::= commatom (';' comm | e)

commatom ::= skip
         |   var '=' intexp
         |   'if' boolexp '{' comm '}'
         |   'if' boolexp '{' comm '}' 'else' '{' comm '}'
         |   'repeat' '{' comm '}' 'until' boolexp
