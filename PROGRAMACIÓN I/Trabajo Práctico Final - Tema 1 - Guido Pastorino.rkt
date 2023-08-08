;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname |Trabajo Práctico Final - Tema 1 - Guido Pastorino|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ((lib "image.rkt" "teachpack" "2htdp")) #f)))
#|
Trabajo Práctico Final - Tema 1
Integrante:
- Pastorino Guido
|#



;;;;;;;; Ejercicio 1

; implica: Boolean Boolean -> Boolean
; Recibe dos valores booleanos p y q. Devuelve #true si p implica lógicamente
; a q, y #false en caso contrario.
(define (implica p q)
  (cond [(and p (not q)) #f]
        [else #t])
  )

;check-expects de la función implica
(check-expect (implica #t #t) #t)
(check-expect (implica #t #f) #f)
(check-expect (implica #f #t) #t)
(check-expect (implica #f #f) #t)


; equivalente: Boolean Boolean -> Boolean
; Recibe dos valores booleanos p y q. Devuelve #true si p y q son lógicamente
; equivalentes, y #false en caso contrario.
(define (equivalente p q)
  (cond [(or (and p (not q)) (and (not p) q)) #f]
        [else #t])
  )

;check-expects de la función equivalente
(check-expect (equivalente #t #t) #t)
(check-expect (equivalente #t #f) #f)
(check-expect (equivalente #f #t) #f)
(check-expect (equivalente #f #f) #t)




;;;;;;;; Ejercicio 2

; agregar-false: List(Boolean) -> List(Boolean)
; Agrega #false al inicio de una lista de booleanos.
(define (agregar-false val)
    (cons #false val))

(check-expect (agregar-false '()) '(#false))
(check-expect (agregar-false '(#true)) '(#false #true))
(check-expect (agregar-false '(#true #false)) '(#false #true #false))


; agregar-true: List(Boolean) -> List(Boolean)
; Agrega #true al inicio de una lista de booleanos.
(define (agregar-true val)
    (cons #true val))


(check-expect (agregar-true '()) '(#true))
(check-expect (agregar-true '(#false)) '(#true #false))
(check-expect (agregar-true '(#false #true)) '(#true #false #true))


; valuaciones: Number -> List((List(Boolean)))
; Recibe un número n. Devuelve una lista de listas de booleanos que representan
; todas las posibles valuaciones para n variables proposicionales.
(define (valuaciones n)
  (if (= n 0)
      (list '())
      (let ((vals (valuaciones (- n 1))))
        (append (map agregar-false vals)
                (map agregar-true vals)))
      )
  )


; check-expect de la función valuaciones
(check-expect (valuaciones 3) (list
 (list #false #false #false)
 (list #false #false #true)
 (list #false #true #false)
 (list #false #true #true)
 (list #true #false #false)
 (list #true #false #true)
 (list #true #true #false)
 (list #true #true #true)))





;;;;;;;; Ejercicio 3


; A : List(Boolean) -> Boolean
(define
  (A l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)])
  (equivalente (and (implica p1 p3)
                    (implica p2 p3))
               (implica (or p1 p2)
                        p3))))



; B : List(Boolean) -> Boolean
; Evalúa la fórmula proposicional B, que involucra tres variables
; booleanas: p1, p2 y p3. Devuelve #true si la implicación (p1 ⋀ p2) -> p3 es
; lógicamente equivalente a la conjunción (p1 -> p3) ⋀ (p2 -> p3)
(define (B l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)])
    (equivalente (implica (and p1 p2) p3)
                 (and (implica p1 p3) (implica p2 p3)))))

; check-expect de la función B:
(check-expect (B (list #t #t #t)) #t)
(check-expect (B (list #f #f #f)) #t)
(check-expect (B (list #t #f #t)) #t)
(check-expect (B (list #f #t #f)) #f)



; C : List(Boolean) -> Boolean
; Evalúa la fórmula proposicional C, que involucra
; dos variables booleanas: p1 y p2. Devuelve #true si la disyunción entre
; la negación de p1 y la negación de p2 es lógicamente equivalente a la conjunción
; de p1 y p2
(define (C l)
  (let ([p1 (first l)]
        [p2 (second l)])
    (equivalente (or (not p1) (not p2))
                 (and p1 p2))))



; check-expect de la función C:
(check-expect (C (list #t #f)) #f)
(check-expect (C (list #f #t)) #f)
(check-expect (C (list #t #t)) #f)
(check-expect (C (list #f #f)) #f)




;;;;;;;; Ejercicio 4

; evaluar: (List(Boolean) -> Boolean) Number -> List(Boolean)
; Evalúa una fórmula proposicional en todas las posibles valuaciones
; de n variables y devuelve una lista con los resultados.
(define (evaluar P n)
  (map P (valuaciones n)))

; check-expect de la función evaluar
(check-expect (evaluar P 3) (list #true #true #true #true #true #true #true #true))


; P: List(Boolean) -> Boolean
; Función proposicional que representa la fórmula a evaluar.
(define (P l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)])
    (implica (and (implica p1 p3)
                  (implica p2 p3))
             (implica (or p1 p2)
                      p3))))

(check-expect (P (list #true #false #true)) #true)





;;;;;;;; Ejercicio 5


; boolean-normal Boolean -> Boolean
; Toma un valor booleano y lo devuelve.
(define (boolean-normal v)
  v)

(check-expect (boolean-normal #t) #t)

; boolean-negate: Boolean -> Boolean
; Toma un valor booleano y devuelve su negación lógica.
(define (boolean-negate v)
  (not v))

(check-expect (boolean-negate #t) #f)

; tautología?: (List(Boolean) -> Boolean) Number -> Boolean
; Verifica si una fórmula proposicional es una tautología.
(define (tautología? P n)
  (andmap boolean-normal (evaluar P n)))

; contradicción?: (List(Boolean) -> Boolean) Number -> Boolean
; Verifica si una fórmula proposicional es una contradicción.
(define (contradicción? P n)
  (andmap boolean-negate (evaluar P n)))

; satisfactible?: (List(Boolean) -> Boolean) Number -> Boolean
; Verifica si una fórmula proposicional es satisfactible.
(define (satisfactible? P n)
  (ormap boolean-normal (evaluar P n)))


(check-expect (tautología? A 3) #t)
(check-expect (contradicción? B 6) #f)
(check-expect (satisfactible? C 8) #f)








; __________ TESTS (archivo tests.txt) __________




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