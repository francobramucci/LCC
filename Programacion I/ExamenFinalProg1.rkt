;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname ExamenFinalProg1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Ejercicio 1

(define (sumanat x y)
  (cond [(zero? y) x]
        [else (sumanat (add1 x) (sub1 y))]
        )
  )

(define (prodnat x y)
  (cond [(zero? y) x]
        [(zero? (sub1 y)) x]
        [else (sumanat x (prodnat x (sub1 y)))]
        )
  )

(define (fact2 n)
  (cond [(zero? n) 1]
        [(zero? (sub1 n)) 1]
        [else (prodnat (fact2 (sub1(sub1 n))) n)]
        )
  )

; Ejercicio 2

(define (concat l1 l2)
  (cond [(empty? l1) l2]
        [else (cons (first l1) (concat (rest l1) l2))]
        )
  )

(define (repetir l n)
  (cond [(empty? l) empty]
        [(zero? n) empty]
        [else (concat l (repetir l (sub1 n)))]
        )
  )
