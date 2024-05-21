;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname Practica2) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
; Calculamos la distancia de un punto (x,y) al origen
; distancia-origen: Number Number -> Number
; Recibe la coordenada de un punto, devuelve su distancia al origen
; entrada: 3 4, salida 5
; entrada 0 0, salida 0
(define (distancia-origen x y) (sqrt (+ (sqr x) (sqr y) )))
(distancia-origen 3 4)
(check-expect (distancia-origen 3 4) 5)
(check-expect (distancia-origen 0 0) 0)

; Calculamos la distancia entre dos puntos
; distancia-puntos Number Number Number Number -> Number
; Recibe la coordenada de un punto (x1,y1) y la de un punto (x2,y2)
; y devuelve la distancia entre ellos
; entrada: 3 4, salida: 5
; entrada 0 10 0 20, salida: 10
(define (distancia-puntos x1 y1 x2 y2) (sqrt (+ (sqr (- x1 x2)) (sqr (- y1 y2)))))
(distancia-puntos 0 10 0 20)
(check-expect (distancia-puntos 0 10 0 20) 10)

; Calculamos el volumen de un cubo dada su arista
; vol-cubo: Number -> Number
; Recibe la longitud de una arista, devuelve el volumen del cubo
; entrada 5, salida: 125
(define (vol-cubo arista) (* arista arista arista))
(check-expect (vol-cubo 5) 125)

; Calculamos el área de un cubo dada una arista
; area-cubo: Number -> Number
; Recibe la longitud de la arista devuelve el area del cubo
; entrada: 5, salida: 150
(define (area-cubo arista) (* arista arista 6))
(area-cubo 5)
(check-expect (area-cubo 5) 150)

; Insertamos el caracter "-" en la posición (pos) del string
; string-insert: String Number -> String
; Recibimos la cadena y la posición en la que queremos insertar el "-"
; entrada: "bocanada" 4, salida: "boca-nada"
(define (string-insert cadena pos) (string-append (substring cadena 0 pos) "-" (substring cadena pos (string-length cadena))))
(string-insert "bocanada" 4)
(check-expect (string-insert "bocanada" 4) "boca-nada")

; Extraemos el último caracter de una cadena
; string-last: String -> String
; Recibimos la cadena y devolvemos su ultimo caracter
; entrada: "bocanada", salida: 'a'
(define (string-last cadena) (substring cadena (- (string-length cadena) 1) (string-length cadena)))
(string-last "bocanada")
(check-expect (string-last "bocanada") "a")

; Removemos el último caracter de una cadena
; string-remove-last: String -> String
; Recibe una cadena y devuelve la cadena sin el último caracter
; entrada: "bocanada", salida: "bocanad"
(define (string-remove-last cadena) (substring cadena 0 (- (string-length cadena) 1)))
(string-remove-last "bocanada")
(check-expect (string-remove-last "bocanada") "bocanad")

(define dp2 10)
(define dp3 20)
(define dm2 15)
(define dm3 25)
(define cuota 650)
(define maxd 35)

; Calculamos la cantidad de dinero a pagar según las personas a inscribir y la cantidad
; de meses a pagar
(define (monto-persona cper cmes)
  (* cmes (- cuota
       (* cuota 0.01 (min maxd
       (cond [(and (= cper 2) (= cmes 2)) (+ dp2 dm2)]
             [(and (= cper 2) (> cmes 2)) (+ dp2 dm3)]
             [(and (> cper 2) (= cmes 2)) (+ dp3 dm2)]
             [(and (> cper 2) (> cmes 2)) (+ dp3 dm3)]
             [else 0]
             )
       )
     )
     )
     )
)

(monto-persona 2 2)

(define h1 13)
(define h2 10)
(define h3 11)
(define h4 11.5)
(define h5 12.6)
(define h6 13)

(define (anemia e h)
  (cond [(<= e 1) (< h h1)]
        [(and (> e 1) (<= e 6)) (< h h2)]
        [(and (> e 6) (<= e 12)) (< h h3)]
        [(and (> e 12) (<= e 60)) (< h h4)]
        [(and (> e 60) (<= e 120)) (< h h5)]
        [(> e 120) (< h h6)]
         )
)

(anemia 50 11.4)

; Ejercicio 11
(define (prom3 a b c) (/ (+ a b c) 3))

(define (ternauto a b c) (if (or (= a (prom3 a b c)) (= b (prom3 a b c)) (= c (prom3 a b c))) (* a b c) (+ a b c)) )
(ternauto 7 5 9)
(ternauto 1 2 123123)

; Ejercicio 12
(define ac 8)
(define ar 11)
(define (autonomia l t)
  (cond [(string=? "super" t) (string-append "Autonomía en ciudad: " (number->string (* l ac)) "km. Autonomía en ruta: " (number->string (* l ar)) "km")]
        [(string=? "premium" t) (string-append "Autonomía en ciudad: " (number->string (* l ac 1.10)) "km. Autonomía en ruta: " (number->string (* l ar 1.10)) "km")]
        [else "Ingresar el tipo de nafta SUPER o PREMIUM"]
  )
 )
(autonomia 20 "premium")










