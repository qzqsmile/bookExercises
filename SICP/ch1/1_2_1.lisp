;; (defun fac (n)
;;     ( 
;;         if (= n 1) 
;;             1
;;         (* n (fac (- n 1)))
;;     )
;; )


;; (print (fac 1000))


(defun factorial (n) (
    fact-iter 1 1 n
)
)

(defun fact-iter (product counter max-count) (
    if (> counter max-count)
            product
        (fact-iter (* counter product) (+ counter 1) max-count)
))