module Lab02 where

{-
   Laboratorio 2
   EDyAII 2022
-}

import Data.List

-- 1) Dada la siguiente definición para representar árboles binarios:

data BTree a = E | Leaf a | Node (BTree a) (BTree a)

t = Node (Node (Leaf 6) (Leaf 4)) (Node E (Leaf 3))
t1 = Node (Node (Leaf 1) (Leaf 2)) (Node (Leaf 3) (Leaf 4))
-- Definir las siguientes funciones:

-- a) altura, devuelve la altura de un árbol binario.

altura :: BTree a -> Int
altura E = -1;
altura (Leaf _) = 0
altura (Node x y) = 1 + max (altura x) (altura y)

-- b) perfecto, determina si un árbol binario es perfecto (un árbol binario es perfecto si cada nodo tiene 0 o 2 hijos
-- y todas las hojas están a la misma distancia desde la raı́z).

perfecto :: BTree a -> Bool
perfecto x = perfectoAux x (altura x)

perfectoAux :: BTree a -> Int -> Bool
perfectoAux E _ = True
perfectoAux (Leaf _) i = (i == 0)
perfectoAux (Node x y) i = let res = perfectoAux x (i-1) && perfectoAux y (i-1) in
                           case (x, y) of
                           (E, E) -> res
                           ((Node _ _), (Node _ _)) -> res
                           ((Leaf _), (Leaf _)) -> res
                           (_, _) -> False

-- c) inorder, dado un árbol binario, construye una lista con el recorrido inorder del mismo.

-- Versión O(n^2)
inorder1 :: BTree a -> [a]
inorder1 E = []
inorder1 (Leaf a) = [a]
inorder1 (Node x y) = inorder1 x ++ inorder1 y

-- Versión O(n)
inorder2 :: BTree a -> [a] -> [a]
inorder2 E l = l
inorder2 (Leaf a) l = a : l
inorder2 (Node x y) l = let s = inorder2 y l in inorder2 x s

-- 2) Dada las siguientes representaciones de árboles generales y de árboles binarios (con información en los nodos):

data GTree a = EG | NodeG a [GTree a] deriving Show

data BinTree a = EB | NodeB (BinTree a) a (BinTree a) deriving Show

{- Definir una función g2bt que dado un árbol nos devuelva un árbol binario de la siguiente manera:
   la función g2bt reemplaza cada nodo n del árbol general (NodeG) por un nodo n' del árbol binario (NodeB ), donde
   el hijo izquierdo de n' representa el hijo más izquierdo de n, y el hijo derecho de n' representa al hermano derecho
   de n, si existiese (observar que de esta forma, el hijo derecho de la raı́z es siempre vacı́o).
   
   
   Por ejemplo, sea t: 
       
                    A 
                 / | | \
                B  C D  E
               /|\     / \
              F G H   I   J
             /\       |
            K  L      M    
   
   g2bt t =
         
                  A
                 / 
                B 
               / \
              F   C 
             / \   \
            K   G   D
             \   \   \
              L   H   E
                     /
                    I
                   / \
                  M   J  
-}

gt = (NodeG 'A' [(NodeG 'B' [(NodeG 'F' []), (NodeG 'G' []), (NodeG 'H' [])]), (NodeG 'C' []), (NodeG 'D' []), (NodeG 'E' [])])

g2bt :: GTree a -> BinTree a
g2bt EG = EB
g2bt n = aux n []

-- aux -> Nodo -> lista de hermanos de ese Nodo
aux :: GTree a -> [GTree a] -> BinTree a
aux EG _ = EB
aux (NodeG a []) [] = NodeB EB a EB
aux (NodeG a (x:xs)) [] = NodeB (aux x xs) a EB
aux (NodeG a []) (y:ys) = NodeB EB a (aux y ys)
aux (NodeG a (x:xs)) (y:ys) = NodeB (aux x xs) a (aux y ys)


-- 3) Utilizando el tipo de árboles binarios definido en el ejercicio anterior, definir las siguientes funciones: 
{-
   a) dcn, que dado un árbol devuelva la lista de los elementos que se encuentran en el nivel más profundo 
      que contenga la máxima cantidad de elementos posibles. Por ejemplo, sea t:
            1
          /   \
         2     3
          \   / \
           4 5   6
                             
      dcn t = [2, 3], ya que en el primer nivel hay un elemento, en el segundo 2 siendo este número la máxima
      cantidad de elementos posibles para este nivel y en el nivel tercer hay 3 elementos siendo la cantidad máxima 4.
   -}

bt = (NodeB (NodeB EB 2 (NodeB EB 4 EB)) 1 (NodeB (NodeB EB 5 EB) 3 (NodeB EB 6 EB)))
bt1 = (NodeB (NodeB (NodeB EB 4 EB) 2 EB) 1 (NodeB (NodeB EB 5 EB) 3 (NodeB EB 6 EB)))

dcn :: BinTree a -> [a]
dcn EB = []
dcn t = let maxNivel = last [b | (a, b) <- zip (cantLvl t) [0..], a == 2^b]
        in buscarNivel t maxNivel []

-- minAux :: [(Int, Int)] -> (Int, Int) -> Int
-- minAux [] (a, b) = b 
-- minAux ((d, n):xs) (a, b) = if d <= a then minAux xs (d, n) else minAux xs (a, b)

cantLvl :: BinTree a -> [Int]
cantLvl EB = []
cantLvl (NodeB l x r) = 1 : sumarIntLists (cantLvl l) (cantLvl r)

sumarIntLists :: [Int] -> [Int] -> [Int]
sumarIntLists [] ys = ys
sumarIntLists xs [] = xs
sumarIntLists (x:xs) (y:ys) = (x+y) : sumarIntLists xs ys

buscarNivel :: BinTree a -> Int -> [a] -> [a]
buscarNivel EB _ ls = ls
buscarNivel (NodeB l x r) 0 ls = x : ls
buscarNivel (NodeB l x r) n ls = let ys = buscarNivel r (n-1) ls in buscarNivel l (n-1) ys

{- b) maxn, que dado un árbol devuelva la profundidad del nivel completo
      más profundo. Por ejemplo, maxn t = 1   -}

maxn :: BinTree a -> Int
maxn EB = -1
maxn t = last [b | (a, b) <- zip (cantLvl t) [0..], a == 2^b]

{- c) podar, que elimine todas las ramas necesarias para transformar
      el árbol en un árbol completo con la máxima altura posible. 
      Por ejemplo,
         podar t = NodeB (NodeB EB 2 EB) 1 (NodeB EB 3 EB)
-}

podar :: BinTree a -> BinTree a
podar EB = EB
podar t = let (b, newtree) = podarAux t (maxn t + 1) False in newtree

podarAux :: BinTree a -> Int -> Bool -> (Bool, BinTree a)
podarAux EB 0 b = (True, EB)
podarAux EB _ b = (b, EB)
podarAux (NodeB l x r) 0 b = if b then (b, EB) else (b, (NodeB EB x EB))
podarAux (NodeB l x r) n b = (elim1, (NodeB a_izq x a_der))
    where
        (elim, a_izq) = podarAux l (n-1) b
        (elim1, a_der) = podarAux r (n-1) elim

-- primeraHojaLvl :: BinTree a -> Int -> (Int, Bool) -> (Int, Bool)
-- primeraHojaLvl EB 0 (c, b) = (c+1, True)
-- primeraHojaLvl EB _ (c, b) = (c, b)
-- primeraHojaLvl _ 0 (c, b) = (c+1, b)
-- primeraHojaLvl (NodeB l x r) n (c, b) = let (g, t) = primeraHojaLvl l (n-1) (c, b)
--                                         in if t then (g, t) else primeraHojaLvl r (n-1) (g, t)







