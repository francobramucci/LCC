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

; * Pila de recursión *
; ╔═════════════╗
; ║ sumanat 2 0 ║
; ╚═════════════╝
;        ↑
; ╔═════════════╗
; ║ sumanat 2 1 ║
; ╚═════════════╝
;        ↑ 
; ╔═════════════╗
; ║ sumanat 2 2 ║
; ╚═════════════╝
;        ↑
; ╔═════════════╗
; ║ sumanat 2 3 ║
; ╚═════════════╝

; Por lo tanto en la pila de recursión fue necesario haber almacenado aproximadamente n valores siendo n
; el tamaño del problema recursivo a resolver en este caso. Si la recursión es muy profunda, es decir
; que ocurren muchas llamadas recursivas, puede ocurrir un desbordamiento de pila (stack overflow)
; debido a la falta de memoria para almacenar todas las llamadas.

;  Con recursión de cola la última operación que se realiza es la llamada recursiva, es decir
; que no necesitamos almacenar los valores anteriores porque la solución está en la llamada recursiva en sí.
; Esto se logra almacenando la solución en la misma llamada recursiva. Pongamos como ejemplo sumanat-tail:
; (sumanat-tail 2 3) = (sumanat-tail 3 2) = (sumanat-tail 4 1) = (sumanat-tail 5 0) = 5
; Vemmos como se almacena el resultado en uno de los parámetros de la función, en este caso
; el primero aunque es más usual hacerlo en el último y es por esto que se llama recursión
; de cola (tail recursion).
; Por lo tanto, cuando la función llegue al caso base no hará más que retornar el parámetro
; donde se fue acumulando el resultado.
; Esto tiene como positivo que ocupa menos espacio en la pila de recursión y al momento de compilación
; pueden ser optimizados.

; Además una función con recursión de cola al no tener que acceder a las llamadas
; anteriores y al ser optimizada en el tiempo de compilación resulta mucho más veloz
; que la misma función sin recursión de cola.
; Comparemos ambos tipos de funciones usando la función time que nos retorna
; el tiempo de ejecución de la llamada de una función. (Con 256MB de memoria)

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

; Ejercicio 3

; Sin recursión de cola
(define (powernat x y)
  (cond [(zero? x) 0]
        [(zero? y) 1]
        [else (multnat (powernat x (sub1  y)) x)]
        )
  )

; Con recursión de cola
(define (powernat-tail x y)
  (local(
         (define (aux x y acc)
           (cond [(zero? x) 0]
                 [(zero? y) acc]
                 [else (aux x (sub1  y) (multnat-tail acc x))]
                 )
           )
          )
    ;IN
    (aux x y 1)
    )
  )

; Comparación:

; (time (powernat-tail 3 14)) --> cpu time: 606 real time: 606 gc time: 71
; (time (powernat 3 14)) --> cpu time: 2431 real time: 2431 gc time: 1890

; curry :: posn -> (Nat -> Nat)
; curry recibe un posn del tipo (Nat, Nat) y una función f
; y devuelve la llamada a la función f con las componentes del posn
; como paŕametros.
(define (curry p f)
  (f (posn-x p) (posn-y p))
  )

; createtc :: Nat -> List(posn)
; Crea una lista de posn que servirán como casos de prueba para alltime
; Dado un n devuelve el producto cartesiano {1..n} x {1..n}
(define (createtc n)
  (local (
          (define (aux x y)
            (cond [(zero? x) empty]
                  [(zero? y) (aux (sub1 x) n)]
                  [else (cons (make-posn x y) (aux x (sub1 y)))]
                  )
            )
          )
    (aux n n)
    )
  )

; alltime :: (Nat -> Nat) -> List(posn)
; aplica la funcion f a todos los elementos de una lista de posn's
; y calcula su tiempo de ejecución. El foldr es para reducir el tamaño
; del texto impreso en pantalla.
(define (alltime f tc)
  (time (foldr + 0 (map (lambda (p) (curry p f)) tc)))
  )

; (define (alltime f tc)
;   (cond [(empty? tc) 0]
;         [else (+ (curry (first tc) f) (alltime f (rest tc)))]
;         )
;   )


; (alltime powernat-tail (createtc 8)) --> cpu time: 3277 real time: 3278 gc time: 616
; (alltime powernat (createtc 8)) --> cpu time: 11968 real time: 11969 gc time: 9114

; (alltime sumanat (createtc 500)) --> cpu time: 6847 real time: 6861 gc time: 660
; (alltime sumanat-tail (createtc 500)) --> cpu time: 6185 real time: 6186 gc time: 543

; Ejercicio 4

; Sin recursión de cola (Nat)
(define (factnat n)
  (cond [(zero? n) 1]
        [else (multnat (factnat (sub1 n)) n)]
        )
  )

; Con recursión de cola (Nat)
(define (factnat-tail n)
  (local (
          (define (aux x acc)
            (cond [(zero? x) acc]
                  [else (aux (sub1 x) (multnat-tail acc x))]
                  )
            )
          )
    (aux n 1)
    )
  )

; Definición de fact para Int sin recursión de cola
(define (fact n)
  (cond [(= n 0) 1]
        [else (* n (fact (- n 1)))]
        )
  )

; Definición de fact para Int con recursión de cola
(define (fact-tail n)
  (local (
          (define (aux x acc)
            (cond [(= x 0) acc]
                  [else (aux (- x 1) (* acc x))]
                  )
            )
          )
    ;IN
    (aux n 1)
    )
  )

; Comparacion:
; (time (> 9 (fact-tail 100000))) --> cpu time: 5277 real time: 5277 gc time: 555
; (time (> 9 (fact 100000))) --> cpu time: 8111 real time: 8112 gc time: 165

; Ejercicio 5

; Sin recursión de cola
(define (fibnat n)
  (cond [(zero? n) 0]
        [(and (positive? n) (zero? (sub1 n))) 1]
        [else (sumanat (fibnat (sub1 n)) (fibnat (sub1 (sub1 n))))]
        )
  )

; Con recursión de cola
(define (fibnat-tail n)
  (local (
          (define (aux x a b)
            (cond [(zero? x) a]
                  [(and (positive? x) (zero? (sub1 x))) b]
                  [else (aux (sub1 x) b (sumanat-tail a b))]
                  )
            )
          )
    (aux n 0 1)
    )
  )

; Ejercicio 6

(define (sigma n f)
  (cond [(zero? n) (f 0)]
        [else (+ (f n) (sigma (sub1 n) f))]
        )
  )

; Ejercicio 7

; R :: Nat -> Number
(define (R n)
  (local (
          (define (aux i)
            (/ 1 (expt 2 i))
            )
          )
    ;IN
    (sigma n aux)
    )
  )

; S :: Nat -> Number
(define (S n)
  (local (
          (define (aux i)
            (/ i (+ i 1))
            )
          )
    ;IN
    (sigma n aux)
    )
  )

; T :: Nat -> Number
(define (T n)
  (local (
          (define (aux i)
            (/ 1 (+ i 1))
            )
          )
    ;IN
    (sigma n aux)
    )
  )

; Ejercicio 8

; componer :: (Number -> Number) Nat Number -> Number
(define (componer f n x)
  (cond [(zero? n) x]
        [else (componer f (sub1 n) (f x))]
        )
  )

(check-expect (componer sqr 2 5) 625)
(check-expect (componer add1 5 13) 18)

; Ejercicio 9

(define (intervalo n)
  (cond [(zero? n) (list 0)]
        [else (cons n (intervalo (sub1 n)))]
        )
  )

; Ejercicio 10

; multiplos :: Nat Nat -> List(Nat)
(define (multiplos n m)
  (cond [(zero? n) empty]
        [else (cons (multnat-tail n m) (multiplos (sub1 n) m))]
        )
  )

(check-expect (multiplos 4 7) (list 28 21 14 7))
(check-expect (multiplos 0 11) empty)

; Ejercicio 11

(define (list-fibonacci-map n)
  (map fibnat-tail (intervalo (add1 n)))
  )

(check-expect (list-fibonacci-map 4) (list 5 3 2 1 1 0))
(check-expect (list-fibonacci-map 0) (list 1 0))

(define (list-fibonacci-rec n)
  (local (
          (define (aux x)
            (cond [(zero? x) (list 0)]
                  [else (cons (fibnat-tail x) (aux (sub1 x)))]
                  )
            )
          )
    (aux (add1 n))
    )
  )

; Ejercicio 12
; cuotas :: Number Nat Number -> List(Number)
(define (cuotas m n i)
  (local (
          (define (aux x acc)
            (cond [(zero? x) acc]
                  [else (aux (sub1 x) (cons (+ (/ m n) (* (/ m n) (/ i 1200) x)) acc))]
                  )
            )
          )
    ;IN
    (aux n empty)
    )
  )

(check-expect (cuotas 10000 0 18) empty)
(check-expect (cuotas 10000 1 12) (list 10100))
(check-expect (cuotas 30000 3 12) (list 10100 10200 10300))
(check-expect (cuotas 100000 4 18) (list 25375 25750 26125 26500))

; Ejercicio 13
(define (circulos m)
  (local (
          (define (aux n)
            (cond [(zero? n) (empty-scene (* 2 (sqr m)) (* 2 (sqr m)) "white")]
                  [else (place-image (circle (sqr n) "outline" "blue") (sqr m) (sqr m) (aux (sub1 n)))]
                  )
            )
          )
    ;IN
    (aux m)
    )
  )

; Ejercicio 14

(define (cuadrados m ang)
  (cond [(zero? m) (empty-scene 200 200 "white")]
        [else (place-image (rotate ang (square (sqr m) "outline" "blue")) 100 100 (cuadrados (sub1 m) (+ ang 20)))]
        )
  )

; Ejercicio 15

(define (list-insert l e x)
  (cond [(empty? l) (list e)]
        [(zero? x) (cons e l)]
        [else (cons (first l) (list-insert (rest l) e (sub1 x)))]
        )
  )

(check-expect (list-insert (list 5 9 10 -2) 8 0) (list 8 5 9 10 -2))
(check-expect (list-insert (list 5 9 10 -2) 8 2) (list 5 9 8 10 -2))
(check-expect (list-insert (list 5 9 10 -2) 8 4) (list 5 9 10 -2 8))
(check-expect (list-insert empty 8 3) (list 8))

; Ejercicio 16

(define (tomar l n)
  (cond [(empty? l) empty]
        [(zero? n) empty]
        [else (cons (first l) (tomar (rest l) (sub1 n)))]
        )
  )

(check-expect (tomar (list 5 2 1 9) 0) empty)
(check-expect (tomar (list 5 2 1 9) 2) (list 5 2))
(check-expect (tomar (list 5 2 1 9) 4) (list 5 2 1 9))
(check-expect (tomar (list 5 2 1 9) 7) (list 5 2 1 9))

; Ejercicio 17

(define (eliminar-n l e n)
  (cond [(empty? l) empty]
        [(zero? n) l]
        [else (if (equal? e (first l)) (eliminar-n (rest l) e (sub1 n)) (cons (first l) (eliminar-n (rest l) e n)) )]
        )
  )

(check-expect (eliminar-n (list 1 2 1 1 1 2 1) 1 3) (list 2 1 2 1))
(check-expect (eliminar-n (list 1 2 2 1 2) 1 3) (list 2 2 2))

; Ejercicio 18

(define (member-n l x n)
  (cond [(and (empty? l) (zero? n)) #t]
        [(empty? l) #f]
        [else (if (equal? x (first l)) (member-n (rest l) x (sub1 n)) (member-n (rest l) x n) )]
        )
  )

(check-expect (member-n (list 1 2 1 1 1 2 1) 1 5) #t)
(check-expect (member-n (list 1 2 2 1 2) 1 3) #f)
(check-expect (member-n (list 2 1 2 1 2 2) 2 3) #f)





