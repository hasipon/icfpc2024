(setq lexical-binding t)
(setq max-specpdl-size 10000)
(setq max-lisp-eval-depth 10000)
(define-obsolete-function-alias 'string-to-int 'string-to-number "22.1")
(add-to-list 'load-path "./site-lisp/bigint/")
(add-to-list 'load-path "./site-lisp/s")
(require 's)
(require 'bigint)
(defun T () t)
(defun F () nil)
(defalias 'take 's-left)
(defalias 'drop 's-right)
(funcall (funcall (lambda (var0)
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
                             "")
                          0

                        (+ 1
                           (funcall var2 (drop 1 var3)))))))
         (funcall (lambda (var1)
                    (s-concat (funcall var1
                                       (funcall var1
                                                (funcall var1
                                                         (funcall var1
                                                                  (funcall var1
                                                                           (funcall var1
                                                                                    (funcall var1
                                                                                             (funcall var1
                                                                                                      (funcall var1
                                                                                                               (funcall var1
                                                                                                                        (funcall var1
                                                                                                                                 (funcall var1
                                                                                                                                          (funcall var1
                                                                                                                                                   (funcall var1
                                                                                                                                                            (funcall var1
                                                                                                                                                                     (funcall var1
                                                                                                                                                                              (funcall var1
                                                                                                                                                                                       (funcall var1
                                                                                                                                                                                                (funcall var1
                                                                                                                                                                                                         (funcall var1
                                                                                                                                                                                                                  (funcall var1
                                                                                                                                                                                                                           (funcall var1
                                                                                                                                                                                                                                    (funcall var1
                                                                                                                                                                                                                                             (funcall var1
                                                                                                                                                                                                                                                      (funcall var1
                                                                                                                                                                                                                                                               (funcall var1
                                                                                                                                                                                                                                                                        (funcall var1
                                                                                                                                                                                                                                                                                 (funcall var1
                                                                                                                                                                                                                                                                                          "na"))))))))))))))))))))))))))))
                              "heyjude"))
                  (lambda (var0)
                    (s-concat var0
                              var0))))
