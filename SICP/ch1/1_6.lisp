;; 因为是应用序

(defun new-if (pred then else) 
(
    cond (pred then)
    (t else)
))


(defun sqrtiter (guess x)
    (new-if (goodEnough guess x)
            (float guess)
        (sqrtiter (improve guess x) x)
    )
)

(defun average (x y)
    (/ (+ x y) 2)
)

(defun improve (guess x)
    (average guess (/ x guess))
)

(defun goodEnough (guess x)
    (< (abs (- (square guess) x)) 0.001)
)

(defun square (x)
    (* x x)
)

(write(sqrtiter 1 2))


;; (write(new-if (= 3 3) 0 5))