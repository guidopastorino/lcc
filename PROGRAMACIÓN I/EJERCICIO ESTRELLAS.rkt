;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |EJERCICIO ESTRELLAS|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/image)
(require 2htdp/universe)

(define ANCHO 800)
(define ALTO 500)

(define ESCENA (empty-scene ANCHO ALTO))

(define-struct ESTRELLA [tam col pos])

(define TAMAÑO_ESTRELLA 20)

(define ESTADO_INICIAL (list (make-ESTRELLA TAMAÑO_ESTRELLA "red" (make-posn (/ ANCHO 2) (/ ALTO 2)))))

(define (generar-estrellas l)
  (foldl (lambda (estrella acumulador)
           (place-image
            (star (ESTRELLA-tam estrella) "solid" (ESTRELLA-col estrella))
            (posn-x (ESTRELLA-pos estrella)) (posn-y (ESTRELLA-pos estrella))
            acumulador))
         ESCENA l)
  )


(define (select-color) (list-ref (list "red" "green" "blue") (random 3)))


(define (select-position) (make-posn (- (random ANCHO) 40) (- (random ALTO) 40)))


(define (handle-tick list)
  (cons
   (make-ESTRELLA 20 (select-color) (select-position))
   list
   )
  )



(big-bang ESTADO_INICIAL
  [to-draw generar-estrellas]
  [on-tick handle-tick 1]
  )