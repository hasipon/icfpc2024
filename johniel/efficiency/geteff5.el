;;; -*- lexical-binding: t -*-
(setq lexical-binding t)
(define-obsolete-function-alias 'string-to-int 'string-to-number "22.1")
;; (add-to-list 'load-path "./site-lisp/bigint/")
;; (add-to-list 'load-path "./site-lisp/s")
(require 's)
(require 'bigint)
(defun T () t)
(defun F () nil)
(defmacro take (len s) (s-left  len s))
(defmacro drop (len s) (s-right len s))
(funcall (lambda (var0)
           (funcall (lambda (var1)
                      (funcall (funcall (lambda (var2)
                                          (funcall (lambda (var3)
                                                     (funcall var2
                                                              (funcall var3 var3)))
                                                   (lambda (var3)
                                                     (funcall var2
                                                              (funcall var3 var3)))))
                                        (lambda (var4)
                                          (lambda (var5)
                                            (if (and (> var5 1000000)
                                                     (and (funcall var0 var5)
                                                          (funcall var1
                                                                   (+ var5 1))))
                                                var5
                                              (funcall var4
                                                       (+ var5 1))))))
                               2))
                    (funcall (lambda (var2)
                               (funcall (lambda (var3)
                                          (funcall var2
                                                   (funcall var3 var3)))
                                        (lambda (var3)
                                          (funcall var2
                                                   (funcall var3 var3)))))
                             (lambda (var4)
                               (lambda (var5)
                                 (if (= var5 1)
                                     (T)
                                   (if (= (% var5 2)
                                          1)
                                       (F)
                                     (funcall var4
                                              (/ var5 2)))))))))
         (lambda (var6)
           (funcall (funcall (lambda (var2)
                               (funcall (lambda (var3)
                                          (funcall var2
                                                   (funcall var3 var3)))
                                        (lambda (var3)
                                          (funcall var2
                                                   (funcall var3 var3)))))
                             (lambda (var4)
                               (lambda (var5)
                                 (if (= var5 var6)
                                     (T)
                                   (if (= (% var6 var5)
                                          0)
                                       (F)
                                     (funcall var4
                                              (+ var5 1)))))))
                    2)))
;;
