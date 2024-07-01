
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


;; info: (L,B)1, visited:=2498
;; restart?
;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((90,26),7235733) 5023884
;; 90 I{
;; 26 I;
;; 7235733 I)ctt
;; 5023884 I'%VW

;; info: (L,B)1, visited:=2498
;; restart?
;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((9,84),7235733) 30546
;; 9 I*
;; 84 Iu
;; 7235733 I)ctt
;; 30546 I$K{

;; S3/,6%},!-"$!-!.^}

;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((86,31),1000000007) 86
;; 86 Iw
;; 31 I@
;; 1000000007 I-l|Dz
;; 86 Iw

;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((88,47),1000000007) 836210
;; 88 Iy
;; 47 IP
;; 1000000007 I-l|Dz
;; 836210 I"!\q

;; ini, mult, mod, fin
;; ((88,47),1000000007) 291
;; 88 Iy
;; 47 IP
;; 1000000007 I-l|Dz
;; 291 I$*

B$ B$ Ly B$ vy vy Lr Lx ? B= vx I$* S3/,6%}},!-"$!-!.^}} B. B$ B$ vr vr B% B* vx IP I-l|Dz BT I" BD B% vx I% SL>OF Iy
