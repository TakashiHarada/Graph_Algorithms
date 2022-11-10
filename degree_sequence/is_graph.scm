;; M-o (Evaluates the current buffer)

;; (is_graph '(5 5 4 4 4 4 4))
;; (is_graph '(4 2 2 1 1))

(define is_graph
  (lambda (xs)
    (cond
     ((fold-right (lambda (x y) (or x y))  #f (map (lambda (x) (< x 0)) xs)) #f)
     ((fold-right (lambda (x y) (and x y)) #t (map (lambda (x) (= x 0)) xs)) #t)
     (else (is_graph (reverse (msort (dec (car xs) (cdr xs)))))))))

(define dec
  (lambda (n xs)
    (cond
     ((null? xs) '())
     ((= 0 n) xs)
     (else (cons (- (car xs) 1) (dec (- n 1) (cdr xs)))))))

(define msort
  (lambda (xs)
    (cond
     ((null? xs) '())
     ((null? (cdr xs)) xs)
     (else
    (merge (msort (take (floor (/ (length xs) 2)) xs))
           (msort (drop (floor (/ (length xs) 2)) xs)))))))

(define take
  (lambda (n xs)
    (cond
     ((null? xs) '())
     ((= 0 n) '())
     (else (cons (car xs) (take (- n 1) (cdr xs)))))))

(define drop
  (lambda (n xs)
    (cond
     ((null? xs) '())
     ((= 0 n) xs)
     (else (drop (- n 1) (cdr xs))))))

(define merge
  (lambda (xs ys)
    (cond
     ((null? xs) ys)
     ((null? ys) xs)
     (else
      (cond
       ((< (car xs) (car ys)) (cons (car xs) (merge (cdr xs) ys)))
       (else (cons (car ys) (merge xs (cdr ys)))))))))
