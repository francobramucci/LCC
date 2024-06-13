;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname parcial2-2018) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Programación 1 - Segundo Parcial - Tema 1 - 2018

; Ejercicio 1

; cuantos-mayores-a : List(Int) Int -> Int
; "l" es una lista de enteros y "x" un entero. Se toman "l" y "x" como parametro y se
; devuelve la cantidad de elementos de "l" que sean mayores a "x"
; Entrada: (list 1 5 9 0 2 -3) 5. Salida: 1
(define (cuantos-mayores-a l x)
  (cond [(empty? l) 0]
        [else (if (> (first l) x) (+ 1 (cuantos-mayores-a (rest l) x)) (cuantos-mayores-a (rest l) x))]
        )
  )

(check-expect (cuantos-mayores-a (list 1 6 8 0 8) 5) 3)
(check-expect (cuantos-mayores-a (list 0 1 2 3) 3) 0)
(check-expect (cuantos-mayores-a (list 1 5 9 0 2 -3) 5) 1)
(check-expect (cuantos-mayores-a (list -2 -4 9 0 2 -3) 0) 2)

; Ejercicio 2

; Calcula el pitagórico mayor dado un par de catetos "p" representado como un posn.
; pitagorico-mayor : posn -> Number
; Entrada; (make-posn 3 4). Salida: 5
(define (pitagorico-mayor p) (sqrt (+ (sqr (posn-x p)) (sqr (posn-y p)))))

; Se recibe un posn que representa los catetos de un triángulo y se devuelve si
; su pitagórico mayor es un entero.
; pitagorico? : posn -> Boolean
; Entrada; (make-posn 3 4). Salida: #t
(define (pitagorico? p)
  (integer? (pitagorico-mayor p))
  )

; Se toma un par de catetos "p" del tipo posn, se calcula su pitagorico mayor
; y se suma al resto, que es la suma de los pitagóricos mayores del resto de los elementos
; sumpit :: posn -> Int -> Int
; Entrada: (make-posn 3 4) 5. Salida: 10
(define (sumpit p y)
  (+ (sqrt (+ (sqr (posn-x p)) (sqr (posn-y p)))) y)
  )

; f :: List(posn) -> Number
; Se recibe una lista de posn donde cada posn representa los catetos de un triángulo
; se aplica la función filter para obtener aquellos pares de catetos que cumplan la condición
; de ser catetos pitagóricos, es decir que su pitagórico mayor sea entero.
; Luego se aplica la función foldr para realizar la suma de los pitagóricos mayores de cada
; elemento.
(define (f l)
  (foldr sumpit 0 (filter pitagorico? l))
  )

(check-expect (f (list (make-posn 4 3) (make-posn 1 2) (make-posn 7 24))) 30)
(check-expect (f (list (make-posn 4 4) (make-posn 1 2))) 0)
(check-expect (f (list (make-posn 3 4) (make-posn 4 3))) 10)

; Ejercicio 3

(define-struct producto [nombre precio cant])

; monto-en-stock :: producto -> Number
; Recibe un producto y calcula el monto que representan todas las unidades
; es decir su precio unitario multiplicado por la cantidad de unidades.
; Entrada: (make-producto "huevos" 300 4). Salida: 1200 
(define (monto-en-stock p)
  (* (producto-precio p) (producto-cant p))
  )

(check-expect (monto-en-stock (make-producto "leche" 24.5 6)) 147)
(check-expect (monto-en-stock (make-producto "jabón" 30 2)) 60)
(check-expect (monto-en-stock (make-producto "huevos" 300 4)) 1200)
(check-expect (monto-en-stock (make-producto "pan" 100 90)) 9000)

(define (actualizar-stock p1 p2)
  (cond [(string=? (producto-nombre p1) (producto-nombre p2))
         (make-producto (producto-nombre p1) (/ (+ (producto-precio p1) (producto-precio p2)) 2) (+ (producto-cant p1) (producto-cant p2)))]
        [else "Los productos no tienen el mismo nombre"]
        )
  )

(check-expect (actualizar-stock (make-producto "leche" 20 5) (make-producto "leche" 30 2))
(make-producto "leche" 25 7))

(check-expect (actualizar-stock (make-producto "pan" 100 20) (make-producto "leche" 30 2))
              "Los productos no tienen el mismo nombre")
(check-expect (actualizar-stock (make-producto "pan" 100 20) (make-producto "pan" 20 5))
              (make-producto "pan" 60 25))










