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

; deleteocurr :: List(Number), Number -> List(Number)
; occur :: Number -> Bool
(define (deleteoccur l n)
  (local((define (occur x) (not (= x n))))
    (filter occur l)
    )
  )

; deleteocur2 :: List(Number), Number -> List(Number)
(define (deleteoccur2 l n)
    (filter (lambda (x) (not(= x n)) ) l)
  )

; eliminar :: List(Number) -> List(Number)
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

; Ejercicio 13

; prod :: List(Number) -> Number
(define (prod l) (foldr * 1 l))

; Ejercicio 14

; pegar :: List(String) -> String
(define (pegar l) (foldr string-append "" l))

; Ejercicio 15

; max1 :: List(Number) -> Number
(define (max1 l) (foldr max 0 l))

; Ejercicio 16

; and1 :: Boolean, Boolean -> Boolean
(define (and1 x y) (and x y))

; todos-verdaderos :: List(Boolean) -> Boolean
(define (todos-verdaderos l) (foldr and1 #t l))

; Ejercicio 17

; lar :: Any, Number -> Number
(define (lar x y) (+ 1 y))

; largo :: List(Any) -> Number
(define (largo l) (foldr lar 0 l))

; Ejercicio 18

; mayores :: List(Number), Number -> List(Number)
(define (mayores l m)
  (local (
          (define (mayor n) (> n m))
          )
    (filter mayor l)
    )
  )

; Ejercicio 19

; largas :: List(String), Number -> List(String)
(define (largas l m)
  (local (
          (define (gtm s) (> (string-length s) m))
          )
    (filter gtm l)
    )
  )

; Ejercicio 20

; lejos  :: List(posn), Number -> List(posn)
(define (lejos l m)
  (local (
          (define (distgtm p) (> (sqrt (+ (sqr (posn-x p)) (sqr (posn-y p)))) m))
          )
    (filter distgtm l)
    )
  )

; Ejercicio 21

; sumar :: List(Number), Number -> List(Number)
(define (sumar l m)
  (local (
          (define (suma x) (+ x m))
          )
    (map suma l)
    )
  )

; Ejercicio 22

; elevar :: List(Number), Number -> List(Number)
(define (elevar l m)
  (local (
          (define (raise x) (expt x m))
          )
    (map raise l)
    )
  )

; Ejercicio 23

; sumcuad :: List(Number) -> Number
(define (sumcuad l)
  (foldr + 0 (map sqr l))
  )

; Ejercicio 24

; sumdist :: List(posn) -> Number
(define (sumdist l)
  (foldr + 0 (map distancia l))
  )

; Ejercicio 25

; multpos :: List(Number) -> Number
(define (multpos l)
  (foldr * 1 (filter positive? l))
  )

; Ejercicio 26

; sumabs :: List(Number) -> Number
(define (sumabs l)
  (foldr + 0 (map abs l))
  )

; Ejercicio 27

(define (raices1 l)
  (map sqrt (filter positive? l))
  )

; Ejercicio 28

; ancha? :: Image -> Boolean
(define (ancha? i) (> (image-width i) (image-height i)))

; area :: Image -> Number
(define (area i) (* (image-width i) (image-height i)))

; saa :: List(Image) -> Number
(define (saa l)
  (foldr + 0 (map area (filter ancha? l)))
  )

; Ejercicio 29

; sumalistpos? :: List(Number) -> Boolean
(define (sumalistpos? l)
  (> (foldr + 0 l) 0)
  )

; or1 :: Boolean, Boolean -> Boolean
(define (or1 x y) (or x y))

; algun-pos :: List(List(Number)) -> Boolean
(define (algun-pos l)
  (foldr or1 #f (map sumalistpos? l))
  )

; Ejercicio 30

; gt4? :: List(Any) -> Boolean 
(define (gt4? l) (> (length l) 4))

; long-lists :: List(List(Any)) -> Boolean
(define (long-lists l)
  (foldr and1 #t (map gt4? l))
  )

; Ejercicio 31
(define (todos-true l)
  (foldr and1 #t (filter boolean? l))
  )

; Ejercicio 32

(define-struct alumno [nombre nota faltas])


; notageq9 :: alumno -> Boolean
(define (notageq9 a) (>= (alumno-nota a) 9))
; destacados :: List(alumno) -> List(alumno)
(define (destacados l)
  (filter notageq9 l)
  )


; condic :: alumno -> String
(define (condic a)
  (cond [(>= (alumno-nota a) 8) "Promovido"]
        [(< (alumno-nota a) 6) "Libre"]
        [else "Regular"]
        )
  )
; condicion :: List(alumno) -> List(String)
(define (condicion l)
  (map condic l)
  )


; verlib :: String, Boolean -> Boolean
(define (verlib x y)
  (and (not(string=? x "Libre")) y)
  )
; exito :: List(alumno) -> Boolean
(define (exito l)
  (foldr verlib #t (condicion l)) 
  )


; regular? :: alumno -> Boolean
(define (regular? a)
  (string=? (condic a) "Regular")
  )
; sumaus :: alumno, Number -> Number
(define (sumaus x y)
  (+ (alumno-faltas x) y)
  )
; faltas-regulares :: List(alumno) -> Number
(define (faltas-regulares l)
  (foldr sumaus 0 (filter regular? l))
  )


; promaus3 :: alumno -> Boolean
(define (promaus3 a)
  (and (string=? (condic a) "Promovido") (>= (alumno-faltas a) 3))
  )
; promovidos-ausentes :: List(alumno) -> List(String)
(define (promovidos-ausentes l)
  (map alumno-nombre (filter promaus3 l))
  )














