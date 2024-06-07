;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname practica5_2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Ejercicio 1

(define (filtereven l)
  (filter even? l)
  )

(define (lt5 x) (< (string-length x) 5))

(define (filterlt5 l)
  (filter lt5 l)
  )

(define MAX 5)
(define (cerca p) (< (sqrt (+ (sqr (posn-x p)) (sqr (posn-y p)))) MAX) )

(define (filtercerca l)
  (filter cerca l)
  )

(define (filterpositive l)
  (filter positive? l)
  )

(define (deleteoccur l n)
  (local((define (occur x) (not (= x n))))
    (filter occur l)
    )
  )

(define (deleteoccur2 l n)
    (filter (lambda (x) (not(= x n)) ) l)
  )



(define (eliminar l)
  (local (
          ; distinto? : Number -> Boolean
          ; determina si un nro es = a (first l) 
          (define (distinto? m)
                  (not (= m (first l))))
          )
    (filter distinto? l))
  )

