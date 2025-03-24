;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname naturales) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Definición autoreferencial
; Un Natural es o bien
; - 0 o,  
; - add1 Natural 

; Constructores:  0 y add1
; Selectores:     sub1
; Predicados:     zero? y positive?


; Recursión sobre naturales:
; ¿Qué necesito?

; (define (f n)
;    (cond [(zero? n) ..])
;          [(positive? n) ..    (f (sub1 n))..])

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Ejemplo 1: 
; fact 0 = 1
; fact (n) = n* fact (n-1)   si n > 0

; fact : Natural -> Natural
(define (fact n)
  (cond [(zero? n)  1]
        [else (* n (fact (sub1 n)))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Ejemplo 2)
; sumatoria : Natural (Natural -> Number) -> Number
; dados un natural n y una función f devuelve la sumatoria de f para
; los valores de 0 a n.

(check-expect (sumatoria 5 sqr) (+ 1 4 9 16 25))
(check-expect (sumatoria 0 sqr) 0)
(check-expect (sumatoria 8 identity) (+ 1 2 3 4 5 6 7 8))

(define (sumatoria n f)
  (cond [(zero? n) (f 0)]
        [else (+ (f n) (sumatoria (sub1 n) f))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Ejemplo 3)
; Vimos como construir listas de tamaño arbitrario
; a partir de listas.
; ¿Podremos construir listas a partir de un natural?

; from : Natural -> List (Natural)
(check-expect (from 5) (list 0 1 2 3 4 5))
(check-expect (from 0) (list 0))

(define (from n)
  (local ((define (aux m)
            (cond [(zero? m) (cons 0 '())]
                  [else (cons m (aux (sub1 m)))])))
  ; - IN -
    (reverse (aux n))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Ejercicio: Definir una función from-to,
; que dado dos naturales n y m devuelva una
; lista con los números de n a m.

(check-expect (from-to 1 4) (list 1 2 3 4))
(check-expect (from-to 2 2) (list 2))
(check-expect (from-to 4 2) empty)

; from-to : Natural Natural -> List (Natural)
(define (from-to n m)
  (cond [(= n m) (list n)]
        [(< n m) (cons n (from-to (add1 n) m))] ; elegimos incrementar n
        [else empty]))


(check-expect (from-to2 1 4) (list 1 2 3 4))
(check-expect (from-to2 2 2) (list 2))
(check-expect (from-to2 4 2) empty)


(define (from-to2 n m)
        (local ((define (aux n m)
                  (cond [(= n m) (list n)]
                        [(< n m) (cons m (aux n (sub1 m)))] ; elegimos decrementar m
                        [else empty])))
         ; - IN -
        (reverse (aux n m))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Ejemplo 4) Ej 14 de la práctica 6
; Diseñe una función círculos que tome un número natural m y devuelva 
; una imagen cuadrada de lado 2*m^2 con m círculos azules centrados
; y radios: m^2, (m-1)^2, ... , 2^2, 1 respectivamente.
; 

; ciculos : Natural Natural -> Image
(define (circulos n m)
  (cond [(zero? n)
             (square (* 2 m m) "outline" "blue")]
        [else (place-image
                  (circle (* n n) "outline" "blue")
                  (* m m)
                  (* m m)
                  (circulos (sub1 n) m))]))

(circulos 10 10)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Ejemplo 5: Tablero de ajedrez

(define TAM 50)
; casilla amarilla
(define CB  (square TAM "solid" "yellow"))
; casilla negra
(define CN  (square TAM "solid" "black"))
; tablero vacío para 64 (8*8) casillas
(define TAB (square (* 8 TAM) "outline" "black"))


; fila : Natural Number -> Image
(define (fila n y)
  (cond [(zero? n) TAB]
        [(even? n)
           ; alterno los cuadrados CB y CN
           (place-image CB
                (- (* n TAM) (/ TAM 2))
                y 
                (fila (sub1 n) y))]
        [else
           (place-image CN
                (- (* n TAM) (/ TAM 2))
                y
                (fila (sub1 n) y))]))

(fila 8 25)
(fila 8 75)

; Ejercicio***: Definir una función tablero que use la función fila
; (o una generalización de ésta) para construir un tablero de ajedrez.
; Ayuda: Usar overlay

         