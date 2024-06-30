
(add-keywords 'emacs-lisp-mode '("L" "B" "U" "S") ')

;; SDLUR
;; S>FOL

;; #$%&?

;;
(funcall (lambda (rep)
           (funcall rep
                    (s-concat (s-concat (funcall rep "DD") "R")
                              (s-concat (funcall rep "UU") "R"))))
         (lambda (word)
           (funcall
            (lambda (triple)
              (funcall triple (funcall triple (funcall triple word))))
            (lambda (pattern)
              (s-concat (s-concat pattern pattern)
                        pattern)))))

;;
B$ L# B$ v# B. B. B$ v# S>> SL B. B$ v# SOO SL L% B$ L$ B$ v$ B$ v$ B$ v$ v% L? B. B. v? v? v?

;;116point

;;
(funcall (lambda (rep)
           (funcall rep
                    (s-concat (s-concat (funcall rep "DDDD") "R")
                              (s-concat (funcall rep "UUUU") "R"))))
         (lambda (word)
           (funcall
            (lambda (quatriple)
              (funcall quatriple (funcall quatriple word)))
            (lambda (pattern)
              (s-concat (s-concat pattern pattern)
                        (s-concat pattern pattern))))))

;;
B$ L# B$ v# B. B. B$ v# S>>>> SL B. B$ v# SOOOO SL L$ B$ L? B$ v? B$ v? v$ L$ B. B. v$ v$ B. v$ v$

;;横移動が足りない。駄目。

;;


(funcall (lambda (rep)
           (funcall rep
                    (s-concat (funcall rep "D")
                              (s-concat (funcall rep "U")
                                        "R"))))
         (lambda (word)
           (funcall
            (lambda (quatriple)
              (funcall quatriple (funcall quatriple (funcall quatriple word))))
            (lambda (pattern)
              (s-concat (s-concat pattern pattern)
                        (s-concat pattern pattern))))))


B$ L# B$ v# B. B$ v# S> B. B$ v# SO SL L% B$ L? B$ v? B$ v? B$ v? v% L$ B. B. v$ v$ B. v$ v$
