(add-keywords 'emacs-lisp-mode '("L" "B" "U" "S") ')

;; SDLUR
;; S>FOL

;; #$%&?

(s-concat (funcall (lambda (octpule)
                     (funcall octpule
                              (s-concat "UUUU"
                                        (funcall octpule
                                                 (s-concat (s-concat (funcall octpule (s-concat (funcall octpule "RR")
                                                                                                "DRRU"))
                                                                     "LDR")
                                                           (s-concat (funcall octpule (s-concat (funcall octpule "LL")
                                                                                                "DLLU"))
                                                                     "RDL"))))))
                   (lambda (word)
                     (funcall
                      (lambda (double)
                        (funcall double (funcall double (funcall double word))))
                      (lambda (pattern)
                        (s-concat pattern pattern)))))
          "RRURRDRRRRRRRRRURRDRRRRRRRRRURRDRRRRRRRRRURRDRRRRRRRRR")


;;

;; B. B$ L- B$ v- B. SOOOO B$ v- B. B. B$ v- B. B$ v- SRR S>LLO SF>L B. B$ v- B. B$ v- SFF S>FFO SL>FF L% B$ L# B$ v# B$ v# B$ v# v% L? B. v? v? SLLOLL>LLLLLLLLLOLL>LLLLLLLLLOLL>LLLLLLLLLOLL>LLLLLLLLL


(funcall (funcall (lambda (x)
                    (funcall x x))
                  (lambda (rec)
                    (lambda (n)
                      (if (= n 0)
                          1
                        (* n (funcall (funcall rec rec) (- n 1)))))))
         5)

;;

(funcall (funcall (lambda (y) (funcall y y))
                  (lambda (rec)
                    (lambda (x)
                      (if (= x 1024)
                          "solve lambdaman10 "
                        (s-concat (funcall (funcall rec rec) (% (* x 2) 998244353))
                                  (take 1 (drop (% x 4) "RDUL")))))))
         1)

;;
;; ini, mult, mod, fin
;; ((77,89),998244353) 6313
;; 77 n
;; 89 z
;; 998244353 -jqaj
;; 6313 d0
;; 3/,6%},!-"$!-!.Y}

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx Id0 S3/,6%}},!-"$!-!.Y}} B. B$ B$ vr vr B% B* vx Iz I-jqaj BT I" BD B% vx I% SL>OF In

;; ini, mult, mod, fin
;; ((901143412,89),998244353) 69493
;; 901143412 ,SzK%
;; 89 z
;; 998244353 -jqaj
;; 69493 (r<
;; 3/,6%}},!-"$!-!.VU}}

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx I(r< S3/,6%}},!-"$!-!.VU}} B. B$ B$ vr vr B% B* vx Iz I-jqaj BT I" BD B% vx I% SL>OF I,SzK%


;; ini, mult, mod, fin
;; ((164528294,5),998244353) 443012
;; 164528294 #+)6!
;; 5 &
;; 998244353 -jqaj
;; 443012 S-u
;; 3/,6%},!-"$!-!.VU}


;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx IS-u S3/,6%}},!-"$!-!.VU}} B. B$ B$ vr vr B% B* vx I#+)6! I-jqaj BT I" BD B% vx I% SL>OF I,SzK%


;; ini, mult, mod, fin
;; ((818830389,1049),998244353) 722624
;; 818830389 +NplX
;; 1049 ,0
;; 998244353 -jqaj
;; 722624 rjO
;; 3/,6%},!-"$!-!.VU}

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx IrjO S3/,6%}},!-"$!-!.VU}} B. B$ B$ vr vr B% B* vx I,0 I-jqaj BT I" BD B% vx I% SL>OF I+NplX
