
(add-keywords 'emacs-lisp-mode '("L" "B" "U" "S") ')

(defun double (s)
  (s-concat s s))

(double (double (double (double "DLUR"))))


;; 
(L(#) (B$ (B$ B. v#) v#))



(lambda (v0)
  (funcall s-concat v0 v0))


(funcall (lambda (double)
           (funcall double (funcall double (funcall double (funcall double (funcall double (funcall double "DLUR")))))))
         (lambda (pattern)
           (s-concat pattern)))


;;
(defun double (str)
  (s-concat str str))

(defun len100 (dir-char)
  (double (double (double (double (double (double dir-char)))))))

(double (double (double (double (double (s-concat (len100 "D")
                                                  (len100 "L")
                                                  (len100 "U")
                                                  (len100 "R")))))))

;; SDLUR
;; S>FOL

;; #$%&?

;;
(funcall (lambda (rep100)
           (funcall rep100
                    (s-concat (s-concat (funcall rep100 "D")
                                        (funcall rep100 "L"))
                              (s-concat (funcall rep100 "U")
                                        (funcall rep100 "R")))))
         (lambda (word)
           (funcall
            (lambda (double)
              (funcall double (funcall double (funcall double (funcall double (funcall double (funcall double (funcall double word))))))))
            (lambda (pattern)
              (s-concat pattern pattern)))))

;;
(B$ (lambda (v#)
      (B$ v#
          (B. (B. (B$ v# S>)
                  (B$ v# SF))
              (B. (B$ v# SO)
                  (B$ v# SL)))))
    (lambda (v%)
      (B$
       (lambda (v$)
         (B$ v$ (B$ v$ (B$ v$ (B$ v$ (B$ v$ (B$ v$ (B$ v$ v%))))))))
       (lambda (v?)
         (B. v? v?)))))

;;
(B$ (L#
     (B$ v#
         (B. (B. (B$ v# S>)
                 (B$ v# SF))
             (B. (B$ v# SO)
                 (B$ v# SL)))))
    (L%
     (B$
      (L$
       (B$ v$ (B$ v$ (B$ v$ (B$ v$ (B$ v$ (B$ v$ (B$ v$ v%))))))))
      (L?
       (B. v? v?)))))

;;
B$ L# B$ v# B. B. B$ v# S> B$ v# SF B. B$ v# SO B$ v# SL L% B$ L$ B$ v$ B$ v$ B$ v$ B$ v$ B$ v$ B$ v$ B$ v$ v% L? B. v? v?

;;
(funcall (lambda (var0) 
           (funcall var0
                    (s-concat (s-concat (funcall var0 "D")
                                        (funcall var0 "L"))
                              (s-concat (funcall var0 "U")
                                        (funcall var0 "R")))))
         (lambda (var1) 
           (funcall (lambda (var2) 
                      (funcall var2
                               (funcall var2
                                        (funcall var2
                                                 (funcall var2
                                                          (funcall var2
                                                                   (funcall var2
                                                                            (funcall var2
                                                                                     var1))))))))
                    (lambda (var3) 
                      (s-concat var3
                                var3)))))

;; 144point!


;;
(funcall (lambda (rep100)
           (funcall rep100
                    (s-concat (s-concat (funcall rep100 "D")
                                        (funcall rep100 "L"))
                              (s-concat (funcall rep100 "U")
                                        (funcall rep100 "R")))))
         (lambda (word)
           (funcall
            (lambda (quatriple)
              (funcall quatriple (funcall quatriple (funcall quatriple (funcall quatriple word)))))
            (lambda (pattern)
              (s-concat (s-concat pattern pattern)
                        (s-concat pattern pattern))))))
;;
(B$ (lambda (v#)
      (B$ v#
          (B. (B. (B$ v# S>)
                  (B$ v# SF))
              (B. (B$ v# SO)
                  (B$ v# SL)))))
    (lambda (v%)
      (B$
       (lambda (v$)
         (B$ v$ (B$ v$ (B$ v$ (B$ v$ v%)))))
       (lambda (v?)
         (B. (B. v? v?) (B. v? v?))))))

;;
B$ L# B$ v# B. B. B$ v# S> B$ v# SF B. B$ v# SO B$ v# SL L% B$ L$ B$ v$ B$ v$ B$ v$ B$ v$ v% L? B. B. v? v? B. v? v?

;; 138point

;;
(funcall (lambda (rep81)
           (funcall rep81
                    (s-concat (s-concat (funcall rep81 "DD")
                                        (funcall rep81 "LL"))
                              (s-concat (funcall rep81 "UU")
                                        (funcall rep81 "RR")))))
         (lambda (word)
           (funcall
            (lambda (triple)
              (funcall triple (funcall triple (funcall triple (funcall triple word)))))
            (lambda (pattern)
              (s-concat (s-concat pattern pattern)
                        pattern)))))

;;
B$ L# B$ v# B. B. B$ v# S>> B$ v# SFF B. B$ v# SOO B$ v# SLL L$ B$ L% B$ v% B$ v% B$ v% B$ v% v$ L? B. B. v? v? v?

;; 136point

;;

;; Yコンビネータの定義
(setq Y
      (lambda (f)
        ((lambda (x) (x x))
         (lambda (x)
           (f (lambda (arg) ((x x) arg)))))))

;; 再帰関数の定義（例: 階乗関数）
(setq factorial
      (Y (lambda (recur)
           (lambda (n)
             (if (= n 0)
                 1
               (* n (funcall recur (- n 1))))))))

;; 使用例
(print (funcall factorial 5)) ;; 出力: 120


;;

;; B$ B$ 
;;         La B$ va va 
;;         Lr Ln
;;             ? 
;;                 B< vn I~~~ 
;;                 B. 
;;                     B$ B$ vr vr B+ vn I"
;;                     BT I" BD B% vn I"% SL>FO
;;                 S{header}
;;     I!

(setq lexical-binding t)

(funcall (funcall (lambda (x)
                    (funcall x x))
                  (lambda (rec)
                    (lambda (n)
                      (if (= n 0)
                          1
                        (* n (funcall (funcall rec rec) (- n 1)))))))
         5)

;;
(funcall (lambda (rep)
           (funcall rep
                    (s-concat (s-concat (funcall rep "D")
                                        (funcall rep "L"))
                              (s-concat (funcall rep "U")
                                        (funcall rep "R")))))
         (lambda (word)
           (funcall (funcall (lambda (x)
                               (funcall x x))
                             (lambda (rec)
                               (lambda (n)
                                 (if (= n 0)
                                     ""
                                   (s-concat word (funcall (funcall rec rec) (- n 1)))))))
                    100)))

;;
B$ L# B$ v# B. B. B$ v# S> B$ v# SF B. B$ v# SO B$ v# SL L= B$ B$ L$ B$ v$ v$ L& L@ ? B= v@ I! v= B. v= B$ B$ v& v& B- v@ I\" I~
