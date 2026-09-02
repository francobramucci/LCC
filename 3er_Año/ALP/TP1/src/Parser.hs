module Parser (module Parser) where

import           Text.ParserCombinators.Parsec
import           Text.Parsec.Token
import           Text.Parsec.Language           ( emptyDef )
import           AST

-----------------------
-- Función para facilitar el testing del parser.
totParser :: Parser a -> Parser a
totParser p = do
  whiteSpace lis
  t <- p
  eof
  return t

-- Analizador de Tokens
lis :: TokenParser u
lis = makeTokenParser
  (emptyDef
    { commentStart    = "/*"
    , commentEnd      = "*/"
    , commentLine     = "//"
    , opLetter        = char '='
    , reservedNames   = ["true", "false", "skip", "if", "else", "repeat", "until"]
    , reservedOpNames = [ "+"
                        , "-"
                        , "*"
                        , "/"
                        , "<"
                        , ">"
                        , "&&"
                        , "||"
                        , "!"
                        , "="
                        , "=="
                        , "!="
                        , ";"
                        , ","
                        , "++"
                        , "--"
                        ]
    }
  )

-----------------------------------
--- Parser de expresiones enteras
-----------------------------------
-- chainl1 devuelve el valor obtenido por la aplicación asociativa a izquierda
-- de las funciones retornadas por addop a los valores retornados por intterm
-- es decir que intexp "5+3-2" = (5 `Plus` 3) `Minus` 2

intexp :: Parser (Exp Int)
intexp = chainl1 intterm addop

addop :: Parser (Exp Int -> Exp Int -> Exp Int)
addop = (reservedOp lis "+" >> return Plus)
    <|> (reservedOp lis "-" >> return Minus)

intterm :: Parser (Exp Int)
intterm = chainl1 intfactor mulop

mulop :: Parser (Exp Int -> Exp Int -> Exp Int)
mulop = (reservedOp lis "*" >> return Times)
    <|> (reservedOp lis "/" >> return Div)

intfactor :: Parser (Exp Int)
intfactor = (parens lis intexp)
    <|>     do {n <- natural lis; return (Const (fromIntegral n))}
    <|>     do {reservedOp lis "-"; iexp <- intexp; return (UMinus iexp)}
    <|>     do {varid <- identifier lis;
                do {reservedOp lis "++"; return (VarInc varid)}
                <|> 
                do {reservedOp lis "--"; return (VarDec varid)}
                <|>
                return (Var varid)
               }


------------------------------------
--- Parser de expresiones booleanas
------------------------------------

boolexp :: Parser (Exp Bool)
boolexp = chainl1 boolatom boolop

boolop :: Parser (Exp Bool -> Exp Bool -> Exp Bool)
boolop = (reservedOp lis "&&" >> return And)
    <|>  (reservedOp lis "||" >> return Or)


-- Intenta leer "==", reservedOp no consume la entrada si falla, entonces <|>
-- ejecuta el siguiente parser. Si alguno lee correctamente el op entonces
-- reservedOp si consume entrada, luego si se falla al leer la exp2 el <|> no
-- intenta probar otro parser.

boolatom :: Parser (Exp Bool)
boolatom = (parens lis boolexp)
    <|>    (reserved lis "true" >> return BTrue)
    <|>    (reserved lis "false" >> return BFalse)
    <|>    do {reservedOp lis "!"; e <- boolexp; return (Not e)} 
    <|>    do {e1 <- intexp; 
               do {reservedOp lis "=="; e2 <- intexp; return (Eq e1 e2)}
               <|>
               do {reservedOp lis "!="; e2 <- intexp; return (NEq e1 e2)}
               <|>
               do {reservedOp lis "<"; e2 <- intexp; return (Lt e1 e2)}
               <|>
               do {reservedOp lis ">"; e2 <- intexp; return (Gt e1 e2)}
              }

-----------------------------------
--- Parser de comandos
-----------------------------------

comm :: Parser Comm
comm = undefined


------------------------------------
-- Función de parseo
------------------------------------
parseComm :: SourceName -> String -> Either ParseError Comm
parseComm = parse (totParser comm)
