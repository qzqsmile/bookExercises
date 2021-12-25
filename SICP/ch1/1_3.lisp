(defun mysummax2 (a b c) (
    if (= a (mymax2 a b))(
        if (= b (mymax2 b c))
            (return-from  mysummax2 (+ a b))
        (return-from mysummax2 (+ a c))
    )
    (
        if (= a (mymax2 a c))
            (return-from mysummax2 (+ b a))
        (return-from mysummax2 (+ b c))
    )
))

(defun mymax2 (a b) 
    (
        if (>= a b)
            (return-from mymax2 a)
        (return-from mymax2 b)
    )
)

(print (mysummax2 10 5 4))

