;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname practica6) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Ejercicio 1
; Sin recursión de cola
(define (sumanat x y)
  (cond [(zero? y) x]
        [(positive? y) (add1 (sumanat x (sub1 y)))]
        )
  )

; Con recursión de cola
(define (sumanat-tail x y)
  (cond [(zero? y) x]
        [(positive? y) (sumanat-tail (add1 x) (sub1 y))]
        )
  )

; Un problema recursivo puede ser resuelto con o sin recursión de cola.
;   Sin recursión de cola todas las llamadas recursivas en la pila de recursión
; deben ser almacenadas pues son necesarias para la resolución de la llamada anterior
; Por ejemplo para sumanat:

; (sumanat 2 3) = (add1 (sumanat 2 2)) = (add1 (add1 (sumanat 2 1))) =
; = (add1 (add1 (add1 (sumanat 2 0)))) = (add1 (add1 (add1 2)))

; (sumanat 2 0) debe ser almacenado para calcular (sumanat 2 1) que a su vez debe ser almacenado
; para recordar (sumanat 2 2) que debe ser recordado para finalmente calcular (sumanat de 2 3)
; Por lo tanto en la pila de recursión fue necesario haber almacenado n valores siendo n
; el tamaño del problema recursivo a resolver en este caso. Si la recursión es muy profunda, es decir
; que ocurren muchas llamadas recursivas, puede ocurrir un desbordamiento de pila (stack overflow)
; debido a la falta de memoria para almacenar todas las llamadas.

;  Con recursión de cola la última operación que se realiza es la llamada recursiva, es decir
; que no necesitamos almacenar los valores anteriores porque la solución está en la llamada recursiva en sí.
; Esto se logra almacenando la solución en la misma llamada recursiva. Pongamos como ejemplo sumanat-tail:
; (sumanat-tail 2 3) = (sumanat-tail 3 2) = (sumanat-tail 4 1) = (sumanat-tail 5 0) = 5
; No solo la ejecución paso a paso es más elegante sino que además se almacena el resultado
; en uno de los parámetros de la función, usualmente en el último, por eso es llamado recursión de cola (tail-recursion)
; Por lo tanto, cuando la función llegue al caso base no hará más que retornar el parámetro
; donde se fue acumulando el resultado.
; Esto tiene como positivo que ocupa menos espacio en la pila de recursión y al momento de compilación
; pueden ser optimizados.

; Además una función con recursión de cola al no tener que acceder a las llamadas
; anteriores y al ser optimizada en el tiempo de compilación resulta mucho más veloz
; que la misma función sin recursión de cola.
; Comparemos ambos tipos de funciones usando la función time que nos retorna
; el tiempo de ejecución de la llamada de una función.

; sumanat y sumanat-tail:

; Entrada 1: 1 10^7
; sumanat: (time (sumanat 1 10000000)) --> The program ran out of memory.
; sumanat-tail: (time (sumanat-tail 1 10000000)) --> cpu time: 1087 real time: 1088 gc time: 146

; Como vemos, sumanat consume demasiada memoria para siquiera calcular la suma entre 1 y 10^7.
; Por otro lado sumanat-tail lo calcula sin problemas.

; Entrada 2: 1 10^6
; sumanat: (time (sumanat 1 1000000)) --> cpu time: 365 real time: 367 gc time: 243
; sumanat-tail: (time (sumanat-tail 1 1000000)) --> cpu time: 116 real time: 116 gc time: 21

; Comparando los "cpu time" de ambas llamadas, observamos como sumanat-tail es 3 veces más rápido
; que sumanat

; mult-nat y multnat-tail

; (time (multnat 9 1000000)) --> cpu time: 1671 real time: 1671 gc time: 642
; (time (multnat-semi 9 1000000)) --> cpu time: 1575 real time: 1575 gc time: 602
; (time (multnat-tail 9 1000000)) --> cpu time: 1123 real time: 1123 gc time: 157

; (time (multnat 9 10000000)) --> The program ran out of memory.
; (time (multnat-semi 9 10000000)) --> The program ran out of memory.
; (time (multnat-tail 9 10000000)) --> cpu time: 11461 real time: 11461 gc time: 1445


; Ejercicio 2
; Sin nada de recursión de cola
(define (multnat x y)
  (cond [(zero? y) 0]                            ; x * 0 = 0
        [(and (positive? y) (zero? (sub1 y))) x] ; x * 1 = x
        [else (sumanat (multnat x (sub1 y)) x)]  ; x * y = x + x * (y-1)
        )
  )

; Con algo de recursión de cola (en la suma)
(define (multnat-semi x y)
  (cond [(zero? y) 0]                            
        [(and (positive? y) (zero? (sub1 y))) x] 
        [else (sumanat-tail (multnat-semi x (sub1 y)) x)]  
        )
  )

; Con recursión de cola
(define (multnat-tail x y)
  (local (
          (define (aux x y acc)
            (cond [(zero? y) 0]                            
                  [(and (positive? y) (zero? (sub1 y))) (sumanat-tail acc x)] 
                  [else (aux x (sub1 y) (sumanat-tail acc x))]
                  )
            )
          )
    ;IN
    (aux x y 0)
    )
  )





