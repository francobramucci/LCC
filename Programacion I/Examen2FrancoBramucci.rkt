;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname Examen2FrancoBramucci) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
; Ejercicio 1
(define-struct Libro [titulo autor paginas])
; Libro es (String, String, Number)
; donde el 1° elemento representa el título del libro,
; el 2° el autor y el 3° el número de páginas.

; 1

; Representamos libros con la estructua Libro.
; libros-de-autor : List(Libro) -> Number
; dada una lista de libros "l", cuenta la cantidad de libros en la lista
; que tienen como autor "Gabriel Rolón". 
; Entrada (list (make-Libro "El pasar" "Gabriel Rolón" 89)). Salida: 1
(define (libros-de-autor l)
  (cond [(empty? l) 0]
        [else (if (string=? "Gabriel Rolón" (Libro-autor (first l))) (+ 1 (libros-de-autor (rest l))) (libros-de-autor (rest l)))]
        )
  )

(check-expect (libros-de-autor (list (make-Libro "La felicidad" "Gabriel Rolón" 100)
                                     (make-Libro "La casa Neville" "Florencia Bonelli" 200)
                                     (make-Libro "El duelo" "Gabriel Rolón" 200)))
 
              2)
 
 (check-expect (libros-de-autor  '()) 0)

; 2. Definición con patrones

; Representamos el nombre de un libro como la variable x de tipo String
; convertir : String -> Libro
; Se recibe el nombre de un libro y se devuelve un Libro con autor DESCONOCIDO y cantidad de páginas 0
; Entrada: "Ciencia y Arte". Salida (make-Libro "Ciencia y Arte" "DESCONOCIDO" 0)
(define (convertir x)
  (make-Libro x "DESCONOCIDO" 0)
  )

(check-expect (convertir "Ciencia y Arte") (make-Libro "Ciencia y Arte" "DESCONOCIDO" 0))

; Representamos libros con la estructua Libro.
; datos-a-libros : List(String) -> List(Libro)
; Dada una lista de cadenas que representan nombres de libros, devuelve una
; lista de libros con los nombres dados, de autor "DESCONOCIDO" y cantidad de hojas 0.
; Entrada: (list "La ciudad y sus muros inciertos" "Tokio blues")).
; Salida: (list (make-Libro "La ciudad y sus muros inciertos" "DESCONOCIDO" 0) (make-Libro "Tokio blues" "DESCONOCIDO" 0))
(define (datos-a-libros l)
  (map convertir l)
  )
 
(check-expect (datos-a-libros (list "La ciudad y sus muros inciertos"
                                    "Tokio blues"))
              (list (make-Libro "La ciudad y sus muros inciertos" "DESCONOCIDO" 0)
                    (make-Libro "Tokio blues" "DESCONOCIDO" 0)))
 
(check-expect (datos-a-libros '()) '())

; 2. Definición con recursión

; Representamos libros con la estructua Libro.
; datos-a-libros : List(String) -> List(Libro)
; Dada una lista de cadenas que representan nombres de libros, devuelve una
; lista de libros con los nombres dados, de autor "DESCONOCIDO" y cantidad de hojas 0.
; Entrada: "Colorín". Salida (make-Libro "Colorín" DESCONOCIDO 0)

(define (datos-a-libros2 l)
  (cond [(empty? l) empty]
        [else (cons (make-Libro (first l) "DESCONOCIDO" 0) (datos-a-libros2 (rest l)))]
        )
  )

(check-expect (datos-a-libros2 (list "La ciudad y sus muros inciertos"
                                    "Tokio blues"))
              (list (make-Libro "La ciudad y sus muros inciertos" "DESCONOCIDO" 0)
                    (make-Libro "Tokio blues" "DESCONOCIDO" 0)))
 
(check-expect (datos-a-libros2 '()) '())

; 3

; x representa un libro
; autor-leila? : Libro -> Boolean
; Se recibe un libro y se devuelve si su autor es o no "Leila Guerrero"
; Entrada: (make-Libro "Mastropiero que nunca" "Mastropiero" 90). Salida: #f
(define (autor-leila? x)
  (string=? "Leila Guerrero" (Libro-autor x))
  )

(check-expect (autor-leila? (make-Libro "Mastropiero que nunca" "Mastropiero" 90)) #f)

; "x" es un libro y "y" es la suma de las páginas del resto de los libros
; suma-pag : Libro Number -> Number
; Se recibe un libro y se suma su cantidad de hojas a la suma de las páginas de los otros libros.
; Entrada: (make-Libro "Desdén" "Juan" 90) 1000. Salida: 1090
(define (suma-pag x y)
  (+ (Libro-paginas x) y)
  )

(check-expect (suma-pag (make-Libro "Desdén" "Juan" 90) 1000) 1090)

; Representamos libros con la estructua Libro.
; paginas-totales : List(Libro) -> Number
; dada una lista de libros calcula la suma de las páginas de los libros
; de la autora "Leila Guerrero".
(define (paginas-totales l)
  (foldr suma-pag 0 (filter autor-leila? l))
  )

(check-expect (paginas-totales (list (make-Libro "Zona de obras" "Leila Guerrero" 100)
                                     (make-Libro "Los cabellos de la noche" "Daniel Balmaceda" 200)
                                     (make-Libro "La llamada" "Leila Guerrero" 150)))
               250)
 
(check-expect (paginas-totales '()) 0)


; Ejercicio 2

; DISEÑO DE DATOS: ESTADO
; vec es (Number Number Number)
(define-struct vec [y sen time])

; Usaremos como estado un vec:
; vec-y representará la coordenada "y" de la posición de la estrella
; vec-sen representará el sentido del movimiento de la estrella
; vec-time almacenará el tiempo transcurrido

; Estado = vec en este caso.
 
; DEFINICIÓN DE CONSTANTES
(define TAM 500)
(define FONDO (empty-scene TAM TAM))     ; escena vacía
(define IMG (star 40 "solid" "yellow"))  ; estrella
(define DELTA 10)                        ; desplazamiento   
 
; Estado inicial
; Se inicializa la estrella en el medio de la escena con sentido
; hacia abajo (que cambiará hacia arriba por propiedades del módulo) y tiempo 0
(define INICIAL (make-vec (/ TAM 2) 1 0))
 
; ——— Función asociada a la cláusula to-draw de la expresión big-bang
; interpretar: Estado -> Image
; s es nuestro estado que, entre otros datos contiene la posición "y" de nuestra estrella
; Se recibe el estado que contiene la coordenada "y" de la estrella y se dibuja en el FONDO
(define (interpretar s)
  (place-image IMG (/ TAM 2) (vec-y s) FONDO)
  )
 
; ——— Función asociada al on-tick 
; manejar-tiempo: Estado -> Estado
; s es nuestra estructura de tipo vec
; Se recibe un estado, si pasaron 5 segundos, es decir si el módulo entre el tiempo transcurrido (vec-time s)
; y 5 es igual a 0, entonces invertimos el sentido de desplazamiento de nuestra estrella.
; En caso de que todavía no haya una diferencia de 5 segundos, se actualiza la posición "y" con el sentido actual
; , se mantiene dicho sentido y se actualiza el tiempo (En ambos casos)
; Entrada: (make-vec 200 -1 73). Salida: (make-vec (- 200 DELTA) -1 74)
(define (manejar-tiempo s)
  (cond [(= (modulo (vec-time s) 5) 0) (make-vec (+ (vec-y s) (* -1 DELTA (vec-sen s))) (* -1 (vec-sen s)) (+ (vec-time s) 1))]
        [else (make-vec (+ (vec-y s) (* DELTA (vec-sen s))) (vec-sen s) (+ (vec-time s) 1))]
        )
  )

(check-expect (manejar-tiempo (make-vec 200 -1 73)) (make-vec (- 200 DELTA) -1 74))
(check-expect (manejar-tiempo (make-vec 200 -1 70)) (make-vec (+ 200 DELTA) 1 71))
 
; — Expresión big-bang —
(big-bang INICIAL
  [to-draw interpretar]
  [on-tick manejar-tiempo 1]
  )






 