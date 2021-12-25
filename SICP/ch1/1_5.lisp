;; 应用序 先求值 再带入 正则序 先带入过程 再求值

(defun test (x y)
    (if(= x 0)
     0
     y
    )
)
(defun p () (p))

(write(test 0 (p)))
;; (write(p))