## Gramática libre de contexto para la sintaxis concreta de LIS
Utilizando precedencia a izquierda para desambiguar. 
También se resuelven recursiones a izquierda. 

digit     ::= '0' | '1' | ... | '9'
letter    ::= 'a' | ... | 'Z'
nat       ::= digit | digit nat
var       ::= letter | letter var

intexp    ::= intterm intexp'
intexp'   ::= '+' intterm intexp' | '-' intterm intexp' | e

intterm   ::= intfactor intterm'
intterm'  ::= '*' intfactor interm' | '/' intfactor interm' | e

intfactor ::= '(' intexp ')' 
          |   nat 
          |   var 
          |   '-' intexp 
          |   '++' var
          |   '--' var

boolexp   ::= boolterm boolexp'
boolexp'  ::= '||' boolterm boolexp' | e

boolterm  ::= boolatom boolterm'
boolterm' ::= '&&' boolatom boolterm' | e

boolatom  ::= 'true' | 'false'
          |   intexp '==' intexp
          |   intexp '!=' intexp
          |   intexp '<' intexp
          |   intexp '>' intexp
          |   '(' boolexp ')'
          |   '!' boolexp


comm      ::= commatom comm'
comm'     ::= ';' commatom comm' | e

commatom  ::= skip
          |   var '=' intexp
          |   'if' boolexp '{' comm '}'
          |   'if' boolexp '{' comm '}' 'else' '{' comm '}'
          |   'repeat' '{' comm '}' 'until' boolexp

