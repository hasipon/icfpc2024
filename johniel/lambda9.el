(define-obsolete-function-alias 'string-to-int 'string-to-number "22.1")
(add-to-list 'load-path "./site-lisp/bigint/")
(add-to-list 'load-path "./site-lisp/s")
(require 's)
(require 'bigint)
(defun T () t)
(defun F () nil)
(defmacro take (len s) (s-left  len s))
(defmacro drop (len s) (s-right len s))
(funcall (lambda (var0)
           (s-concat (s-concat "L"
                               (funcall (funcall var0
                                                 ".")
                                        49))
                     (funcall (funcall var0
                                       (s-concat "\n"
                                                 (funcall (funcall var0
                                                                   ".")
                                                          50)))
                              49)))
         (lambda (var1)
           (funcall (lambda (var1)
                      (funcall (lambda (var2)
                                 (funcall var1
                                          (funcall var2
                                                   var2
                                                   )))
                               (lambda (var2)
                                 (funcall var1
                                          (funcall var2
                                                   var2
                                                   )))))
                    (lambda (var3)
                      (lambda (var2)
                        (if (= var2
                               1)
                            var1
                          (s-concat var1
                                    (funcall var3
                                             (- var2
                                                1)))))))))
