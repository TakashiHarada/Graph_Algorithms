(define gen-rand-deg-seq
  (lambda (n)
    (cond
     ((<= n 0) ())
     (else (sort (cons (+ 1 (random (- n 1))) (gen-rand-deg-seq-sub n (- n 1))) >)))))

(define gen-rand-deg-seq-sub
  (lambda (n i)
    (cond
     ((<= i 0) ())
     (else (cons (+ 1 (random (- n 1))) (gen-rand-deg-seq-sub n (- i 1)))))))

;; (gen-rand-deg-seq 8)
