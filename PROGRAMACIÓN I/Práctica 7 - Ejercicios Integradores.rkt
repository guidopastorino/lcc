;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |Práctica 7 - Ejercicios Integradores|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
; Práctica 7 - Ejercicios Integradores

; 1)

(define CARAS 6)

(define (simular-dado n)
  (cond
    ((zero? n) '())
    (else (cons (+ 1 (random n)) (simular-dado (sub1 n))))
    )
  )

; (simular-dado CARAS)



(define (frecuencia n lst)
  (cond
    [(empty? lst) 0]
    [(equal? (first lst) n) (add1 (frecuencia n (rest lst)))]
    [else (frecuencia n (rest lst))]))




; 2)


