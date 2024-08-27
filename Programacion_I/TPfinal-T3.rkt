;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname TP-T3-Apellido1-Apellido2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; representaremos alfabetos como Strings.
; Por ejemplo, si nuestros símbolos son las cinco primeras letras, los dígitos y el espacio,
; lo representaremos como "ABCDE0123456789 "

; representaremos símbolos como strings de longitud 1. En el alfabeto anterior,
; el símbolo E lo representamos con el string "E"

; el código del césar lo representaremos mediante parejas de símbolos.
; Por ejemplo, si queremos decir que el símbolo "A" se codifica con el
; símbolo "C", tendremos (make-Tupla "A" "C") para representar esta situación.

;;;;;;;; Primero comenzamos definiendo algunas funciones
; sobre strings y listas que nos son de utilidad.

; partir : String -> Listof String
; dado un string, devuele una lista de strings con cada símbolo separado
(check-expect (partir "ABC") (list "A" "B" "C"))
(check-expect (partir "12345") (list "1" "2" "3" "4" "5"))
(check-expect (partir "") empty)

; COMPLETAR

; tomar : (Listof Natural) Natural -> Listof Natural
; dada una lista y un número natural n, devuelve una lista
; con los primeros n elementos de l. Si l no tiene tantos elementos,
; devuelve l.
(check-expect (tomar (list 1 2 3 4 5) 4) (list 1 2 3 4))
(check-expect (tomar (list 1 2 3 4 5) 10) (list 1 2 3 4 5))
(check-expect (tomar (list 1 2 3 4 5) 0) empty)
(check-expect (tomar empty 5) empty)


; COMPLETAR

; tirar : (Listof Natural) Natural -> Listof Natural
; dada una lista y un número natural n, devuelve una lista
;  sin los primeros n elementos de l. Si l no tiene tantos elementos,
; devuelve empty.
(check-expect (tirar (list 1 2 3 4 5) 2) (list 3 4 5))
(check-expect (tirar (list 1 2 3 4 5) 10) empty)
(check-expect (tirar (list 1 2 3 4 5) 0) (list 1 2 3 4 5))
(check-expect (tirar empty 3) empty)

; COMPLETAR

; OBSERVACION: para cualquier n <= length l, (append (tomar n l) (tirar n l)) = l

(define-struct Tupla [f s])
; Tupla es [Any Any]
; que representa un par de elementos de cualquier tipo.  

; emparejar : List (X) List(Y) -> List Tuplas
; dadas dos listas [a0,..., an] y [b0, ...., bn] de la misma longitud, devuelve una lista
; de tuplas con parejas tomadas de ambas listas: [(make-posn a0 b0), ...., (make-posn an bn)]
(check-expect (emparejar (list "a" 2) (list "b" 4)) (list (make-Tupla "a" 3) (make-Tupla "b" 4)))
(check-expect (emparejar (list "h" "l") (list "o" "a")) (list (make-Tupla "h" "o") (make-Tupla "l" "a")))

; COMPLETAR


;;;;;;;;;;;;; Ahora comienzan las funciones específicas para el método del César
; cifrado : N String -> Listof Tupla
; dada una clave de desplazamiento y un alfabeto s, devuelve una lista
; con parejas de strings, donde el primer elemento es el caracter a cifrar, y el segundo
; su código del César de acuerdo a la clave. Se asume que 0 < n < (string-length s)
(check-expect (cifrado 2 "ABC") (list (make-posn "A" "C") (make-posn "B" "A") (make-posn "C" "B"))) 
(check-expect (cifrado 1 "ABC") (list (make-posn "A" "B") (make-posn "B" "C") (make-posn "C" "A")))
; COMPLETAR (las funciones tirar, tomar, partir y emparejar le serán de utilidad.



; encriptar-simbolo : String (Listof Tupla) -> String
; dado un string s de longitud 1 que es un símbolo del
; alfabeto y una lista de parejas que representa un código del césar,
; devuelve el código que le corresponde a s
(check-expect (encriptar-simbolo "A" (cifrado 2 "ABC")) "C")
(check-expect (encriptar-simbolo "A" (cifrado 1 "ABC")) "B")
; COMPLETAR ...  


; encriptar-mensaje : String String Natural -> String
; dado un string, un alfabeto y una clave, devuelve el string encriptado
(check-expect (encriptar-mensaje "ABC" "ABCDEF" 3) "DEF")
(check-expect (encriptar-mensaje "ABC" "ABCDEF" 4) "EFA")
; COMPLETAR ...



; desencriptar-simbolo : String (Listof Tupla) -> String
; dado un string s de longitud 1 que es un símbolo del
; alfabeto y una lista de parejas que representa un código del césar,
; devuelve el caracter desencriptado que le corresponde a s
(check-expect (desencriptar-simbolo "A" (cifrado 2 "ABC")) "B")
(check-expect (desencriptar-simbolo "A" (cifrado 1 "ABC")) "C")
; COMPLETAR ...

; desencriptar-mensaje : String String Natural -> String
; dado un string, un alfabeto y una clave, devuelve el string encriptado
(check-expect (desencriptar-mensaje "DEF" "ABCDEF" 3) "ABC")
(check-expect (desencriptar-mensaje "EFA" "ABCDEF" 4) "ABC")
; COMPLETAR ...

