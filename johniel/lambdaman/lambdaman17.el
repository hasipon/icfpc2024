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
;;

;; DONE: (a,b)1
;; ini, mult, mod, fin
;; ((195218096,4049),998244353) 16125
;; 195218096 #P$O9
;; 4049 L(
;; 998244353 -jqaj
;; 16125 "nT

;; DONE: (b,x)2
;; ini, mult, mod, fin
;; ((106948013,6678),998244353) 139595
;; 106948013 "Ch_n
;; 6678 h%
;; 998244353 -jqaj
;; 139595 0l&

;; DONE: (x,c)8
;; ini, mult, mod, fin
;; ((842510466,6831),998244353) 9872
;; 842510466 +kBh=
;; 6831 i`
;; 998244353 -jqaj
;; 9872 ",#

;; DONE: (c,d)3
;; ini, mult, mod, fin
;; ((309407153,2686),998244353) 1377
;; 309407153 ${Q^L
;; 2686 =W
;; 998244353 -jqaj
;; 1377 /^

;; DONE: (d,e)4
;; ini, mult, mod, fin
;; ((70998579,6777),998244353) 178826
;; 70998579 vN/$
;; 6777 i*
;; 998244353 -jqaj
;; 178826 57G

(setq lexical-binding t)

(funcall (lambda (solve)
           (s-concat (s-concat (s-concat (funcall (funcall (funcall solve 195218096) 4049) 16125)
                                         (funcall (funcall (funcall solve 106948013) 6678) 139595))
                               (s-concat (funcall (funcall (funcall solve 842510466) 6831) 9872)
                                         (funcall (funcall (funcall solve 309407153) 2686) 1377)))
                     (funcall (funcall (funcall solve 70998579) 6777) 178826)))
         (lambda (seed)
           (lambda (mult)
             (lambda (fin)
               (funcall (funcall (lambda (y) (funcall y y))
                                 (lambda (rec)
                                   (lambda (x)
                                     (if (= x fin)
                                         ""
                                       (s-concat (take 1 (drop (% x 4) "RDUL"))
                                                 (funcall (funcall rec rec) (% (* x mult) 998244353)))))))
                        seed)))))

;; !"#$%&'()*+,-./:;<=>?@[\]^_`|~<space><newline>
;; 0123456

;;  RDUL
;; SL>OF

;; B$ Lz B. B. B. B$ B$ B$ vz I#P$O9 IL( I"nT B$ B$ B$ vz I"Ch_n Ih% I0l& B. B$ B$ B$ vz I+kBh= Ii` I",# B$ B$ B$ vz I${Q^L I=W I/^ B$ B$ B$ vz IvN/$ Ii* I57G Ls Lm Lf B$ B$ Ly B$ vy vy Lr Lx ? B= vx vf S B. BT I" BD B% vx I% SL>OF B$ B$ vr vr B% B* vx vm I-jqaj vs


(funcall (lambda (solve)
           (s-concat (s-concat (funcall (funcall (funcall solve 195218096) 4049) 16125)
                               (funcall (funcall (funcall solve 106948013) 6678) 139595))
                     (funcall (funcall (funcall solve 70998579) 6777) 178826)))
         (lambda (seed)
           (lambda (mult)
             (lambda (fin)
               (funcall (funcall (lambda (y) (funcall y y))
                                 (lambda (rec)
                                   (lambda (x)
                                     (if (= x fin)
                                         ""
                                       (s-concat (take 1 (drop (% x 4) "RDUL"))
                                                 (funcall (funcall rec rec) (% (* x mult) 998244353)))))))
                        seed)))))
;;

;; DONE: (a,b)1
;; ini, mult, mod, fin
;; ((404359852,3753),998244353) 16449
;; 404359852 &1oiU
;; 3753 Hx
;; 998244353 -jqaj
;; 16449 "q~

;; DONE: (b,c)2
;; ini, mult, mod, fin
;; ((836972889,3262),998244353) 102156
;; 836972889 +db%v
;; 3262 Cc
;; 998244353 -jqaj
;; 102156 ,Ui

;; DONE: (c,d)3
;; ini, mult, mod, fin
;; ((414907699,431),998244353) 504372
;; 414907699 &>SPb
;; 431 %X
;; 998244353 -jqaj
;; 504372 Z(_

;; B$ Lz B. B. B$ B$ B$ vz I&1oiU IHx I"q~ B$ B$ B$ vz I+db%v ICc I,Ui B$ B$ B$ vz I&>SPb I%X IZ(_ Ls Lm Lf B$ B$ Ly B$ vy vy Lr Lx ? B= vx vf S B. BT I" BD B% vx I% SL>OF B$ B$ vr vr B% B* vx vm I-jqaj vs


(funcall (lambda (solve)
           (s-concat (funcall (funcall (funcall solve 195218096) 4049) 16125)
                     (funcall (funcall (funcall solve 106948013) 6678) 139595)))
         (lambda (seed)
           (lambda (mult)
             (lambda (fin)
               (funcall (funcall (lambda (y) (funcall y y))
                                 (lambda (rec)
                                   (lambda (x)
                                     (if (= x fin)
                                         ""
                                       (s-concat (take 1 (drop (% x 4) "RDUL"))
                                                 (funcall (funcall rec rec) (% (* x mult) 998244353)))))))
                        seed)))))
;;

;; DONE: (A,B)1
;; ini, mult, mod, fin
;; ((254692993,7194),998244353) 5307
;; 254692993 $9]Lx
;; 7194 mS
;; 998244353 -jqaj
;; 5307 YL

;; DONE: (B,C)2
;; ini, mult, mod, fin
;; ((343601640,4109),998244353) 69656302
;; 343601640 %FaUY
;; 4109 Ld
;; 998244353 -jqaj
;; 69656302 tr7O

;; B$ Lz B. B$ B$ B$ vz I$9]Lx ImS IYL B$ B$ B$ vz I%FaUY ILd Itr7O Ls Lm Lf B$ B$ Ly B$ vy vy Lr Lx ? B= vx vf S B. BT I" BD B% vx I% SL>OF B$ B$ vr vr B% B* vx vm I-jqaj vs
;; B$ Lz B. B$ B$ B$ vz I$9]Lx Ims IYL B$ B$ B$ vz I%FaUY ILd Itr7O Ls Lm Lf B$ B$ Ly B$ vy vy Lr Lx ? B= vx vf S B. BT I" BD B% vx I% SL>OF B$ B$ vr vr B% B* vx vm I-jqaj vs
