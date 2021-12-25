;; (defun new-if (pred then else) 
;; (
;;     cond (pred then)
;;     (t else)
;; ))


(defun sqrtiter (guess x)
    (if (goodEnough guess x)
            (float guess)
        (sqrtiter (improve guess x) x)
    )
)

(defun average (x y)
    (/ (+ x y) 2)
)

(defun improve (guess x)
    (setq t1 (* guess guess))
    (float (/ (+ (/ x t1) (* 2 guess)) 3))
)

(defun goodEnough (guess x)
    (< (abs (- (third1 guess) x)) 0.001)
)

(defun third1 (x)
    (* (* x x) x)
)

(write(sqrtiter 1 9))


