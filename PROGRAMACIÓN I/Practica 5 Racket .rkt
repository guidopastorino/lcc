;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |Practica 5 Racket |) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
; PRÁCTICA 5 - Primera Parte

; LISTAS:

; - Lista de un elemento:
;(cons "name" '())
; - lista de más de un elemento:
#|
(cons 1
      (cons 2
            (cons 3
                  (cons 4
                        (cons 5 '())))))
|#
; '() representa una lista vacía
;(list? '()) ; true
;(list "name")


; - Abreviación de escritura:
; Para hacer una lista con muchos elementos, podemos usar "list":
;(list "name" 1 4 7 true "user")
; Para hacer una lista vacía, usamos "empty":
;(list empty)


; ----- EJERCICIOS -----
; 1)
#|
(cons "contacto 1"
      (cons "contacto 2"
            (cons "contacto 3"
                  (cons "contacto 4"
                        (cons "contacto 5" '())))))
|#


; ----- Programando con listas -----


; 5)
; contains-el? : list -> boolean
; contains-el? busca en una lista si contiene un elemento (en este caso, lo representamos como un String) o no y nos devuelve un booleano.
(define (contiene? list el)
  (cond
    [(empty? list) false]
    [(string=? (first list) el) true]
    [else (contiene? (rest list) el)]))

;(contiene? (list "Guido" 1 2 4) "Guido") ; true



; 8)

(define lista (list 1 12 3 4 4))

; pos? : list -> boolean
; pos? recibe una lista y devuelve true si todos sus elementos son pares, sino devuelve false

(define (pos? l)
  (if (= (length (filter even? l)) (length l))
      true
      false
      )
  )

(pos? lista)

; 9)
(define listaBool (list #true #true #true #false))


; todos-verdaderos : List -> Boolean
(define (todos-verdaderos l)
  (cond
    [(empty? l) false]
    [(list? l) (= (length (filter false? l)) 0)]
   )
  )

;(todos-verdaderos (list true true true true))


; uno-verdadero : List -> Boolean
(define (uno-verdadero l)
  (cond
    [(empty? l) false]
    [(list? l) (if (and (car l) true)
                   true
                   (uno-verdadero (cdr l))
                   )]
   )
  )

;(uno-verdadero (list false false true))



; 10)
(define (cant-elementos l)
  (length l))

;(cant-elementos lista)


; 11)

(define (promedio l)
  (cond
    [(null? l) 0]
    [else (/ (+ (first l) (promedio (cdr l))) (length l))]
    )
  )

;(promedio (list 2 6))



; ----- Clasificando elementos de una lista -----


; 12)
(define (pares l)
  (filter even? l)
  )

;(pares lista)



; 13)
(define (cortas l)
  (cond
    [(null? l) '()]
    [(list? l) (if (< (string-length (car l)) 5)
         (cons (car l) (cortas (cdr l)))
         (cortas (cdr l))
         )]
    [else "Tipo de elemento no válido como lista"]
    )
  )

; (cortas (list "Esto" "es" "un" "ejemplo" "con" "listas"))



; 14)
; mayores : List Number -> List
(define (mayores l n)
  (cond
    [(empty? l) '()]
    [(list? l) (if (> (car l) n)
                   (cons (car l) (mayores (cdr l) n))
                   (mayores (cdr l) n)
                   )]
    [else "Tipo de elemento no válido como lista"]
   )
  )

; (mayores (list 1 2 3 4 5 6 5) 4)




; 15)
; constante de distancia máxima
(define MAX (make-posn 5 5))

; cerca : List -> List
(define (cerca l)
  (cond
    [(empty? l) '()]
    [(list? l) (if (and (>= (posn-x (car l)) (posn-x MAX)) (>= (posn-y (car l)) (posn-y MAX)))
                   (cons (car l) (cerca (cdr l)))
                   (cerca (cdr l))
                   )]
   )
  )


;(cerca (list (make-posn 3 5) (make-posn 1 2) (make-posn 0 1) (make-posn 5 6)))
; (list (make-posn 1 2) (make-posn 0 1))




; 16)
; positivos : List -> List
(define (positivos l)
  (cond
    [(null? l) '()]
    [(list? l) (if (> (car l) 0)
                   (cons (car l) (positivos (cdr l)))
                   (positivos (cdr l))
                   )]
    [else "Tipo de elemento no válido como lista"]
   )
  )


; (positivos (list -5 37 -23 0 12))



; 17)
(define (eliminar l n)
  (cond
    [(null? l) '()]
    [(list? l) (if (= (car l) n)
                   (eliminar (cdr l) n)
                   (cons (car l) (eliminar (cdr l) n))
                   )]
    [else "Tipo de elemento no válido como lista"]
   )
  )


; (eliminar (list 1 2 3 2 7 6) 2)



; ----- Aplicando transformaciones a cada elemento de una lista -----
; 18)
(define (raices l)
  (cond
    [(null? l) '()]
    [(list? l) (cons (sqrt (car l)) (raices (cdr l)))]
    [else "Tipo de elemento no válido como lista"]
   ))

;(raices (list 9 16 4))




; 19)
; distancias : List -> List
(define (distancias l)
  (cond
    [(null? l) '()]
    [(list? l) (cons (sqrt (+ (sqr (posn-x (car l))) (sqr (posn-y (car l)))))  (distancias (cdr l)) )]
   )
  )

;(distancias (list (make-posn 3 4) (make-posn 0 4) (make-posn 12 5)))





; 20)
(define (anchos l)
  (cond
    [(null? l) '()]
    [(list? l) (cons (image-width (car l)) (anchos (cdr l)))]
    [else "Tipo de elemento no válido como lista"]
    )
  )

;(anchos (list (circle 30 "solid" "red") (rectangle 10 30 "outline" "blue")))





; 21)
; función sgn2 (definida en la Práctica 1, segunda parte.)
(define (sgn2 x) (cond [(< x 0) -1]
                       [(= x 0) 0]
                       [(> x 0) 1]))

; signos : List -> List
(define (signos l)
  (cond
    [(null? l) '()]
    [(list? l) (cons (sgn2 (car l)) (signos (cdr l)))]
    )
  )

; (signos (list 45 32 -23 0 12))






; 22)
(define (cuadrados l)
  (cond
    [(null? l) '()]
    [(list? l) (cons (sqr (car l)) (cuadrados (cdr l)))]
    [else "Tipo de elemento no válido como lista"]
  ))

;(cuadrados (list 1 2 3))



; 23)
(define (longitudes l)
  (cond
    [(null? l) '()]
    [(list? l) (cons (string-length (car l)) (longitudes (cdr l)))]
    [else "Tipo de elemento no válido como lista"]
    )
)


; (longitudes (list "hola" "cómo" "estás?"))






; 24)
(define (convertirFC l)
  (cond
    [(null? l) '()]
    [(list? l) (cons (* (- (car l) 32) (/ 5 9)) (convertirFC (cdr l)))]
    [else "Tipo de elemento no válido como lista"]
  )
)

; (convertirFC (list 1 2 100))




; ----- Operando con los elementos de una lista -----
; 25)
(define (prod l)
  (cond
    [(null? l) 1]
    [(list? l) (* (car l) (prod (cdr l)))]
    [else "Tipo de elemento no válido como lista"]
  )
)

;(prod (list 1 2 3 4 5))



; 26)
(define (pegar l)
  (cond
    [(empty? l) ""]
    [(list? l) (string-append (car l) (pegar (cdr l)))]
    [else "Tipo de elemento no válido como lista"]
    )
  )

;(pegar (list "Las " "lis" "tas " "son " "complicadas" "."))


; 27)
(define (maximo l)
  (cond
    [(null? l) 0]
    [(list? l) (if (> (car l) (maximo (cdr l)))
                   (car l)
                   (maximo (cdr l))
                   )]
    [else "Tipo de elemento no válido como lista"]
  )
)


; (maximo (list 23 543 325 0 75))



; 28)
; sumdist : List -> Number
(define (sumdist l)
  (cond
    [(null? l) '()]
    [(list? l) (foldl + 0 (cons (sqrt (+ (sqr (posn-x (car l))) (sqr (posn-y (car l)))))  (distancias (cdr l)) ))]
   )
  )

; (sumdist (list (make-posn 3 4) (make-posn 0 4) (make-posn 12 5)))






; 29)
(define (sumcuad l)
  (cond
    [(null? l) 0]
    [(list? l) (+ (sqr (car l)) (sumcuad (cdr l)))]
    [else "Tipo de elemento no válido como lista"]
    ))

;(sumcuad (list 1 2 3))