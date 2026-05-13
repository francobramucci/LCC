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

-- 3)

insertar :: Punto p => p -> NdTree p -> NdTree p
insertar p t = ins p t 0
    where
        ins p Empty n = Node Empty p Empty (mod n (dimension p))
        ins p (Node l x r k) n | coord k p <= coord k x = Node (ins p l (k+1)) x r k
                               | otherwise = Node l x (ins p r (k+1)) k


-- 4)

equal_punto :: Punto p => p -> p -> Bool
equal_punto x y = eq x y (dimension x - 1)
    where
        eq x y 0 = (coord 0 x) == (coord 0 y)
        eq x y n = (coord n x) == (coord n y) && eq x y (n-1)

instance Eq Punto2d where
    x == y = x `equal_punto` y

instance Eq Punto3d where
    x == y = x `equal_punto` y

eliminar :: (Eq p, Punto p) => p -> NdTree p -> NdTree p
eliminar p Empty = Empty
eliminar p t@(Node l x r k) | p == x = replace t
                            | coord k p <= coord k x = Node (eliminar p l) x r k 
                            | coord k p > coord k x = Node l x (eliminar p r) k 

replace :: (Eq p, Punto p) => NdTree p -> NdTree p
replace (Node Empty x Empty _) = Empty
replace (Node l x Empty e) = let max_e_left = maxETree l e in Node (eliminar max_e_left l) max_e_left Empty e 
replace (Node l x r e) = let min_e_right = minETree r e in Node l min_e_right (eliminar min_e_right r) e 

minE :: Punto p => p -> p -> Int -> p
minE p q e = if coord e p < coord e q then p else q

minETree :: Punto p => NdTree p -> Int -> p
minETree (Node Empty p Empty _) _ = p
minETree (Node Empty p r _) e = minE p (minETree r e) e
minETree (Node l p Empty _) e = minE p (minETree l e) e
minETree (Node l p r _) e = minE p (minE (minETree r e) (minETree l e) e) e

maxE :: Punto p => p -> p -> Int -> p
maxE p q e = if coord e p > coord e q then p else q

maxETree :: Punto p => NdTree p -> Int -> p
maxETree (Node Empty p Empty _) _ = p
maxETree (Node Empty p r _) e = maxE p (maxETree r e) e
maxETree (Node l p Empty _) e = maxE p (maxETree l e) e
maxETree (Node l p r _) e = maxE p (maxE (maxETree r e) (maxETree l e) e) e

-- 5)

type Rect = (Punto2d, Punto2d)

-- a)

inRegion :: Punto2d -> Rect -> Bool
inRegion (P2d (x, y)) (P2d (a, b), P2d (c, d)) = x >= a && x <= c && y >= b && y <= d

-- b)

ortogonalSearch :: NdTree Punto2d -> Rect -> [Punto2d]
ortogonalSearch Empty _ = []
ortogonalSearch t rec = ortaux t rec []

ortaux :: NdTree Punto2d -> Rect -> [Punto2d] -> [Punto2d]
ortaux Empty _ xs = xs
ortaux (Node l p@(P2d (x,y)) r e) rec@(P2d (a,b), P2d (c,d)) xs
    | e == 0 && x < a = ortaux r rec ys
    | e == 0 && x > c = ortaux l rec ys
    | e == 0 && x >= a && x <= c = ortaux l (P2d (a,b), P2d (x,d)) (ortaux r (P2d (x,b), P2d (c,d)) ys)
    | e == 1 && y < b = ortaux r rec ys
    | e == 1 && y > d = ortaux l rec ys
    | e == 1 && y >= b && y <= d = ortaux l (P2d (a,b), P2d (c, y)) (ortaux r (P2d (a,y), P2d (c,d)) ys)
    where
        ys = if inRegion p rec then p:xs else xs

