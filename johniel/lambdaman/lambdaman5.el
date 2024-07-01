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
                                  (funcall (funcall rec rec) (% (* x 2) 998244353))))))))


;; DONE: (A,B)1
;; ini, mult, mod, fin
;; ((737537172,1718),998244353) 4096
;; 737537172 I*J|W-
;; 1718 I3;
;; 998244353 I-jqaj
;; 450974094 I&i{9g

;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((8466,55),998244353) 283
;; 8466 I{'
;; 55 IX
;; 998244353 I-jqaj
;; 283 I$"


;; 119
;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx II$" S3/,6%}},!-"$!-!.Z}} B. B$ B$ vr vr B% B* vx IX I-jqaj BT I" BD B% vx I% SL>OF II{'

;; restart?
;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((28,42),998244353) 1809
;; 28 I=
;; 42 IK
;; 998244353 I-jqaj
;; 1809 I48

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx I48 S3/,6%}},!-"$!-!.Z}} B. B$ B$ vr vr B% B* vx IX I-jqaj BT I" BD B% vx IK SL>OF I=


;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx I$" S3/,6%}},!-"$!-!.Z}} B. B$ B$ vr vr B% B* vx IX I-jqaj BT I" BD B% vx I% SL>OF I{'

;; restart?
;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((28,42),998244353) 3158
;; 28 I=
;; 42 IK
;; 998244353 I-jqaj
;; 3158 IBY

;; 115
;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx IBY S3/,6%}},!-"$!-!.Z}} B. B$ B$ vr vr B% B* vx IK I-jqaj BT I" BD B% vx I% SL>OF I=

;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((57,15),65087) 57
;; 57 IZ
;; 15 I0
;; 65087 I(CH
;; 57 IZ

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx IZ S3/,6%}},!-"$!-!.Z}} B. B$ B$ vr vr B% B* vx I0 I(CH BT I" BD B% vx I% SL>OF IZ

;; 3/,6%}},!-"$!-!.Z}


;; DONE: (L,B)1
;; ini, mult, mod, fin
;; ((28,42),7235733) 540
;; 28 I=
;; 42 IK
;; 7235733 I)ctt
;; 540 I&g

;; B$ B$ Ly B$ vy vy Lr Lx ? B= vx I&g S3/,6%}},!-"$!-!.Z}} B. B$ B$ vr vr B% B* vx IK I)ctt BT I" BD B% vx I% SL>OF I=




;; DONE: (A,B)1
;; ini, mult, mod, fin
;; ((28,42),524287) 56
;; 28 I=
;; 42 IK
;; 524287 I\@R
;; 56 IY



B$ B$ Ly B$ vy vy Lr Lx ? B= vx IY S3/,6%}},!-"$!-!.Z}} B. B$ B$ vr vr B% B* vx IK I\@R BT I" BD B% vx I% SL>OF I=
