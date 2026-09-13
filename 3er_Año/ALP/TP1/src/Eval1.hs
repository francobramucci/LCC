module Eval1
  ( eval
  , State
  )
where

import           AST
import qualified Data.Map.Strict               as M
import           Data.Strict.Tuple

-- Estados
type State = M.Map Variable Int

-- Estado vacío
-- Completar la definición
initState :: State
initState = M.empty 

-- Busca el valor de una variable en un estado
-- Completar la definición
lookfor :: Variable -> State -> Int
lookfor v s = s M.! v 

-- Cambia el valor de una variable en un estado
-- Completar la definición
update :: Variable -> Int -> State -> State
update = M.insert 

-- Evalúa un programa en el estado vacío
eval :: Comm -> State
eval p = stepCommStar p initState

-- Evalúa múltiples pasos de un comando en un estado,
-- hasta alcanzar un Skip
stepCommStar :: Comm -> State -> State
stepCommStar Skip s = s
stepCommStar c    s = Data.Strict.Tuple.uncurry stepCommStar $ stepComm c s

-- Evalúa un paso de un comando en un estado dado
-- Completar la definición
stepComm :: Comm -> State -> Pair Comm State
stepComm Skip s = (Skip :!: s)

stepComm (Let v e) s = let (n :!: s') = evalExp e s
                       in (Skip :!: update v n s')

stepComm (Seq Skip c1) s = (c1 :!: s) 

stepComm (Seq c0 c1) s = let (c0' :!: s') = stepComm c0 s
                         in (Seq c0' c1 :!: s')

stepComm (IfThenElse b c0 c1) s = let (bv :!: s') = evalExp b s
                                  in ((if bv then c0 else c1) :!: s')

stepComm (RepeatUntil c b) s = (Seq c (IfThenElse b Skip (RepeatUntil c b)) :!: s)


-- Evalúa una expresión
-- Completar la definición
evalExp :: Exp a -> State -> Pair a State
evalExp (Const nv) s = (nv :!: s)

evalExp (Var x) s = (lookfor x s :!: s)

evalExp (UMinus e) s = let (n :!: s') = evalExp e s
                       in (-n :!: s')

evalExp (Plus e0 e1) s = evalBinOp e0 e1 s (+)

evalExp (Minus e0 e1) s = evalBinOp e0 e1 s (-)

evalExp (Times e0 e1) s = evalBinOp e0 e1 s (*)

evalExp (Div e0 e1) s = evalBinOp e0 e1 s (div)

evalExp (VarInc x) s = let val = lookfor x s
                       in (val+1 :!: update x (val+1) s)

evalExp (VarDec x) s = let val = lookfor x s
                       in (val-1 :!: update x (val-1) s)

evalExp BTrue s = (True :!: s)

evalExp BFalse s = (False :!: s)

evalExp (Lt e0 e1) s = evalBinOp e0 e1 s (<)
    
evalExp (Gt e0 e1) s = evalBinOp e0 e1 s (>)

evalExp (Eq e0 e1) s = evalBinOp e0 e1 s (==)

evalExp (NEq e0 e1) s = evalBinOp e0 e1 s (/=)

evalExp (And p0 p1) s = evalBinOp p0 p1 s (&&)

evalExp (Or p0 p1) s = evalBinOp p0 p1 s (||)

evalExp (Not p0) s = let (b0 :!: s') = evalExp p0 s
                     in (not b0 :!: s')

-- Evalúa operaciones binarias
evalBinOp :: Exp a -> Exp a -> State -> (a -> a -> b) -> Pair b State
evalBinOp e0 e1 s op = let (a0 :!: s') = evalExp e0 s
                       in let (a1 :!: s'') = evalExp e1 s'
                          in ((a0 `op` a1) :!: s'')

