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
(defmacro take (len s) (s-left  len s))
(defmacro drop (len s) (s-right len s))
(funcall (funcall (lambda (var0)
                    (funcall (lambda (var1)
                               (funcall var0
                                        (funcall var1 var1)))
                             (lambda (var1)
                               (funcall var0
                                        (funcall var1 var1)))))
                  (lambda (var2)
                    (lambda (var3)
                      (funcall (funcall (lambda (var0)
                                          (lambda (var1)
                                            (if (< var0 var1)
                                                var0
                                              var1)))
                                        var3)
                               (+ 1
                                  (if (> var3 2)
                                      (funcall (funcall (funcall (lambda (var0)
                                                                   (funcall (lambda (var1)
                                                                              (funcall var0
                                                                                       (funcall var1 var1)))
                                                                            (lambda (var1)
                                                                              (funcall var0
                                                                                       (funcall var1 var1)))))
                                                                 (lambda (var4)
                                                                   (lambda (var5)
                                                                     (lambda (var6)
                                                                       (if (= var5 var3)
                                                                           var6
                                                                         (funcall (funcall var4 (+ var5 1))
                                                                                  (if (> (funcall var2 var5)
                                                                                         (- var5 1))
                                                                                      (if (= (% var3 var5)
                                                                                             0)
                                                                                          (* (/ var6 (funcall var2 var5))
                                                                                             (- (funcall var2 var5) 1))
                                                                                        var6)
                                                                                    var6)))))))
                                                        2)
                                               var3)
                                    var3))))))
         1234567)
