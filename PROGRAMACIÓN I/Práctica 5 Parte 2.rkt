;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |Práctica 5 Parte 2|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
; Práctica 5 segunda parte

; 1) Rediseñar todas las funciones usando filter.
; a)
(define (pares l)
  (filter even? l))

(pares (list 1 2 3 4 5 6 7 8 9 10))

; b)
; corta?: List -> Boolean
; corta? es una función que hace un mapeo de una lista y devuelve true al elemento cuya longitud
; es menor que 5 y devuelve false en caso contrario
(define (corta? x)
  (cond
    [(empty? x) empty]
    [else (if (< (string-length x) 5)
                   true
                   false
                   )]))

; cortas: List -> List
(define (cortas l)
  (filter corta? l)
  )


(cortas (list "Lista" "de" "palabras" "sin" "sentido"))


; c)
; distancia máxima:
(define MAX (make-posn 1 2))

; cerca?: List -> Boolean
; x: (make-posn 3 5)
(define (cerca? x)
  (cond
    [(empty? x) '()]
    [else (if (and (<= (posn-x x) (posn-x MAX)) (<= (posn-y x) (posn-y MAX)))
              true
              false
              )]
   )
  )

; cerca : List -> List
(define (cerca l)
  (filter cerca? l)
  )

(cerca (list (make-posn 3 5) (make-posn 1 2) (make-posn 0 1) (make-posn 5 6)))



; d)
(define (positivos l)
  (filter even? l)
  )

(positivos (list 2 3 4 2))

; e)
(define (eliminar l x)
  (remove x l)
  )

(eliminar (list 1 2 3) 3)

; _____________________________

; 6)

(define (equal0? x)
  (cond
    [(empty? x) empty]
    [else (if (= 0 x)
              false
              true
            )]))

(define (eliminar-0 l)
  (filter equal0? l))

(eliminar-0 (list 1 0 0 0 7 6 0))


; 7)

; definimos la funcion auxiliar
(define (equalNum? num x)
  (not (= num x)))


; funcion principal
; eliminar-n: List Number -> List
; eliminar-n recibe una lista y un número y devuelve la lista pero sin todas las ocurrencias del número que le pasamos, es decir, lo elimina por completo.
(define (eliminar-n l n)
  (filter (lambda (x) (equalNum? n x)) l)
  )

(eliminar-n (list 1 0 0 0 7 6 0) 6)


; ---------- MAP ----------
; 8)
(define (raices l)
  (map sqrt l))

(raices (list 9 16 4))


; 9)
; x -> posn
(define (obtener-distancia x)
  (sqrt (+ (sqr (posn-x x)) (sqr (posn-y x))))
  )


(define (distancias l)
  (map obtener-distancia l))


(distancias (list (make-posn 3 4) (make-posn 0 4) (make-posn 12 5)))




; 10)
(define (anchos l)
  (map (lambda (x) (image-width x)) l)
  )

(anchos (list (circle 30 "solid" "red") (rectangle 10 30 "outline" "blue")))





; 11)
; función practica 1 sgn2
(define (sgn2 x) (cond [(< x 0) -1]
                       [(= x 0) 0]
                       [(> x 0) 1]))

(define (signos l)
  (map sgn2 l)
  )

(signos (list 45 32 -23 0 12))





; 12)
(define (cuadrados l)
  (map sqr l))

(cuadrados (list 1 2 3))




; 13)
(define (longitudes l)
  (map (lambda (x) (string-length x)) l)
  )

(longitudes (list "hola" "cómo" "estás?"))




; 14)
; (* (- x 32) (/ 5 9))

(define (convertirFC l)
  (map (lambda (x) (* (- x 32) (/ 5 9))) l)
  )

(convertirFC (list 1 2 4 67 99))



; ---------- FOLDL / FOLDR ----------
; foldl -> acumula un valor de la lista de izquierda a derecha
; ej: (foldr string-append "" (list "Hola " "Guido " "Como " "Estás?")) -> "Estás?Como Guido Hola "

; foldr -> acumula un valor de la lista de derecha a izquierda
; ej: (foldr string-append "" (list "Hola " "Guido " "Como " "Estás?")) -> "Hola Guido Como Estás?"




; 15)
(define (prod l)
  (foldl * 1 l)
  )

(prod (list 1 2 3 4 5))



; 16)
(define (pegar l)
  (foldr string-append "" l)
  )

(pegar (list "Las " "lis" "tas " "son " "complicadas" "."))



; 17)
(define (maxPositive l)
  (foldr (lambda (x acc)
           (if (> x acc) x acc)
           )
         0 l)
  )

(maxPositive (list 23 543 325 0 75))





; ---------- 4. Más ejercicios ----------

; 18)
; sumCuad: List -> List
(define (sumCuad l)
  (cond
    [(empty? l) 0]
    [else (foldr + 0 (map sqr l))]
   )
  )

(sumCuad (list 1 2 3 4))
(sumCuad empty)


; 19)
; sumdist: List(posn) -> Number
(define (sumdist l)
  (foldr + 0 (map (lambda (x)
                    (sqrt (+ (sqr (posn-x x)) (sqr (posn-y x)))))
                  l))
  )

(sumdist (list (make-posn 3 4) (make-posn 0 3)))



; 20)
; multPos: List(Number) -> Number
; multPos filtra desde una lista los numeros positivos y los multiplica entre sí
(define (multPos l)
  (foldr * 1 (filter (lambda (x)
                       (> x 0)
                       ) l))
  )

(multPos (list 3 -2 4 0 1 -5))




; 21)
(define (sumAbs l)
  (foldr + 0 (map abs l))
  )

(sumAbs (list 3 -2 4 0 1 -5))




; 22)
; raicesPos: List -> List
(define (raicesPos l)
  (map sqrt (filter (lambda (x)
                      (>= x 0)
                      )
                    l))
  )

(raicesPos (list 16 -4 9 0))




; 23)
; saa: List -> List

(define (saa l)
  (foldr + 0 (map (lambda (x)
                    (* (image-width x) (image-height x)))
                  (filter (lambda (x)
                       (< (image-height x) (image-width x))
                       ) l))
   )
)

(saa (list (circle 20 "solid" "red")
              (rectangle 40 20 "solid" "blue")
              (rectangle 10 20 "solid" "yellow")
              (rectangle 30 20 "solid" "green")))




; 24)
; any: devuelve true si el predicado al menos se aplica para 1 elemento, caso contrario devuelve false si no hay elementos que cumplan esa condicion
; every: devuelve true si para todos los elementos se cumple esa condicion, caso contrario devuelve false
(define (algun-pos l)
  (not (null? (filter positive? (map (lambda (x)
                                       (foldr + 0 x)) l))))
  )


(algun-pos (list (list -1 2 -3 4 -5) empty (list -3 -4)))
(algun-pos empty)




; 25)
(define (long-lists l)
  (foldr (lambda (sublist result)
           (and result (> (length sublist) 4))
           ) #true l)
  )


(long-lists (list (list 1 2 3 4 5) (list 1 2 3 4 5 6) (list 87 73 78 83 33)))

(long-lists (list '() '() (list 1 2 3)))

(long-lists (list (list 1 2 3 4 5) empty))




; 26)

(define (todos-true l)
  (null? (filter false? (map (lambda (x)
                        (not (false? x))
                        ) l)))
  )

(todos-true (list 1 #true (circle 10 "solid" "red") -12 #false))





; 27)
(define-struct alumno [nombre nota faltas])


; destacados: List -> List
; Recibe una lista de alumnos y devuelve una lista de los alumnos que sacaron
; nota mayor o igual a 9
(define (destacados l)
  (cond
    [(empty? l) '()]
    [else (map alumno-nombre (filter (lambda (x)
                    (>= (alumno-nota x) 9)
                    )l))]
   )
  )

(destacados (list (make-alumno "Ada Lovelace" 10 20)
                  (make-alumno "Carlos Software" 3.5 12)))





; ------
; condicion: Struct -> String
(define (condicion alumno)
  (cond
    [(>= (alumno-nota alumno) 8) "Promovido"]
    [(< (alumno-nota alumno) 6) "Libre"]
    [else "Regular"]
    )
  )

(condicion (make-alumno "Ada Lovelace" 5 20))




; exito; List -> Boolean
; exito devuelve true si todos los alumnos de la lista no han quedado libre,
; caso contrario, devuelve false
(define (exito l)
  (cond
    [(empty? l) false]
    [else (= (length (filter (lambda (x)(not (string=? (condicion x) "Libre")))l))
             (length l)
             )]
   )
  )

(exito (list (make-alumno "Juan Computación" 5 13)
             (make-alumno "Carlos Software" 3.5 12)
             (make-alumno "Ada Lovelace" 10 20)))





; faltas-regulares: List -> Number

(define (faltas-regulares l)
  (cond
    [(empty? l) 0]
    [else (foldr + 0 (map alumno-faltas (filter (lambda (x)
                               (string=? (condicion x) "Regular")
                               )l)))]
   )
  )

(faltas-regulares (list (make-alumno "Juan Computación" 7 2)
                        (make-alumno "Carlos Software" 3.5 4)
                        (make-alumno "Ada Lovelace" 10 1)))




; promovidos-ausentes: List -> List
(define (promovidos-ausentes l)
  (cond
    [(empty? l) 0]
    [else (map alumno-nombre (filter (lambda (x)
                                       (and (string=? (condicion x))
                                            (>= (alumno-faltas x) 3))
                                       )l))]
    )
  )


(promovidos-ausentes (list (make-alumno "Juan Computación" 9 3)
                        (make-alumno "Carlos Software" 3.5 2)
                        (make-alumno "Ada Lovelace" 10 1)))