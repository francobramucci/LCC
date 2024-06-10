;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname practica5_2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; filter1 :: (a -> Bool) -> [a] -> [a]
(define (filter1 f l)
  (cond [(empty? l) empty]
        [else (if (f (first l)) (cons (first l) (filter f (rest l))) (filter1 f (rest l)))]
        )
  )

; map1 :: (a -> b) -> [a] -> [b]
(define (map1 f l)
  (cond [(empty? l) empty]
        [else (cons (f (first l)) (map f (rest l)))]
        )
  )


; foldr1 :: (a -> b -> b) -> b -> [a] -> b 
(define (foldr1 f e l)
  (cond [(empty? l) e]
        [else (f (first l) (foldr1 f e (rest l)))]
        )
  )

; Ejercicio 1, 2, 3, 4 y 5
; filtereven :: List(Number) -> List(Number)
(define (filtereven l)
  (filter even? l)
  )

; lt5 :: String -> Bool
(define (lt5 x) (< (string-length x) 5))

; filterlt5 :: List(String) -> List(String)
(define (filterlt5 l)
  (filter lt5 l)
  )

(define MAX 5)
; cerca :: posn -> Bool
(define (cerca p) (< (sqrt (+ (sqr (posn-x p)) (sqr (posn-y p)))) MAX) )
; filtercerca :: List(posn) -> List (posn)
(define (filtercerca l)
  (filter cerca l)
  )

; filterpositive :: List(Number) -> List(Number) 
(define (filterpositive l)
  (filter positive? l)
  )

; deleteocurr :: List(Number) -> Number -> List(Number)
; occur :: Number -> Bool
(define (deleteoccur l n)
  (local((define (occur x) (not (= x n))))
    (filter occur l)
    )
  )

; deleteocur2 :: List(Number) -> Number -> List(Number)
(define (deleteoccur2 l n)
    (filter (lambda (x) (not(= x n)) ) l)
  )

; deleteocurr :: List(Number) -> Number -> List(Number)
(define (eliminar l)
  (local (
          ; distinto? : Number -> Boolean
          ; determina si un nro es = a (first l) 
          (define (distinto? m)
                  (not (= m (first l))))
          )
    (filter distinto? l))
  )

; Ejercicio 6

; raices :: Number -> Number
(define (raices l)
  (map sqrt l)
  )

; Ejercicio 7
; distancia :: posn -> Number
(define (distancia p)
  (sqrt (+ (sqr (posn-x p)) (sqr (posn-y p))))
  )

; distancias :: List(posn) -> List(Number)
(define (distancias l)
  (map distancia l)
  )

; Ejercicio 8

; anchos :: List(Image) -> List(Number)
(define (anchos l)
  (map image-width l)
  )

; Ejercicio 9

; sgn2 :: Number -> Number
(define (sgn2 n)
  (cond [(> n 0) 1]
        [(< n 0) -1]
        [else 0]
        )
  )
; signos :: List(Number) -> List(Number)
(define (signos l)
  (map sgn2 l)
  )

; Ejercicio 10

; cuadrados :: List(Number) -> List(Number)
(define (cuadrados l)
  (map sqr l)
  )

; Ejercicio  11

; longitudes :: List(String) -> List(Number)
(define (longitudes l)
  (map string-length l)
  )

; Ejercicio 12

; FtoC :: Number -> Number
(define (FtoC f)
  (/ (- f 32) 1.8)
  )

; convertirFC :: List(Number) -> List(Number)
(define (convertirFC l)
  (map FtoC l)
  )






