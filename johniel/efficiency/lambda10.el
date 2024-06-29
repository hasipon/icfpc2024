(define-obsolete-function-alias 'string-to-int 'string-to-number "22.1")
(add-to-list 'load-path "./site-lisp/bigint/")
(add-to-list 'load-path "./site-lisp/s")
(require 's)
(require 'bigint)
(defun T () t)
(defun F () nil)
(defmacro take (len s) (s-left  len s))
(defmacro drop (len s) (s-right len s))
(s-concat "L"
          (funcall (funcall (lambda (var0)
                              (funcall (lambda (var1)
                                         (funcall var0
                                                  (funcall var1
                                                           var1)))
                                       (lambda (var1)
                                         (funcall var0
                                                  (funcall var1
                                                           var1)))))
                            (lambda (var0)
                              (lambda (var1)
                                (if (= var1
                                       2500)
                                    ""
                                  (s-concat (if (= (% var1
                                                      50)
                                                   0)
                                                "\n"
                                              "")
                                            (s-concat (if (= (% var1 11)
                                                             0)
                                                          "#"
                                                        ".")
                                                      (funcall var0
                                                               (+ var1
                                                                  1))))))))
                   1))
