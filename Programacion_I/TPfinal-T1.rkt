;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname TPfinal-T1) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
#| Trabajo Práctico Final - Tema 1

Integrantes:
- [Bramucci, Franco]
- [Marsilio, Franco]
|#

;;;;;;;; Ejercicio 1

; Recibe dos valores booleanos y devuelve el resultado de aplicar
; el operador implica a dichos valores.
; implica :: Boolean Boolean -> Boolean
; Entrada: #t #f. Salida: #f
; Entrada: #f #t. Salida: #t
(define (implica p q) (or (not p) q) )

(check-expect (implica #t #f) #f)
(check-expect (implica #f #f) #t) 

; Recibe dos valores booleanos y devuelve el resultado de aplicar
; el operador bicondicional a dichos valores.
; equivalente :: Boolean Boolean -> Boolean
; Entrada: #f #f. Salida: #t
; Entrada: #t #f. Salida: #f 
(define (equivalente p q) (and (implica p q) (implica q p)))

(check-expect (equivalente #t #f) #f)
(check-expect (implica #f #f) #t)

;;;;;;;; Ejercicio 2

; Recibe cantidad de valuaciones y cada cuanto deberá alternar el valor de verdad de
; una proposición
; columna :: Nat Nat -> List(Boolean)
; columna genera una columna con todos los valores de verdad que
; tomará una proposición dada una proposición compuesta de n variables proposicionales
; cant es 2^n que será la cantidad de valores que tomara la proposición
; m será cada cuantos valores cambia el valor de la preposición en las valuaciones
; para n=3 la primera columna se obtendrá con (columna 8 4), es decir que la variable tomará
; 8 valores que irán alternando cada 4 valuaciones, es decir que los 4 primeros serán false
; y los 4 últimos serán true
; Entrada: 4 2. Salida: (list #f #f #t #t)
; Entrada: 4 1. Salida; (list #f #t #f #t)
(define (columna cant m)
  (local (
          (define (aux c v)
            (cond [(zero? c) empty]
                  [(not (= 0 (modulo c m))) (cons v (aux (sub1 c) v))]
                  [else (cons (not v) (aux (sub1 c) (not v)))]
                  )
            )
          )
    ;IN
    (aux cant #t)
    )
)

(check-expect (columna 4 2) (list #f #f #t #t))
(check-expect (columna 4 1) (list #f #t #f #t))

; Dada la cantidad de valuaciones se obtiene una lista de listas 
; donde cada sublista contendrá todos los valores que tomarán dichas variables
; en un determinado orden donde el elemento de la enésima posición de cada lista compone
; los valores de la enésima valuación. Es decir que los primeros elementos de las listas
; son los valores de la primera valuación.
; addcolumns :: Int -> List(List(Boolean))
; Entrada: 4. Salida: (list (list #f #f #t #t) (list #f #t #f #t))
(define (addcolumns n)
    (local (
        (define (aux x) 
            (cond 
                [(= 1 x) empty]
                [else (cons (columna n (/ x 2)) (aux (/ x 2)))]
            )
        )
    )
    (aux n)
    )
)

(check-expect (addcolumns 4) (list (list #f #f #t #t) (list #f #t #f #t)))

; Recibe una lista de listas no vacías y devuelve una lista 
; con los primeros elementos de cada lista
; enfilar :: List(List(Any)) -> List(Any)
; Entrada: (list (list 1 2 3) (list #t #f #t)). Salida: (list 1 #t)
(define (enfilar l)
    (if (not (empty? (first l))) (map first l) empty)
)

(check-expect (enfilar (list (list #f #f #t) (list #t #t #f) (list #t #f #f))) (list #f #t #t))
(check-expect (enfilar (list (list #t #f #t) (list #f #f #f) (list #f #f #f))) (list #t #f #f))

; Recibe una lista de listas "l" con sublistas de largo n, devuelve una lista de listas
; donde cada sublista enésima está compuesta por los enésimos elementos de las sublistas de "l"
; es decir que la sublista 1 que se devuelve estará formada por los primeros elementos de todas las
; sublistas de "l". La sublista 2 con todos los segundos elementos de las sublistas de "l" y así.
; lsupremo :: List(List(Any)) -> List(List(Any))
; Entrada: (list (list "a" 1 9) (list "b" 2 9) (list "c" 3 9))). Salida: (list (list "a" "b" "c") (list 1 2 3) (list 9 9 9))
(define (lsupremo l)
  (cond [(empty? (first l)) empty]
        [else (cons (enfilar l) (lsupremo (map rest l)))]
        )
  )

(check-expect (lsupremo (list (list "a" 1 9) (list "b" 2 9) (list "c" 3 9))) (list (list "a" "b" "c") (list 1 2 3) (list 9 9 9))) 
(check-expect (lsupremo (list (list #t #f #f) (list #f #f #f) (list #t #t #t))) (list (list #true #false #true) (list #false #false #true) (list #false #false #true)))
(check-expect (lsupremo (list (list #t #t #t) (list #f #f #f) (list #f #f #f))) (list (list #true #false #false) (list #true #false #false) (list #true #false #false)))

; Recibe la cantidad de variables proposiciones n y se generan todas las 
; posibles valuaciones para dicho n en forma de lista de listas de Bool
; valuaciones :: Nat -> (List(List(Boolean)))
; Entrada: 2. Salida: (list (list #f #f) (list #f #t) (list #t #f) (list #t #t))
;(define (valuaciones n)
;    (lsupremo (addcolumns (expt 2 n)))
;)

(check-expect (valuaciones 3)
              (list
               (list #false #false #false)
               (list #false #false #true)
               (list #false #true #false)
               (list #false #true #true)
               (list #true #false #false)
               (list #true #false #true)
               (list #true #true #false)
               (list #true #true #true))
              )

; Otra forma mucho más acotada de hacer la función valuaciones
(define (valuaciones n)
  (local (
          (define (aux x acc)
            (cond [(zero? x) acc]
                  [else (append (aux (sub1 x) (cons #f acc)) (aux (sub1 x) (cons #t acc)))]
                  )
            )
          
          (define (parser l m acc)
            (cond [(empty? l) (list acc)]
                  [(zero? m) (cons acc (parser l n empty))]
                  [else (parser (rest l) (sub1 m) (cons (first l) acc))]
                  )
            )
          )
    ;IN
    (parser (aux n empty) n empty)
    )
  )


;;;;;;;; Ejercicio 3

; Recibe una lista de 3 booleanos, devuelve un booleano.
; A : List(Boolean) -> Boolean
; Entrada: (list #t #f #f). Salida #t
(define (A l)
    (let ([p1 (first l)]
          [p2 (second l)]
          [p3 (third l)])
    (equivalente (and (implica p1 p3) (implica p2 p3)) (implica (or p1 p2) p3))
    )
)

(check-expect (A (list #t #f #f)) #t)
(check-expect (A (list #f #f #f)) #t)

; Recibe una lista de 3 booleanos, devuelve un booleano.
; B :: List(Boolean) -> Boolean
; Entrada: (list #t #f #t) Salida: #t
; Entrada: (list #t #f #f) Salida: #f
(define (B l)
    (let ([p1 (first l )]
          [p2 (second l)]
          [p3 (third l)])
    (equivalente (implica (and p1 p2) p3) (and (implica p1 p3) (implica p2 p3)))
    )
)

(check-expect (B (list #t #f #t)) #t)
(check-expect (B (list #t #f #f)) #f)

; Recibe una lista de 2 booleanos, devuelve un booleano.
; C :: List(Boolean) -> Boolean
; Entrada: (list #t #f #t) Salida: #f
; Entrada: (list #f #t #f) Salida: #f
(define (C l)
     (let ([p1 (first l )]
           [p2 (second l)])
        (equivalente (or (not p1) (not p2)) (and p1 p2))
    ) 
)

(check-expect (C (list #t #f)) #f)
(check-expect (C (list #t #f)) #f)

;;;;;;;; Ejercicio 4

; Toma una proposición y la cantidad de variables de la misma, retorna
; el resultado de evaluar dicha proposición en todas las posibles valuaciones
; evaluar :: (List(Boolean) -> Boolean) Nat -> List(Boolean)
; Entrada:  (lambda (l) (not(first l))) 1. Salida (list #t #f)
; Entrada: (lambda (l) (and (first l) (second l))) 2. Salida: (list #false #false #false #true)
(define (evaluar P n)
    (let ([casos (valuaciones n)])
        (map P casos)
    )    
)

(check-expect (evaluar (lambda (l) (not(first l))) 1) (list #t #f))
(check-expect (evaluar (lambda (l) (and (first l) (second l))) 2) (list #false #false #false #true))


;;;;;;;; Ejercicio 5

; Recibe una proposición y la cantidad de variables y devuelve si es una tautología o no.
; tautología? :: ((List(Boolean)) -> Boolean) Nat -> Boolean
; Evalua la proposición en todas las posibles valuaciones, si todas las evaluaciones son
; verdad entonces es tautología. En caso contrario, no lo es.
; Entrada: (lambda (l) (and (first l) (second l))) 2. Salida: #f.
; Entrada: (lambda (l) (or (first l) (not (first l)))) 1. Salida: #true.
(define (tautología? P n)
    (foldr (lambda (x y) (and x y)) #t (evaluar P n))
)

(check-expect (tautología? A 3) #t)
(check-expect (tautología? (lambda (l) (and (first l) (second l))) 2) #false)
(check-expect (tautología? (lambda (l) (or (first l) (not (first l)))) 1) #true)


; Recibe una proposición y la cantidad de variables y devuelve si es una contradicción o no.
; contradicción? :: ((List(Boolean)) -> Boolean) Nat -> Boolean
; Evalua la proposición en todas las posibles valuaciones, si todas las evaluaciones son
; falsas entonces es contradicción. En caso contrario, no lo es.
; Entrada: (lambda (l) (and (first l) (not (first l)))) 1. Salida: #t.
(define (contradicción? P n)
    (not (foldr (lambda (x y) (or x y)) #f (evaluar P n)))
)

(check-expect (contradicción? C 3) #t)
(check-expect (contradicción? (lambda (l) (and (first l) (not (first l)))) 1) #true)
(check-expect (contradicción? (lambda (l) (and (first l) (second l))) 2) #f)


; Recibe una proposición y la cantidad de variables y devuelve si es satisfactible o no
; satisfactible? :: ((List(Boolean)) -> Boolean) Nat -> Boolean
; Evalua la proposición en todas las posibles valuaciones, si existe alguna valuación
; que sea verdad, entonces es satisfactible.
; Entrada: (lambda (l) (and (first l) (second l))) 2. Salida: #t.
(define (satisfactible? P n)
    (foldr (lambda (x y) (or x y)) #f (evaluar P n))
)

(check-expect (satisfactible? B 3) #t)
(check-expect (satisfactible? (lambda (l) (and (first l) (second l))) 2) #t)
(check-expect (satisfactible? (lambda (l) (and (first l) (not (first l)))) 1) #f)

;; Casos de prueba de test.txt

;;;; Ejemplos de fórmulas proposicionales

; D : List(Boolean) -> Boolean
; D representa la fórmula proposicional p
(define
  (D l)
  (first l))

; E : List(Boolean) -> Boolean
; E representa la fórmula proposicional p \/ ~p 
(define
  (E l)
  (let ([p (first l)])
  (or p (not p))))

; F : List(Boolean) -> Boolean
; F representa la fórmula proposicional p /\ ~p 
(define
  (F l)
  (let ([p (first l)])
  (and p (not p))))

; MP : List(Boolean) -> Boolean
; MP representa la fórmula proposicional ((p -> q) /\ p) -> q
; conocida como modus ponens.
(define
  (MP l)
  (let ([p (first l)]
        [q (second l)])
  (implica (and (implica p q) p) q)))

; MT : List(Boolean) -> Boolean
; MT representa la fórmula proposicional ((p -> q) /\ ~q) -> ~p
; conocida como modus tollens.
(define
  (MT l)
  (let ([p (first l)]
        [q (second l)])
  (implica (and (implica p q) (not q)) (not p))))

; DM1 : List(Boolean) -> Boolean
; DM1 representa la fórmula proposicional ~(p \/ q) <-> (~p /\ ~q)
; que constituye una de las leyes de morgan.
(define
  (DM1 l)
  (let ([p (first l)]
        [q (second l)])
  (equivalente (not (or p q))
               (and (not p) (not q)))))

; G : List(Boolean) -> Boolean
; G representa la fórmula proposicional p1 /\ ~ p2 /\ (p1 -> ~p4) /\ (p2 \/ p3) /\ (p3 -> p4)
(define
  (G l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)])
  (and p1
       (not p2)
       (implica p1 (not p4))
       (or p2 p3)
       (implica p3 p4))))

; H : List(Boolean) -> Boolean
; H representa la fórmula proposicional ((p1 \/ p2) -> p3) /\ (~p3 \/ ~p4)
(define
  (H l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)])
  (and (implica (or p1 p2) p3)
       (or (not p3) (not p4)))))

; I : List(Boolean) -> Boolean
; I representa la fórmula proposicional
; ((p1 \/ ~p2) -> (p5 \/ (p1 /\ p3 /\ ~p4))) <-> (~(~p1 \/ ~p3 \/ p4 \/ p5) -> (~p1 \/ ~p2))
(define
  (I l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)]
        [p5 (fifth l)])
  (equivalente
    (implica (or p1 (not p2))
             (or p5 (and p1 p3 (not p4))))
    (implica (not (or (not p1) (not p3) p4 p5))
             (or (not p1) (not p2))))))

;;;; Tests para ejercicio 4

; ocurrencias : List(X) X -> Natural
; Dados una lista l de elementos de tipo X y un elemento v de tipo
; X, devuelve la cantidad de veces que v aparece en l.
(define
  (ocurrencias l v)
  (length (filter (lambda (x) (equal? x v)) l)))

(check-expect (ocurrencias (evaluar A 3) #t) 8)
(check-expect (ocurrencias (evaluar A 3) #f) 0)
(check-expect (ocurrencias (evaluar B 3) #t) 6)
(check-expect (ocurrencias (evaluar B 3) #f) 2)
(check-expect (ocurrencias (evaluar C 2) #t) 0)
(check-expect (ocurrencias (evaluar C 2) #f) 4)
(check-expect (ocurrencias (evaluar D 1) #t) 1)
(check-expect (ocurrencias (evaluar D 1) #f) 1)
(check-expect (ocurrencias (evaluar E 1) #t) 2)
(check-expect (ocurrencias (evaluar E 1) #f) 0)
(check-expect (ocurrencias (evaluar F 1) #t) 0)
(check-expect (ocurrencias (evaluar F 1) #f) 2)
(check-expect (ocurrencias (evaluar MP 2) #t) 4)
(check-expect (ocurrencias (evaluar MP 2) #f) 0)
(check-expect (ocurrencias (evaluar MT 2) #t) 4)
(check-expect (ocurrencias (evaluar MT 2) #f) 0)
(check-expect (ocurrencias (evaluar DM1 2) #t) 4)
(check-expect (ocurrencias (evaluar DM1 2) #f) 0)
(check-expect (ocurrencias (evaluar G 4) #t) 0)
(check-expect (ocurrencias (evaluar G 4) #f) 16)
(check-expect (ocurrencias (evaluar H 4) #t) 6)
(check-expect (ocurrencias (evaluar H 4) #f) 10)
(check-expect (ocurrencias (evaluar I 5) #t) 21)
(check-expect (ocurrencias (evaluar I 5) #f) 11)

;;;; Tests para ejercicio 5

(check-expect (tautología? A 3) #t)
(check-expect (tautología? B 3) #f)
(check-expect (tautología? C 2) #f)
(check-expect (tautología? D 1) #f)
(check-expect (tautología? E 1) #t)
(check-expect (tautología? F 1) #f)
(check-expect (tautología? MP 2) #t)
(check-expect (tautología? MT 2) #t)
(check-expect (tautología? DM1 2) #t)
(check-expect (tautología? G 4) #f)
(check-expect (tautología? H 4) #f)
(check-expect (tautología? I 5) #f)

(check-expect (contradicción? A 3) #f)
(check-expect (contradicción? B 3) #f)
(check-expect (contradicción? C 2) #t)
(check-expect (contradicción? D 1) #f)
(check-expect (contradicción? E 1) #f)
(check-expect (contradicción? F 1) #t)
(check-expect (contradicción? MP 2) #f)
(check-expect (contradicción? MT 2) #f)
(check-expect (contradicción? DM1 2) #f)
(check-expect (contradicción? G 4) #t)
(check-expect (contradicción? H 4) #f)
(check-expect (contradicción? I 5) #f)

(check-expect (satisfactible? A 3) #t)
(check-expect (satisfactible? B 3) #t)
(check-expect (satisfactible? C 2) #f)
(check-expect (satisfactible? D 2) #t)
(check-expect (satisfactible? E 1) #t)
(check-expect (satisfactible? F 1) #f)
(check-expect (satisfactible? MP 2) #t)
(check-expect (satisfactible? MT 2) #t)
(check-expect (satisfactible? DM1 2) #t)
(check-expect (satisfactible? G 4) #f)
(check-expect (satisfactible? H 4) #t)
(check-expect (satisfactible? I 5) #t)










