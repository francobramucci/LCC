## Gramática libre de contexto para la sintaxis concreta de LIS
Gramática no ambigua utilizando precedencia de operadores.
La gramática en sí es asociativa a derecha, no puede escribirse asociativa
a izquierda sin recursión a izquierda. Sin embargo, de esta forma, pueden
parsearse los operadores como funciones e invertir el orden de los argumentos.
Por ejemplo:

exp :: Parser (Exp Int)
exp = do
    t <- term
    f <- exp'
    return (f t)

exp' :: Parser (Exp Int -> Exp Int)
exp' = do
    symbol "-"
    t <- term
    f' <- exp'
    return (\n -> f' (Minus n t)) 
  <|> return id


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

