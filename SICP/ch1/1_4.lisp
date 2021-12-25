(defun aplusabsb (a b)
((kk a b) a b)
)

(defun kk (a b)
    (if (> b 0) 
        (return-from kk +)
    (return-from kk -))
)

(print (aplusabsb 1 2))