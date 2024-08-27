;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname ExamenFrancoBramucci) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; 02/05/24 

; Ejercicio 1
; Representamos a los meses como un número n
; años : Number -> String
; Nuestra función recibirá una cantidad de meses n y devolveremos
; su equivalente en años y meses como una cadena de la forma
; "x años y meses" siendo "x" la cantidad de años y "y" los meses
; Entrada: 12, Salida: "1 años 0 meses"
; Entrada 25, Salida: "2 años 1 meses"

(define (años n)
  (string-append (number->string (quotient n 12)) " años " (number->string (modulo n 12)) " meses")
  )

(check-expect (años 95) "7 años 11 meses")
(check-expect (años 25) "2 años 1 meses")
(check-expect (años 12) "1 años 0 meses")

; Ejercicio 2
; DISEÑO DE DATOS: ESTADO
; El estado representa la cantidad de meses que van pasando
; según el evento que ocurre
; Estado es del tipo Number
 
; DEFINICIÓN DE CONSTANTES
(define ALTO 500)
(define ANCHO 500)
(define FONDO (empty-scene ANCHO ALTO)) ; escena vacía
 
; Estado inicial
(define INICIAL 0)
 
; ——— Función asociada a la cláusula to-draw de la expresión big-bang
; El estado s es la cantidad de meses que recibimos
; draw : Estado -> Image
; Recibimos la cantidad de meses y devolvemos una imagen
; con una cadena que convierte esta cantidad de meses a
; años y meses.

(define (draw s)
  (place-image (text (años s) 24 "indigo") (/ ANCHO 2) (/ ALTO 2) FONDO)
  )
 
; ——— Función asociada a la cláusula on-key
; S es el estado y k es la tecla ingresada desde el entorno
; key-driver : Estado String -> Estado
; Recibo el estado y una tecla. Si la tecla es la flecha izquierda
; reduzco 1 año (12 meses) mi estado. Si por otro lado la tecla es
; la flecha derecha aumento en 1 año (12 meses) al estado.
; Ejemplo: presiono "right" y aumento en el estado de 0 a 12.
; Ejemplo: presiono "left" y reduzco el estado de 13 a 1.
(define (key-driver s k)
  (cond [(string=? k "right") (+ s 12)]
        [(string=? k "left") (if (>= (- s 12) 0) (- s 12) 0)]
        [else s]
        )
  )

(check-expect (key-driver 0 "right") 12)
(check-expect (key-driver 13 "left") 1)
(check-expect (key-driver 7 "left") 0)
 
; ————— Función asociada al mouse
; S es el estado, "x" es la coordenada horizontal de la posición del cursor
; "y" es la coordenada vertical de la posición del cursor (cuando ocurrió el evento)
; "e" es el tipo de evento
; mouse-driver : Estado Number Number String -> Estado
; Recibimos el evento del mouse. En caso de que este sea un click
; aumentamos nuestro estado en 1 mes. Si es otro estado no hacemos nada.
; Ejemplo: hago click y aumento el estado de 45 a 46.
(define (mouse-driver s x y e)
  (if (string=? e "button-down") (+ s 1) s)
  )

(check-expect (mouse-driver 0 12 23 "button-down") 1)
(check-expect (mouse-driver 45 12 23 "button-down") 46)
(check-expect (mouse-driver 78 12 23 "move") 78)
 
 
; — Expresión big-bang —
(big-bang INICIAL
  [to-draw draw]
  [on-key key-driver]
  [on-mouse mouse-driver]
  )
