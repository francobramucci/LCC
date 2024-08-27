;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname Examen2017T2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (f x y z) (cond [(< z (* x y)) "Blanco"]
                        [(> z (+ x y)) "Negro"]
                        [else "Chau"]
                        )
  )

(f 2 4 10)
; Proposito:
; Mixture: Si el parámetro es un número positivo o cero devolvemos su cuadrado, si es negativo, su cubo
; si el parámetro es un string devolvemos un circulo color verde cuyo radio es 10 veces el largo de la cadena
; si el parametro es una imagen devolvemos su superficie
; en caso de que el parametro no matchee su tipo de dato con alguno de los anteriores se devuelve una cadena
; notificando el error

; Signatura de tipo:
; mixture : Any -> Any
; Entrada: 30. Salida: 900
; Entrada: "hola". Salida (circle 40 "solid" "green")

(define (mixture x)
  (cond [(number? x) (if (>= x 0) (* x x) (exp 3 x))]
        [(string? x) (circle (* (string-length x) 10) "solid" "green" )]
        [(image? x) (string-append "La superficie de la imagen es: " (number->string (* (image-width x) (image-height x))))]
        [else "Tipo de dato incorrecto"]
        )
  
)

(mixture (circle 90 "solid" "green"))

(check-expect (mixture 30) 900)

;(place-image/align (triangle 70 "solid" "gold") 250 250 "right" "center" (place-image/align (circle 100 "solid" "black") 250 250 "right" "center" (empty-scene 500 500 "white")))

(define-struct rotri [angle opac mode])

(define INIT (make-rotri 0 0 0))

(define ANCHO 500)
(define ALTO 500)
(define L 80)
(define D (* L (/ (sqrt 3) 12)))
(define FONDO (empty-scene ANCHO ALTO "black"))

(define (draw s)
  (place-image (rotate s (triangle L "solid" "blue")) (/ ANCHO 2) (/ ALTO 2) FONDO)
  )

(define (draw1 s)
  (place-image (rotate (rotri-angle s) (place-image (triangle L "solid" (make-color 0 0 255 (rotri-opac s))) (/ L (sqrt 3)) (- (/ L (sqrt 3)) D) (circle (/ L (sqrt 3)) "solid" (make-color 255 255 255 0))))
               (/ ANCHO 2) (/ ALTO 2) FONDO)
  )


(define (time-driver s)
  (cond [(= (rotri-opac s) 0) (make-rotri (+ 1 (rotri-angle s)) (modulo (+ 1 (rotri-opac s)) 255) 0)]
        [(= (rotri-opac s) 254) (make-rotri (+ 1 (rotri-angle s)) (modulo (+ -1 (rotri-opac s)) 255) 1)]
        [(= (rotri-mode s) 1) (make-rotri (+ 1 (rotri-angle s)) (modulo (+ -1 (rotri-opac s)) 255) 1)]
        [(= (rotri-mode s) 0) (make-rotri (+ 1 (rotri-angle s)) (modulo (+ 1 (rotri-opac s)) 255) 0)]
        )
  )

(big-bang (make-rotri 0 0 0)
  [to-draw draw1]
  [on-tick time-driver 0.01]
)



