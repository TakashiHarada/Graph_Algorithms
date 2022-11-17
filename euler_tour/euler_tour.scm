(define input '((0 1) (0 3) (1 4) (2 3) (2 6) (3 4) (3 7) (4 5) (4 8) (5 9) (6 7) (7 8) (7 10) (8 9) (8 11) (10 11)))

(define ith
  (lambda (xs i)
    (cond
     ((null? xs) '())
     ((= 0 i) (car xs))
     (else (ith (cdr xs) (- i 1))))))

(define rember
  (lambda (a xs)
    (cond
     ((null? xs) '())
     ((eq? a (car xs)) (cdr xs))
     (else (cons (car xs) (rember a (cdr xs)))))))

(define make-n-vertex-empty-graph
  (lambda (n)
    (cond
     ((= 0 n) '())
     (else (cons '() (make-n-vertex-empty-graph (- n 1)))))))

(define add-edge-sub
  (lambda (al u v)
    (cond
     ((null? al) '())
     ((= u 0) (cons (cons v (car al)) (cdr al)))
     (else (cons (car al) (add-edge-sub (cdr al) (- u 1) v))))))

(define add-edge
  (lambda (al e)
    (add-edge-sub 
     (add-edge-sub al (car e) (car (cdr e)))
     (car (cdr e))
     (car e))))

(define remove-edge
  (lambda (e al)
    (remove-edge-sub
     (remove-edge-sub al (car e) (car (cdr e)))
     (car (cdr e))
     (car e))))

(define remove-edge-sub
  (lambda (al u v)
    (cond
     ((null? al) '())
     ((= 0 u) (cons (rember v (car al)) (cdr al)))
     (else (cons (car al) (remove-edge-sub (cdr al) (- u 1) v))))))

(define make-adjacency-list-sub
  (lambda (al es)
    (cond
     ((null? es) al)
     (else
      (make-adjacency-list-sub (add-edge al (car es)) (cdr es))))))

(define make-adjacency-list
  (lambda (n es)
    (map reverse
	 (make-adjacency-list-sub (make-n-vertex-empty-graph n) es))))

;; s means a starting point
;; This function assumes that al is an adjacency list of a graph containing an Euler tour
(define make-euler-tour
  (lambda (al s)
    (reverse (map reverse (make-euler-tour-sub al s '() '())))))

(define make-euler-tour-sub
  (lambda (al v S L)
    (cond
     ((null? (ith al v))
      (cond
       ((null? S) L)
       (else (make-euler-tour-sub
	      al
	      (car (car S))
	      (cdr S)
	      (cons (car S) L)))))
     (else
      (make-euler-tour-sub
       ;; remove edge {v, u} from graph
       (remove-edge (cons v (cons (car (ith al v)) '())) al)
       (car (ith al v))
       ;; push {v, u} to S
       (cons (cons v (cons (car (ith al v)) '())) S)
       L)))))

(define testal (make-adjacency-list 12 input))
(define start 0)

(make-euler-tour testal start)
