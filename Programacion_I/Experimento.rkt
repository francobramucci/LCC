;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname Experimento) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
(define (world l) (place-image (circle (list-ref l 0) "solid" (list-ref l 1)) 200 200 (empty-scene 400 400)))
(define (inc-dec l)
  (cond [(= 0 (round (list-ref l 0))) (list (+ 1 (list-ref l 0)) (list-ref l 1) (* -1.1 (list-ref l 2)))]
        [(= 120 (round (list-ref l 0))) (list (- (list-ref l 0) 1) (list-ref l 1) (* -1.1 (list-ref l 2)))]
        [else (list (+ (list-ref l 0) (list-ref l 2)) (list-ref l 1) (list-ref l 2))]
        )
  )
(big-bang (list 100 "blue" -1)
  [to-draw world]
  [on-tick inc-dec]
  )

; evenfirst :: List(Number) -> List(Number)
(define (evenfirst l)
  (local (
          (define (aux e o)
             (cond [(empty? e) o]
                   [else (if (odd? (first e)) (aux (rest e) (cons (first e) o)) (cons (first e) (aux (rest e) o)))]
                   )
            )
          )
    (aux l empty)
    )
  )

