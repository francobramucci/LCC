;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname ejercicios-finales) (read-case-sensitive #t) (teachpacks ((lib "universe.rkt" "teachpack" "2htdp") (lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "universe.rkt" "teachpack" "2htdp") (lib "image.rkt" "teachpack" "2htdp")) #f)))
; Ejercicio 22

; f :: Nat -> Nat
(define (f n)
  (cond [(zero? n) 0]
        [(zero? (sub1 n)) 2]
        [(zero? (sub1 (sub1 n))) 5]
        [else (+ (f (sub1 n)) (* 2 (f (- n 3))))]
        )
  )

; Fs :: Nat -> List(Nat)
(define (Fs n)
  (local (
          (define (aux x l)
            (cond [(zero? x) (cons (f 0) l)]
                  [else (aux (sub1 x) (cons (f x) l))]
                  )
            )
          )
    ;IN
    (aux n empty)
    )
  )

(check-expect (Fs 5) (list 0 2 5 5 9 19))
(check-expect (Fs 0) (list 0))

; Ejercicio 23

(define TAM 640)

; dibujar-elipses :: Nat -> Img
(define (dibujar-elipses n)
  (cond [(zero? n) (empty-scene TAM TAM "white")]
        [else (place-image (rotate (* n 2) (ellipse (* n 10) (* n 5) "outline" "blue")) (/ TAM 2) (/ TAM 2) (dibujar-elipses (sub1 n)))]
        )
  )

; Ejercicio 24

; fun :: Nat -> Boolean
(define (fun n c)
  (cond [(< n (* c c)) #t]
        [(zero? (modulo n c)) #f]
        [else (fun n (add1 c))]
        )
  )

; prime? :: Nat -> Boolean
(define (prime? n) (fun n 2))

; goldbach :: Nat -> posn
(define (goldbach n)
  (local (
          (define (aux x y)
            (cond [(= x y) (make-posn 0 0)]
                  [else (if (and (prime? y) (prime? (- x y))) (make-posn (- x y) y) (aux x (add1 y)))]
                  )
            )
          )
    ;IN
    (aux n 2)
    )
  )

; Ejercicio 25

; aprox-pi :: Nat -> Float
(define (aprox-pi n)
  (local (
          (define (aux x acc)
            (cond [(zero? x) (sqrt (* acc 6))]
                  [else (aux (sub1 x) (+ (/ 1 (sqr x)) acc))]

                  )
            )
          )
    ;IN
    (aux n 0)
    )
  )


