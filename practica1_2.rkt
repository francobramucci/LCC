;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname practica1_2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
; Practica 1 Parte 2
; Ejercicio 1
(define (sgn1 x) (if(= x 0) 0 (if(< x 0) -1 1)))

(define (sgn2 x)
  (cond [(= x 0) 0]
        [(< x 0) -1]
        [(> x 0) 1]
  )
)
(sgn2 (- 2 3))
(sgn2 6)

; Ejercicio 2.2
(define (forma w h)
  (cond [(> w h) "Ancha"]
        [(< w h) "Angosta"]
        [(= w h) "Cuadrada"]
    )
  )

; Ejercicio 2.4
(define (trianclas a b c)
  (cond [(not(= (+ a b c) 180)) "La suma de los angulos interiores de un triangulo debe ser igual a 180°"]
        [(= a b c) "Equilátero"]
        [(or(= a b) (= a c) (= b c)) "Isósceles"]
        [else "Escaleno"]
    )
  )
(trianclas 45 45 90)

; Ejercicio 2.6
(define PC 60)
(define PL 8)

(define (ofertas c l)
  (cond [(>= (+ c l) 10) (* (+ (* c PC) (* l PL)) 0.72)]
        [(and (>= c 4) (>= l 5)) (+ (* l PL 0.85) (* c PC 0.90))]
        [(>= l 5) (+ (* l PL 0.85) (* c PC))]
        [(>= c 4) (+ (* c PC 0.90) (* l PL))]
    )
  )

; Ejercicio 2.7
(define (pitagorica? a b c)
  (cond [(= (+ (sqr a) (sqr b)) (sqr c)) (string-append "Los numeros: " (number->string a) ", " (number->string b) ", y " (number->string c) " forman una terna pitagórica" )]
        [else (string-append "Los numeros: " (number->string a) ", " (number->string b) ", y " (number->string c) " NO forman una terna pitagórica" )]
    )
  )
(pitagorica? 3 4 5)

; Ejercicio 3
(define (pitagoricdes? a b c)
  (cond [(or(= (+ (sqr a) (sqr b)) (sqr c)) (= (+ (sqr c) (sqr b)) (sqr a)) (= (+ (sqr a) (sqr c)) (sqr b))) #true]
        [else #false]
    )
  )

; Ejercicio 4
(define (clasif w h)
  (cond [(= w h) "Cuadrada"]
        [(> h (* 2 w)) "Muy angosta"]
        [(> w (* 2 h)) "Muy gorda"]
        [(> w h) "Ancha"]
        [(> h w) "Angosta"]
    )
  )

; Ejercicio 5
(define (clasificar t)
  (cond [(<= t 0) "Muy frío (MF)"]
        [(and (> t 0) (< t 15)) "Frío (F)"]
        [(and (>= t 15) (<= t 25)) "Agradable (A)"]
        [(> t 25) "Caluroso (C)"]
        )
  )

; Ejercicio 6
(define (sgn3 x)
  (cond [(number? x) (sgn3 x)]
        [x 1]
        [(not x) 0]
    )
  )
(sgn3 #false)




