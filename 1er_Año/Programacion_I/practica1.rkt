;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname practica1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
;Practica 1
"Ejercicio 1"
(define (angosta-ancha w h) (if (>= h w) "Angosta" "Ancha"))
(angosta-ancha 30 20)

"Ejercicio 2"
(define (rectangle-type w h) (if (> h w) "Angosta" (if (= h w) "Cuadrada" "Ancha")))
(rectangle-type 20 201)

"Ejercicio 3"
(define (triangle-type a b c) (if (= a b) (if (= b c) "Equilatero" "Isosceles") (if (= b c) "Isosceles" "Escaleno")) )
(triangle-type 40 40 100)

"Ejercicio 4"
(define (if-triangle-then-type a b c) (if (= 180 (+ a b c)) (triangle-type a b c) "It isn't a triangle"))
(if-triangle-then-type 40 40 100)

"Ejercicio 5"
(define PC 60)
(define PL 8)

(define (price c l) (if (> l 5)
                        (if (> c 4) (+ (* PL 0.85 l) (* PC 0.9 c)) (+ (* PL 0.85 l) (* PC c)))
                        (if (> c 4) (+ (* PL l) (* PC 0.9 c)) (+ (* PL l) (* PC c)))) )
(price 10 3)

"Ejercicio 6"
(define (better-price c l) (if (and (> (+ c l) 10) (< (* (+(* c PC) (* l PL)) 0.82) (price c l))) (* (+(* c PC) (* l PL)) 0.82) (price c l)) )
(better-price 3 10)

"Ejercicio 7"
(define (if-pitagorica a b c) (if (= (+ (sqr a) (sqr b)) (sqr c)) #t #f))
(if-pitagorica 4 4 5)

"Ejercicio 8"
(define (string-if-pitagorica a b c) (if (if-pitagorica a b c)
                                         (string-append "Los numeros " (number->string a) ", " (number->string b) " y " (number->string c) " forman una terna pitagórica")
                                         (string-append "Los numeros " (number->string a) ", " (number->string b) " y " (number->string c) " NO forman una terna pitagórica")) )
(string-if-pitagorica 4 4 5)

"Ejercicio 9"
(define (collatz n) (if (= n 1) (list 1) (if (even? n) (cons (/ n 2) (collatz (/ n 2))) (cons (+ (* 3 n) 1) (collatz (+ (* 3 n) 1))))))
(collatz 11)

"Ejercicio 10"


"Ejercicio 10a"
(define peru (place-image (rectangle 30 58 "solid" "red")
                             15 30
                             (place-image (rectangle 30 58 "solid" "red")
                             75 30
                                          (empty-scene 90 60))))

peru

"Ejercicio 10b"
(define italia (place-image (rectangle 30 58 "solid" "green")
                             15 30
                             (place-image (rectangle 30 58 "solid" "red")
                             75 30
                                          (empty-scene 90 60))))
italia

"Ejercicio 10c"

(define (3-vertical-bands-flags a b c) (place-image (rectangle 30 58 "solid" a)
                             15 30
                             (place-image (rectangle 30 58 "solid" b)
                             45 30
                             (place-image (rectangle 30 58 "solid" c)
                             75 30
                                          (empty-scene 90 60)))))


(3-vertical-bands-flags "red" "blue" "purple")

"Ejercicio 10d"

(define holanda (place-image (rectangle 90 20 "solid" "black")
                             45 10
                             (place-image (rectangle 90 20 "solid" "red")
                                          45 30
                             (place-image (rectangle 90 20 "solid" "yellow")
                                          45 50
                                          (empty-scene 90 60)))))

holanda

"Ejercicio 10e y f"

(define (3-horizontal-bands-flags a b c) (place-image (rectangle 90 20 "solid" a)
                             45 10
                             (place-image (rectangle 90 20 "solid" b)
                                          45 30
                             (place-image (rectangle 90 20 "solid" c)
                                          45 50
                                          (empty-scene 90 60)))))

(3-horizontal-bands-flags "red" "white" "blue")

"Ejercicio 10g y h"

(define (3-bands-flags a b c m) (if (string=? m "h") (3-horizontal-bands-flags a b c) (if (string=? m "v") (3-vertical-bands-flags a b c) "Inserte los modos validos horizontal (h) o vertical (v)")))

(3-bands-flags "blue" "white" "red" "v")

"Ejercicio 10i"

(place-image (rotate 30 (triangle 85 "solid" "green")) 15 30 (3-bands-flags "red" "white" "black" "h"))