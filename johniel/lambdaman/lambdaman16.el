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

B. B$ L- B$ v- B. SOOOO B$ v- B. B. B$ v- B. B$ v- SRR S>LLO SF>L B. B$ v- B. B$ v- SFF S>FFO SL>FF L% B$ L# B$ v# B$ v# B$ v# v% L? B. v? v? SLLOLL>LLLLLLLLLOLL>LLLLLLLLLOLL>LLLLLLLLLOLL>LLLLLLLLL

"$*W!3k},FqejLxL0H#It\'K5c)}7\\Z`6TnC8(b#0H%o=e8W<#g;i0i{E46jOy09{f\'^:Bz_U?+PIz5.#tm?LVQp3)z&R@J`L+~)=_sluH1xcS$-0k=K0tJk{:`@Jh@5]*u`VyS#)(f@R{6j|h$Ilz5-#}6Ig6[\'auODodw9,=Tt:K+wGPIRC=[W1~y^3|<`SahMgk]^5f6ntS$fjt=XXFyS2V6+}1,!e}52bB?hdL{4MBqP1mIpHstk7vw/Bnvy_}WnlUn\"A!OU>j-YT^::iywuCPo.>r^/h;}5X>6}Dj+5m#HqaVM/l<VB9=#LZ5sstnQQ^\"K9~Dw~QIS6xB8!`47&PA74dtV/\\d/TiGS|sC)m\'9jU]\\wu^l?;Y.+MYfLcOycVRdVwfvU-&|A1Lfn:k{BuhA#rRqMyzC3n9ZJpM`=X#vg120!\'n(vFBj\'w!0.0(7WXMM%yUz|vS|w/BHD9fdj:8\"h=U.dGz3,I|@FHL\"xEq<>3PNt?Y#%-np;*h_CZ7qKdtQ$\"]#U9Dv\"I3D6C{nWkZbk#iLttA_RSf()HGLkBG_dppf}krPsbO|\"Ls:Ig<V,row#]+2]Eb_Pn.da|ug=U6a@-FHMt;:kY}S{>oRucy$-TcwrL[etmF=D,Rgi<iHM=Yp]<%Mf=ZpuADtAht^t/HyZcEVNmzTaSYNvM6FX},pC#s{H;NP6;$N|pMU4T/NzgtJ(9uBkRD#9N!`^Zz_\'99`7?1,Ry>y7XPWy&\'#.?Z`_lH}se3Wbgtd|l9-\\x1jP(&MpiJ#By%=s|>hGv]JgC>Bs={/:>cV~@a4q*@_Y=B[!>=Bn[cqLC[h/Kt_GuyP0x8tH0W,>>qEH{>lQPH1i0OEh7v&dZR]Fb@SO}/))CD-y8^7s`\\MeUHg:$]Mh\"!7r+\'9Y.s`-a>w+&^\"0FZ-)O-Rc%jY^JtsF*TG&.AL}$.3~w|)3fQeuMgWFYp6;BM8HT5Se)Hd&[:`<WpY@-c9$n]*J:&T+P%BgS,\\+A1="

(setq lexical-binding t)

(defalias 'take 's-left)
(defalias 'drop 's-chop-left)

(funcall (lambda (curve)
           (funcall (funcall (lambda (x) (funcall x x))
                             (lambda (hilbert)
                               (lambda (n)
                                 (if (= (/ n 4) 0)
                                     ""
                                   (s-concat (s-concat (s-concat (funcall (funcall hilbert hilbert) (+ (* (- (/ n 4) 1) 4)
                                                                                                       (% (+ (% n 4) 1) 4)))
                                                                 (funcall curve (% n 4)))
                                                       (s-concat (funcall (funcall hilbert hilbert) (+ (* (- (/ n 4) 1) 4)
                                                                                                       (% n 4)))
                                                                 (funcall curve (% (+ 1 (% n 4)) 4))))
                                             (s-concat (s-concat (funcall (funcall hilbert hilbert) (+ (* (- (/ n 4) 1) 4)
                                                                                                       (% n 4)))
                                                                 (funcall curve (% (+ 2 (% n 4)) 4)))
                                                       (funcall (funcall hilbert hilbert) (+ (* (- (/ n 4) 1) 4)
                                                                                             (% (+ (% n 4) 3) 4)))))))))
                    8))
         (lambda (dir)
           (take 1 (drop dir "DRUL"))))

;;

(funcall (lambda (curve)
           (funcall (funcall (funcall (funcall (lambda (x) (funcall x x))
                                               (lambda (hilbert)
                                                 (lambda (depth)
                                                   (lambda (dir)
                                                     (lambda (rotate)
                                                       (if (= depth 0)
                                                           ""
                                                         (s-concat (s-concat (s-concat (funcall (funcall (funcall (funcall hilbert hilbert)
                                                                                                                  (- depth 1))
                                                                                                         dir)
                                                                                                (not rotate))
                                                                                       (funcall (funcall curve dir) rotate))
                                                                             (s-concat (funcall (funcall (funcall (funcall hilbert hilbert)
                                                                                                                  (- depth 1))
                                                                                                         dir)
                                                                                                rotate)
                                                                                       (funcall (funcall curve (% (+ dir 1) 4))
                                                                                                rotate)))
                                                                   (s-concat (s-concat (funcall (funcall (funcall (funcall hilbert hilbert)
                                                                                                                  (- depth 1))
                                                                                                         dir)
                                                                                                rotate)
                                                                                       (funcall (funcall curve (% (+ dir 2) 4))
                                                                                                rotate))
                                                                             (funcall (funcall (funcall (funcall hilbert hilbert)
                                                                                                        (- depth 1))
                                                                                               (% (+ 2 dir) 4))
                                                                                      (not rotate))))))))))
                                      8)
                             0)
                    false))
         (lambda (dir)
           (lambda (rotate)
             (take 1 (drop dir (if rotate "DRUL" "RDLU"))))))

;;

;; SDLUR
;; S>FOL
;; !"#$%&'()*+,-./:;<=>?@[\]^_`|
;; 0123456789

;; B$ L# B$ B$ B$ B$ L? B$ v? v? L# L* L< L> ? B= v* I! S B. B. B. B$ B$ B$ B$ v# v# B- v* I" v< B! v> B$ B$ v# v< v> B. B$ B$ B$ B$ v# v# B- v* I" v< v> B$ B$ v# B% B+ v< I" I% v> B. B. B$ B$ B$ B$ v# v# B- v* I" v< v> B$ B$ v# B% B+ v< I# I% v> B$ B$ B$ B$ v# v# B- v* I" B% B+ I# v< I% B! v> I) S! F L< L> BT I" BD v< ? v> S>LOF SL>FO

;; B$ L# B$ B$ B$ B$ L? B$ v? v? L# L* L< L> ? B= v* I! S B. B. B. B$ B$ B$ B$ v# v# B- v* I\" v< B! v> B$ B$ v# v< v> B. B$ B$ B$ B$ v# v# B- v* I\" v< v> B$ B$ v# B% B+ v< I\" I% v> B. B. B$ B$ B$ B$ v# v# B- v* I\" v< v> B$ B$ v# B% B+ v< I# I% v> B$ B$ B$ B$ v# v# B- v* I\" B% B+ I# v< I% B! v> I) I! F L< L> BT I\" BD v< ? v> S>LOF SL>FO


;; B$ Lc B$ B$ B$ B$ Lx B$ vx vx Lh Ln Ld Lr ? B= vn I! S B. B. B. B$ B$ B$ B$ vh vh B- vn I" vd U! vr B$ B$ vc vd vr B. B$ B$ B$ B$ vh vh B- vn I" vd vr B$ B$ vc B% B+ vd I" I% vr B. B. B$ B$ B$ B$ vh vh B- vn I" vd vr B$ B$ vc B% B+ vd I# I% vr B$ B$ B$ B$ vh vh B- vn I" B% B+ I# vd I% U! vr I) I! F Ld Lr BT I" BD vd ? vr S>LOF SL>FO


(defun hilbert (level)
  (labels ((h (n x y dx dy)
              (when (> n 0)
                (h (- n 1) x y dy dx)
                (setq x (+ x dx) y (+ y dy))
                (format t "~A ~A~%" x y)
                (h (- n 1) x y dx dy)
                (setq x (+ x dy) y (+ y dx))
                (format t "~A ~A~%" x y)
                (h (- n 1) x y dx dy)
                (setq x (- x dx) y (- y dy))
                (format t "~A ~A~%" x y)
                (h (- n 1) x y (- dy) (- dx)))))
    (h level 0 0 1 0)))

(hilbert 3)
