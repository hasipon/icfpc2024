(setq lexical-binding t)

(require 's)
(defalias 'take 's-left)
(defalias 'drop 's-chop-left)



(funcall (funcall (lambda (y) (funcall y y))
                  (lambda (rec)
                    (lambda (x)
                      (if (= x 383897362)
                          ""
                        (s-concat (take 1 (drop (% x 4) "RDUL"))
                                  (funcall (funcall rec rec) (% (* x 709725402) 998244353)))))))
         1)


;; abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`|~<space><newline>

;; !"#$%&'()*+,-./:;<=>?@[\]^_`|~<space><newline>
;; 0123456

;; SDLUR
;; S>FOL

;; ini, mult, mod, fin
;; ((1,140554628),998244353) 300741564
;; 1 "
;; 140554628 "l6%!
;; 998244353 -jqaj
;; 300741564 $q(yA

;; S3/,6%}},!-"$!-!.\}}

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx I$q(yA S B. BT I" BD B% vx I% SL>OF B$ B$ vr vr B% B* vx I"l6%! I-jqaj I"


B$ B$ Ly B$ vy vy Lr Lx ? B= vx I7 S3/,6%}},!-"$!-!.\}} B. B$ B$ vr vr B% B* vx IM I/oD BT I" BD B% vx I% SL>OF Iq
