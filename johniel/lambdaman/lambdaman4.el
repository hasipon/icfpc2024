(setq lexical-binding t)

(require 's)
(defalias 'take 's-left)
(defalias 'drop 's-chop-left)


(setq lexical-binding t)
(funcall (funcall (lambda (y) (funcall y y))
                  (lambda (rec)
                    (lambda (x)
                      (if (= x 1024)
                          ""
                        (s-concat (take 1 (drop (% x 4) "RDUL"))
                                  (funcall (funcall rec rec) (% (* x 2) 998244353)))))))
         1)


;; abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`|~<space><newline>

;; !"#$%&'()*+,-./:;<=>?@[\]^_`|~<space><newline>
;; 0123456

;; SDLUR
;; S>FOL

;; ini, mult, mod, fin
;; ((727542893,773883195),998244353) 628867074
;; 727542893 *>yO"
;; 773883195 *ve|z
;; 998244353 -jqaj
;; 628867074 )&."9

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx I)&."9 S B. BT I" BD B% vx I% SL>OF B$ B$ vr vr B% B* vx I*ve|z I-jqaj I*>yO"

;; ini, mult, mod, fin
;; ((1,709725402),998244353) 383897362
;; 1 "
;; 709725402 *)O#7
;; 998244353 -jqaj
;; 383897362 %w3{O


;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx I%w3{O S B. BT I" BD B% vx I% SL>OF B$ B$ vr vr B% B* vx I*)O#7 I-jqaj I"

;;

;; ini, mult, mod, fin
;; ((1,86),998244353) 7396
;; 1 "
;; 86 w
;; 998244353 -jqaj
;; 7396 oa
;; 3/,6%},!-"$!-!.Y}

(funcall (funcall (lambda (y) (funcall y y))
                  (lambda (rec)
                    (lambda (x)
                      (if (= x 7396)
                          "solve lambdaman4 "
                        (s-concat (funcall (funcall rec rec) (% (* x 86) 998244353))
                                  (take 1 (drop (% x 4) "RDUL")))))))
         1)

(funcall (funcall (lambda (y) (funcall y y))
                  (lambda (rec)
                    (lambda (x)
                      (if (= x 1024)
                          "solve lambdaman4 "
                        (s-concat (funcall (funcall rec rec) (% (* x 2) 998244353))
                                  (take 1 (drop (% x 4) "RDUL")))))))
         1)

;;
;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx I95G S3/,6%}},!-"$!-!.Y}} B. B$ B$ vr vr B% B* vx IM I-jqaj BT I" BD B% vx I% SL>OF I"


;; ini, mult, mod, fin
;; ((77,89),998244353) 6313
;; 77 n
;; 89 z
;; 998244353 -jqaj
;; 6313 d0
;; 3/,6%},!-"$!-!.Y}

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx Id0 S3/,6%}},!-"$!-!.Y}} B. B$ B$ vr vr B% B* vx Iz I-jqaj BT I" BD B% vx I% SL>OF In
