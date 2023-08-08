;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |Practica 6|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
; Práctica 6

(define (sumnat a b)
  (if (= b 0)
      a
      (sumnat (add1 a) (sub1 b))
      )
  )

;(sumnat 1 2)


; 2)
(define (multiplicar a b)
  (if (= b 0)
      0
      (sumnat a (multiplicar a (sub1 b)))
      )
  )

;(multiplicar 3 3)


; 3)
(define (powernat base expt)
  (if (= expt 0)
      1
      (multiplicar base (powernat base (sub1 expt)))
      )
  )

; (powernat 3 3)


; 4)
; sigma: Natural (Natural -> Number) -> Number

(define (sigma n f)
  (if (= n 0)
      (f 0)
      (+ (f n) (sigma (sub1 n) f))
      )
  )


; (sigma 10 identity)


; 6)
(define (intervalo n)
  (cond
    [(zero? n) '()]
    [else (append (intervalo (sub1 n)) (list n))]
    )
  )



; (reverse (intervalo 5))


; 7)
(define (factorial n)
  (if (or (= n 1) (= n 0))
      1
      (* n (factorial (sub1 n)))
      )
  )

;(factorial 4)



; 8)
; fib: Number -> Number
(define (fib n)
  (cond
    [(= n 0) 1]
    [(= n 1) 1]
    [else (+ (fib (- n 1)) (fib (- n 2)))]
    )
  )

;(fib 5)



; 9)
; list-fib: Number -> List 
(define (list-fib n)
  (cond
    [(= n 0) (list 1)]
    [(= n 1) (list 1 1)]
    [else (cons (fib n) (list-fib (sub1 n)))]
    )
  )

; (list-fib 1)



; 10)
(define (g n)
  (cond
    [(= n 0) 1]
    [(= n 1) 2]
    [(= n 2) 3]
    [else (* (g (- n 1)) (g (- n 2)) (g (- n 3)))]
    )
  )


(define (list-g n)
  (if (< n 0)
      '()
      (append (list-g (sub1 n)) (list (g n)))
      )
  )


; (list-g 6)



; 11)
(define (componer f n a)
  (cond
    [(zero? n) a]
    [else (componer f (sub1 n) (f a))]
    )
  )

; (componer sqr 2 5)



; 12)
(define (multiplos n m)
  (cond
    [(zero? n) '()]
    [(zero? m) '()]
    [else (cons (* n m) (multiplos (sub1 n) m))]
    )
  )

; (multiplos 4 7)


; 13)
(define (g2 f n)
  (cond
    [(not (zero? n)) (f (sub1 n))]
    [else #f]
    )
  )


;(g2 even? 7)




; 14)
(define (circulos m)
  (cond
    [(zero? m) (empty-scene 200 200)]
    [(positive? m) (place-image
                    (circle (sqr m) "outline" "blue")
                    100 100
                    (circulos (sub1 m))
                    )]
    )
  )


(circulos 10)



; 15)
(define (cuadrados lado ang)
  (rotate ang (square (sqr lado) "outline" "blue"))
  )

(define FONDO (empty-scene 200 200))

(define (cuadrado m ang)
  (cond
    [(zero? m) FONDO]
    [(positive? m) (place-image
                    (cuadrados m ang)
                    100 100
                    (cuadrado (sub1 m) (+ 20 ang)))]
    )
  )

(cuadrado 50 50)


