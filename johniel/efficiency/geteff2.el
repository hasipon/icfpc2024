(define-obsolete-function-alias 'string-to-int 'string-to-number "22.1")
(add-to-list 'load-path "./site-lisp/bigint/")
(add-to-list 'load-path "./site-lisp/s")
(require 's)
(require 'bigint)
(defun T () t)
(defun F () nil)
(defmacro take (len s) (s-left  len s))
(defmacro drop (len s) (s-right len s))
(+ 2134
   (* (funcall (funcall (lambda (var0)
                          (funcall (lambda (var1)
                                     (funcall var0
                                              (funcall var1
                                                       var1)))
                                   (lambda (var1)
                                     (funcall var0
                                              (funcall var1
                                                       var1)))))
                        (lambda (var2)
                          (lambda (var3)
                            (if (= var3
                                   0
                                   )
                                1

                              (+ 1
                                 (funcall var2
                                          (- var3
                                             1)))))))
               9345873499)
      0))
