-- 1)

data NdTree p = Node (NdTree p) -- subárbol izquierdo
                p               -- punto
                (NdTree p)      -- subárbol derecho
                Int             -- eje
                | Empty
    deriving (Eq, Ord, Show)

class Punto p where
    dimension :: p -> Int        -- devuelve el número de coordenadas de un punto
    coord :: Int -> p -> Double   -- devuelve la coordenada k-ésima de un punto (comenzando de 0)
    dist :: p -> p -> Double      -- calcula la distancia entre dos puntos

-- a) 

dista :: Punto p => p -> p -> Double
dista p q = distaux p q ((dimension p) - 1)

distaux :: Punto p => p -> p -> Int -> Double
distaux p q 0 = (coord 0 q - coord 0 p) ^ 2
distaux p q n = (coord n q - coord n p) ^ 2 + distaux p q (n-1)

-- b)

newtype Punto2d = P2d (Double, Double) deriving Show
newtype Punto3d = P3d (Double, Double, Double)

instance Punto Punto2d where
    dimension _ = 2
    coord 0 (P2d (x, _)) = x
    coord 1 (P2d (_, y)) = y
    dist p q = dista p q

instance Punto Punto3d where
    dimension _ = 3
    coord 0 (P3d (x, _, _)) = x
    coord 1 (P3d (_, y, _)) = y
    coord 2 (P3d (_, _, z)) = z
    dist p q = dista p q

-- 2)

fromList :: Punto p => [p] -> NdTree p
fromList ps = flAux ps (length ps) 0

flAux :: Punto p => [p] -> Int -> Int -> NdTree p
flAux [] _ _ = Empty
flAux pss@(p:_) len level = Node left med right axis
    where
        n = dimension p
        axis = mod level n
        newpss = msort pss (compk axis)
        (leqs, med, gts) = median newpss len
        med_ord = div n 2
        left = flAux leqs med_ord (level+1) 
        right = flAux gts (med_ord-1) (level+1) 

compk:: Punto p => Int -> p -> p -> Int
compk k p q | coord k p < coord k q = -1
            | coord k p > coord k q = 1
            | otherwise = 0

median :: [a] -> Int -> ([a], a, [a])
median l n = med l (div n 2) 
    where
        med (x:xs) 0 = ([], x, xs)
        med (x:xs) j = let (leqs, m, gts) = med xs (j-1) 
                       in (x: leqs, m, gts) 

msort :: [a] -> (a -> a -> Int) -> [a] 
msort [] _ = []
msort [x] _ = [x]
msort xs comp = let
                  (ls, rs) = split xs
                  (ls', rs') = (msort ls comp, msort rs comp)
                in
                  merge (ls', rs') comp

split :: [a] -> ([a], [a])
split [] = ([], [])
split [x] = ([x], [])
split (x:y:zs) = let
                   (xs, ys) = split zs
                 in
                   (x:xs, y:ys)

merge :: ([a], [a]) -> (a -> a -> Int) -> [a]
merge ([], ys) _ = ys
merge (xs, []) _ = xs
merge (xss@(x:xs), yss@(y:ys)) comp | (comp x y) <= 0 = x : merge (xs, yss) comp
                                    | otherwise = y : merge (xss, ys) comp


