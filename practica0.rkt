;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname practica0) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
; Practica 0

"Sección 2 Expresiones aritméticas"
  "Ejercicio 1"
; 1) Considere las siguientes expresiones aritméticas:

  ; 12 * 5 - 7 * 6
  (-(* 12 5) (* 7 6))

  ; 3 * 5 - 7 * 4 / 14 + 3 / 1
  (+ (* 3 5) (-(/ (* 7 4) 14)) (/ 3 1))

  ;cos(0.8) + 1/5 + sen(0.5) * 3.5
  (+ (cos 0.8) (/ 1 5) (* 3.5 (sin 0.5)))
  ;#i es un prefijo par indicar que el numero es inexacto, usualmente para irracionales.

  "Ejercicio 2"
; 2) Usando DrRacket, evalúe las siguientes expresiones:
  
  (/ 1 (sin (sqrt 3)))
  (* (sqrt 2) (sin pi))
  ; En las funciones trigonométricas los resultados siempre son inexactos a menos que z sea 0.
  ; En el caso del seno de pi, pi es un numero inexacto por lo que tenderá a 0 pero no será igual.
  (+ 3 (sqrt (- 4)))
  (* (sqrt 5) (sqrt (/ 3 (cos pi))))
  ;(/ (sqrt 5) (sin (* 3 0))) Error: División por cero.
  ;(/ (+ 3) (* 2 4)) Error: El operador + necesita dos operandos.
  (* 1 2 3 4 5 6 7 8)
  (/ 120 2 3 2 2 5) ; Divide el primer número por el resto.

"Sección 3 Strings"

; 1) Evalúe en DrRacket las siguientes expresiones.
  (string-append "Hola" "mundo")
  (string-append "Pro" "gra" "ma.")
  (number->string 1357)
  ;(string-append "La respuesta es " (+ 21 21)) (+ 21 21) No es un string. Error de tipado.
  (string-append "La respuesta es " (number->string (+ 21 21))); Debemos tipar para poder operar
  (* (string-length "Hola") (string-length "Chau"))
  (substring "Programar" 2 9)
  (string-ith "Macumbero" 4)
; Sección 4.2 Mezclando booleanos y números

; Ejercicio 1. Evalúe en DrRacket las siguientes expresiones:

(and #t (or #f (not #f)) (not #t))

(= (* 5 5) (sqrt 625))

(not (string=? (string-ith "Ada Lovelace" 2) "a"))

(overlay (regular-polygon 35 6 "solid" "white") (circle 50 "solid" "black") (circle 60 "solid" "white") (circle 70 "solid" "black") (rectangle 200 200 "solid" "blue"))

(place-image (circle 10 "solid" "blue") 40 80 (empty-scene 100 100))

"Sección 6.2 Definiendo funciones"

"Ejercicio 2"
(define (dist-origen x y) (sqrt (+ (sqr x) (sqr y))))
(dist-origen 4 3)
