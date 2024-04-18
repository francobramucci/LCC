;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname Practica3) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Practica3

; Estado es un string, que representa el color del círculo a dibujar en pantalla.
; Posibles valores:
; - "blue"
; - "red"
; - "green"

; interpretar: Estado -> Image
; dado un estado, devuelve la imagen a mostrar por el programa
; (omitimos los ejemplos para faciltar la legibilidad)

; Ejercicio 1

(define
   (interpretar s)
   (place-image (circle 40 "solid" s) 100 100 (empty-scene 200 200)))
(interpretar "brown")

(define (key-manager s k) (cond [(key=? k "b") "blue"]
                                [(key=? k "v") "violet"]
                                [(key=? k "r") "red"]
                                [(key=? k "y") "yellow"]
                                [(key=? k "n") "black"]
                                [(key=? k "escape") "terminar"]
                                [(key=? k " ") is]
                                [else is]
                            )
  )
(define (terminar? s) (string=? s "terminar"))


(define is "gray")

(big-bang is
  [to-draw interpretar]
  [on-key key-manager]
  [stop-when terminar?]
  )

; Ejercicio 2

(define (circulo s)
  (cond [(and (>= s 0) (<= s 50)) (place-image (circle s "solid" "yellow") 200 200 (empty-scene 400 400))]
        [(and (> s 50) (< s 100)) (place-image (circle s "solid" "orange") 200 200 (empty-scene 400 400))]
        [(and (>= s 100) (< s 150)) (place-image (circle s "solid" "red") 200 200 (empty-scene 400 400))]
        [(>= s 150) (place-image (circle s "solid" "dark red") 200 200 (empty-scene 400 400))]
    )
  )
(define (decrease s)
  (cond [(> s 0) (- s 1)]
        [(= s 0) 100]
        )
  )
(define (increase s)
  (cond [(< s 200) (+ s 1)]
        [else 0]
    )
  )

(define (key-manager2 s) ())


(big-bang 0
  [to-draw circulo]
  [on-tick increase]
  [on-key key-manager2]
  )







