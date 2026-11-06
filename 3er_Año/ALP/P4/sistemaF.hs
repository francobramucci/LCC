{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE TypeApplications #-}
{-# LANGUAGE ImpredicativeTypes #-}
{-# LANGUAGE ScopedTypeVariables #-}

import Prelude hiding (sum, fst, snd, Bool, and)

double :: forall x. (x -> x) -> x -> x
double = \(f :: x -> x) -> \(v :: x) -> f (f v)

type Nat = forall x. (x -> x) -> x -> x

zero :: Nat
zero = \f x -> x

suc :: Nat -> Nat
suc = \(n :: Nat) -> \(f :: x -> x) (v :: x) -> f (n @x f v) 

type PairNat = forall x. (Nat -> Nat -> x) -> x

pairNat :: Nat -> Nat -> PairNat
pairNat = \(n :: Nat) -> \(m :: Nat) -> \(f :: Nat -> Nat -> x) -> f n m

fstNat :: PairNat -> Nat
fstNat = \(p :: PairNat) -> p @Nat (\n -> \m -> n)

sndNat :: PairNat -> Nat
sndNat = \(p :: PairNat) -> p @Nat (\n -> \m -> m)

pred :: Nat -> Nat
pred = \(n :: Nat) -> sndNat (n @PairNat (\(p :: PairNat) -> pairNat (suc (fstNat p)) (fstNat p)) (pairNat zero zero))

type List x = forall y. (x -> y -> y) -> y -> y

nil :: forall x. forall y. List x
nil = \(f :: x -> y -> y) -> \(n :: y) -> n

cons :: forall x. x -> List x -> List x
cons = \(e :: x) -> \(xs :: List x) -> \(f :: x -> y -> y) -> \(n :: y) -> f e (xs @y f n)

map1 :: forall x. forall y. (x -> y) -> List x -> List y
map1 = \(f :: x -> y) -> \(zs :: List x) -> zs @(List y) (\(z :: x) -> \(l :: List y) -> cons @y (f z) l) (nil @y)

append :: forall x. x -> List x -> List x
append = \(e :: x) -> \(xs :: List x) -> xs @(List x) (\(h :: x) -> \(t :: List x) -> cons @x h t) (cons @x e (nil @x))

reverse :: forall x. List x -> List x
reverse = \(xs :: List x) -> xs @(List x) (\(e :: x) -> \(l :: List x) -> append @x e l) (nil @x)

sum :: List Nat -> Nat
sum = \(ns :: List Nat) -> ns @Nat (\(n :: Nat) -> \(s :: Nat) -> suma n s) zero

suma :: Nat -> Nat -> Nat
suma = \(n :: Nat) -> \(m :: Nat) -> n @Nat suc m

insert :: forall x. (x -> x -> Bool) -> List x -> x -> List x
insert = \(c :: x -> x -> Bool) -> 
         \(xs :: List x) -> 
         \(y :: x) -> fst @(List x) @Bool (xs @(Pair (List x) Bool)
                              (\(e :: x) -> 
                               \(p :: Pair (List x) Bool) -> (and (snd @(List x) @Bool p) (c y e)) 
                                                              @(Pair (List x) Bool) 
                                                              (pair @(List x) @Bool (cons @x e (cons @x y (fst @(List x) @Bool p))) false)
                                                              (pair @(List x) @Bool (cons @x e (fst @(List x) @Bool p)) true)
                              )
                              (pair @(List x) @Bool (nil @x) true)
                          )

type Pair x y = forall z. (x -> y -> z) -> z

pair :: forall x. forall y. x -> y -> Pair x y
pair = \(a :: x) -> \(b :: y) -> \(f :: x -> y -> z) -> f a b

fst :: forall x. forall y. Pair x y -> x
fst = \(p :: Pair x y) -> p @x (\(a :: x) -> \(b :: y) -> a)

snd :: forall x. forall y. Pair x y -> y
snd = \(p :: Pair x y) -> p @y (\(a :: x) -> \(b :: y) -> b)
                      
type Bool = forall x. x -> x -> x

true :: Bool
true = \(p :: x) -> \(q :: x) -> p

false :: Bool
false = \(p :: x) -> \(q :: x) -> q

and :: Bool -> Bool -> Bool
and = \(p :: Bool) -> \(q :: Bool) -> p @Bool q false











