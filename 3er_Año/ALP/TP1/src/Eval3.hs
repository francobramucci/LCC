module Eval3
  ( eval
  , State
  )
where

import           AST
import qualified Data.Map.Strict               as M
import           Data.Strict.Tuple

-- Estados 
type State = (M.Map Variable Int, String)

-- Estado vacío
-- Completar la definición
initState :: State
initState = (M.empty, [])

-- Busca el valor de una variable en un estado
-- Completar la definición
lookfor :: Variable -> State -> Either Error Int
lookfor v (m, _) = case M.lookup v m of
    Just x -> Right x
    Nothing -> Left UndefVar

-- Cambia el valor de una variable en un estado
-- Completar la definición
update :: Variable -> Int -> State -> State
update v n (m, t)= (M.insert v n m, t)

-- Agrega una traza dada al estado
-- Completar la definición
addTrace :: String -> State -> State
addTrace t' (m, []) = (m, t')
addTrace t' (m, t) = (m, t ++ " " ++ t')

-- Formatea una asignación para añadirla a la traza
formatLet :: Variable -> Int -> String
formatLet x n = "Let " ++ x ++ " " ++ show n

-- Evalúa un programa en el estado vacío
eval :: Comm -> Either Error State
eval p = stepCommStar p initState

-- Evalúa múltiples pasos de un comnado en un estado,
-- hasta alcanzar un Skip
stepCommStar :: Comm -> State -> Either Error State
stepCommStar Skip s = return s
stepCommStar c    s = do
  (c' :!: s') <- stepComm c s
  stepCommStar c' s'

-- Evalúa un paso de un comando en un estado dado
-- Completar la definición
stepComm :: Comm -> State -> Either Error (Pair Comm State)
stepComm Skip s = return (Skip :!: s)

stepComm (Let v e) s = do
    (n :!: s') <- evalExp e s
    return (Skip :!: update v n (addTrace (formatLet v n) s'))

stepComm (Seq Skip c1) s = return (c1 :!: s)

stepComm (Seq c0 c1) s = do
    (c0' :!: s') <- stepComm c0 s
    return (Seq c0' c1 :!: s')

stepComm (IfThenElse b c0 c1) s = do
    (bv :!: s') <- evalExp b s
    return ((if bv then c0 else c1) :!: s')

stepComm (RepeatUntil c b) s = return (Seq c (IfThenElse b Skip (RepeatUntil c b)) :!: s)

-- Evalúa una expresión
-- Completar la definición
evalExp :: Exp a -> State -> Either Error (Pair a State)
evalExp (Const nv) s = return (nv :!: s)

evalExp (Var x) s = do
    nv <- lookfor x s 
    return (nv :!: s)

evalExp (UMinus e) s = do
    (n :!: s') <- evalExp e s
    return (-n :!: s')

evalExp (Plus e0 e1) s = evalBinOp e0 e1 s (+)

evalExp (Minus e0 e1) s = evalBinOp e0 e1 s (-)

evalExp (Times e0 e1) s = evalBinOp e0 e1 s (*)

evalExp (Div e0 e1) s = do
    (n0 :!: s') <- evalExp e0 s
    (n1 :!: s'') <- evalExp e1 s'
    if n1 == 0 then Left DivByZero
               else return (div n0 n1 :!: s'')
    
evalExp (VarInc x) s = do
    val <- lookfor x s
    return (val+1 :!: update x (val+1) (addTrace (formatLet x (val+1)) s))

evalExp (VarDec x) s = do
    val <- lookfor x s
    return (val-1 :!: update x (val-1) (addTrace (formatLet x (val-1)) s))

evalExp BTrue s = return (True :!: s)

evalExp BFalse s = return (False :!: s)

evalExp (Lt e0 e1) s = evalBinOp e0 e1 s (<)
    
evalExp (Gt e0 e1) s = evalBinOp e0 e1 s (>)

evalExp (Eq e0 e1) s = evalBinOp e0 e1 s (==)

evalExp (NEq e0 e1) s = evalBinOp e0 e1 s (/=)

evalExp (And p0 p1) s = evalBinOp p0 p1 s (&&)

evalExp (Or p0 p1) s = evalBinOp p0 p1 s (||)

evalExp (Not p0) s = do
    (b0 :!: s') <- evalExp p0 s
    return (not b0 :!: s')

-- Evalúa operaciones binarias
evalBinOp :: Exp a -> Exp a -> State -> (a -> a -> b) -> Either Error (Pair b State)
evalBinOp e0 e1 s op = do
    (a0 :!: s') <- evalExp e0 s
    (a1 :!: s'') <- evalExp e1 s'
    return ((a0 `op` a1) :!: s'')





