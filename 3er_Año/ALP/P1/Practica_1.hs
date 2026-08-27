import Parsing
import Control.Applicative
import Data.Char

-- 2.

expr :: Parser Int
expr = do t <- term
          do symbol "+"
             e <- expr
             return (t+e)  
           <|>
           do symbol "-"
              e <- expr
              return (t-e)
            <|> return t

term :: Parser Int
term = do f <- factor
          do symbol "*"
             t <- term
             return (f*t)
           <|>
           do symbol "/"
              e <- term
              return (div f e)
            <|> return f     

factor :: Parser Int
factor = do symbol "("
            e <- expr
            symbol ")"
            return e
          <|> natural 
 
-- 3.

transformador :: Parser a -> Parser a
transformador p = do (symbol "(" <|> return [])
                     t <- p
                     (symbol ")" <|> return [])
                     return t

-- 4.

data Expr = Num Int | BinOp Op Expr Expr deriving Show
data Op = Add | Mul | Min | Div deriving Show

exprT :: Parser Expr

exprT = do t <- termT
           do symbol "+"
              e <- exprT
              return (BinOp Add t e)  
            <|>
            do symbol "-"
               e <- exprT
               return (BinOp Min t e)
             <|> return t


termT :: Parser Expr

termT = do f <- factorT
           do symbol "*"
              t <- termT
              return (BinOp Mul f t)
            <|>
            do symbol "/"
               e <- termT
               return (BinOp Div f e)
             <|> return f     

factorT :: Parser Expr

factorT = do symbol "("
             e <- exprT
             symbol ")"
             return e
           <|> 
           do n <- natural
              return (Num n)


-- 5.

data Basetype = DInt | DChar | DFloat deriving Show
type Hasktype = [Basetype]

auxstring :: Parser Basetype
auxstring = do symbol "Int"
               return DInt
             <|>
             do t2 <- symbol "Char"
                return DChar
              <|>
              do t3 <- symbol "Float"
                 return DFloat

parserhaskell :: Parser Hasktype
parserhaskell = sepBy auxstring (symbol "->")

-- 6.

data Numchar = Numb Int | Car Char deriving Show
type Hetlist = [Numchar]

auxnumchar :: Parser Numchar
auxnumchar = do n <- integer 
                return (Numb n)
              <|>
              do symbol "'"
                 c <- (sat isAlpha)  
                 symbol "'"
                 return (Car c)

parserlistas :: Parser Hetlist
parserlistas = do symbol "["
                  xs <- sepBy auxnumchar (symbol ",")
                  symbol "]"  
                  return xs
-- 7.

data Hasktype' = DInt' | DChar' | DFloat' | Fun Hasktype' Hasktype' deriving Show

-- term Int Char Float -> ( )
-- noterm fun var
-- inic fun
-- 
-- fun -> var"->"fun | var
-- var -> Int | Char | Float | "("fun")"
-- 
-- fun -> var -> "("fun")" -> "(" var "->" fun ")" -> "((Int -> Float)" "->" fun ")" ->
-- 
-- 
-- ((Int -> Float) -> Char -> (Float -> Int))

fun :: Parser Hasktype'

fun = do v <- var
         do symbol "->"
            f <- fun
            return (Fun v f)
          <|> return v

var :: Parser Hasktype'

var = do s <- auxstring'
         return s
       <|>
       do symbol "("
          f <- fun
          symbol ")"
          return f

auxstring' :: Parser Hasktype'

auxstring' = do symbol "Int"
                return DInt'
              <|>
              do t2 <- symbol "Char"
                 return DChar'
               <|>
               do t3 <- symbol "Float"
                  return DFloat'

-- 9
-- int*a[5] != int(*a)[5];
-- direct_declarator -> '(' direct_declarator ')' brackets | identifier brackets
-- brackets -> '[' constant_expression ']' brackets | epsilon


data CType = Pointer CType | CInt | CChar | CFloat deriving Show

type CVar = (String, CType, [Int])


declaration :: Parser CVar
declaration = do ts <- typeSpecifier
                 d <- declarator
                 symbol ";"
                 return (d ts)


declarator :: Parser (CType -> CVar)
declarator = do symbol "*"
                d <- declarator
                return (d . (\typ -> Pointer typ))
              <|>
              do d <- directDeclarator
                 return d

directDeclarator :: Parser (CType -> CVar)
directDeclarator = do symbol "("
                      dd <- directDeclarator
                      symbol ")"
                      b <- brackets
                      return ((\(id, typ, xs) -> (id, typ, xs ++ b)) . dd)
                    <|>
                    do id <- identifier
                       b <- brackets
                       return (\typ -> (id, typ, b))

typeSpecifier :: Parser CType
typeSpecifier = do symbol "int"
                   return CInt
                 <|>
                 do symbol "char"
                    return CChar
                  <|>
                  do symbol "float"
                     return CFloat

brackets :: Parser [Int]
brackets = Parsing.many ((symbol "[" >> natural) >>= (\v -> symbol "]" >>= (\v1 -> return v)))










