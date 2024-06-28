(define-obsolete-function-alias 'string-to-int 'string-to-number "22.1")
(add-to-list 'load-path "./site-lisp/bigint/")
(add-to-list 'load-path "./site-lisp/s")
(require 's)
(require 'bigint)
(defun T () t)
(defun F () nil)
(defmacro take (len s) (s-left  len s))
(defmacro drop (len s) (s-right len s))
(funcall (funcall (lambda (var0)
(funcall (lambda (var1)
(funcall var0
 (funcall var1
 var1
 )))
         (lambda (var1)
      (funcall var0
               (funcall var1
                        var1)))))
                  (lambda (var2)
(lambda (var3)
(funcall (lambda (var0)
(funcall (lambda (var1)
(funcall (lambda (var4)
(funcall (lambda (var5)
(funcall (lambda (var6)
(funcall (lambda (var7)
(funcall (lambda (var8)
(funcall (lambda (var9)
(funcall (lambda (var10)
(funcall (lambda (var11)
(funcall (lambda (var12)
(funcall (lambda (var13)
(funcall (lambda (var14)
(funcall (lambda (var15)
(funcall (lambda (var16)
(funcall (lambda (var17)
(funcall (lambda (var18)
(funcall (lambda (var19)
(funcall (lambda (var20)
(funcall (lambda (var21)
(funcall (lambda (var22)
(funcall (lambda (var23)
(funcall (lambda (var24)
(funcall (lambda (var25)
(funcall (lambda (var26)
(funcall (lambda (var27)
(funcall (lambda (var28)
(funcall (lambda (var29)
(funcall (lambda (var30)
(funcall (lambda (var31)
(funcall (lambda (var32)
(funcall (lambda (var33)
(funcall (lambda (var34)
(funcall (lambda (var35)
(funcall (lambda (var36)
(funcall (lambda (var37)
(funcall (lambda (var38)
(funcall (lambda (var39)
(funcall (lambda (var40)
(funcall (lambda (var41)
(if (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (or (not var19
) (not var16
)) (or (not var15
) (not var10
))) (or (or (not var20
) var38
) var13
)) (not var40
)) (or (not var21
) var19
)) (or (or (not var9
) var17
) (not var25
))) (or (not var30
) (not var40
))) (or (not var1
) var20
)) var16
) (or (or (not var38
) var20
) (not var7
))) (or var26
 (not var24
))) (or (or (not var18
) var41
) var22
)) (or (or (not var24
) var36
) var25
)) (or (not var31
) (not var29
))) var16
) (or (or (not var38
) var20
) var7
)) (or (not var4
) (not var12
))) (or (not var36
) (not var4
))) (or (or (not var30
) var40
) var23
)) (or (not var28
) (not var11
))) (or var29
 (not var9
))) (or (not var5
) var40
)) (or var11
 var27
)) (or (or var23
 var15
) var16
)) (not var14
)) (or (or var37
 var29
) (not var36
))) (or (or (not var9
) var17
) var25
)) (or (or (not var8
) var4
) (not var41
))) (or (or var23
 var15
) var16
)) (not var14
)) (or (or (not var9
) var17
) var25
)) (or (or (not var20
) var38
) var13
)) (or var11
 (not var27
))) (or (not var21
) (not var19
))) (or (not var9
) (not var17
))) (or (or (not var4
) var12
) (not var24
))) (or (not var17
) var38
)) (or (not var39
) (not var12
))) (or (or (not var32
) var14
) var15
)) (or (not var34
) var20
)) (or (or (not var15
) var10
) (not var30
))) (or var7
 var17
)) (or (or var37
 var29
) var36
)) (or (not var20
) (not var38
))) (or (not var6
) var7
)) (or var11
 var27
)) (or (or (not var4
) var12
) var24
)) (or (or var27
 var38
) (not var17
))) (or (or var23
 var15
) (not var16
))) (or (or var26
 var24
) var39
)) (or var37
 (not var29
))) (or (not var36
) var4
)) (or (or (not var35
) var36
) (not var38
))) (or (not var6
) (not var7
))) (or (not var34
) (not var20
))) (or (or (not var18
) var41
) var22
)) (or (or (not var31
) var29
) var5
)) (or (or (not var35
) var36
) var38
)) (or (or var29
 var9
) var30
)) (not var22
)) (or (or (not var19
) var16
) var40
)) var41
) (or (or (not var4
) var12
) var24
)) (or (not var18
) (not var41
))) (or (not var36
) var4
)) (or (not var34
) var20
)) (or (or var26
 var24
) (not var39
))) (or (not var28
) var11
)) (or (or var37
 var29
) var36
)) (or (or (not var8
) var4
) var41
)) (or (not var12
) var36
)) (or var7
 var17
)) (or (or (not var31
) var29
) var5
)) (or (not var12
) (not var36
))) (or (not var33
) var20
)) (or (not var38
) (not var20
))) (or var27
 (not var38
))) (or (or (not var31
) var29
) (not var5
))) (not var22
)) (or (not var21
) var19
)) (or (not var10
) var32
)) (or (or var29
 var9
) var30
)) (or (or (not var32
) var14
) (not var15
))) (or (or (not var25
) var33
) var36
)) (or var13
 var17
)) (or (or (not var30
) var40
) var23
)) (or (or (not var15
) var10
) var30
)) (not var40
)) (or (not var5
) (not var40
))) (or (or (not var38
) var20
) var7
)) (or (not var24
) (not var36
))) (or (or (not var30
) var40
) (not var23
))) (or (not var6
) var7
)) var41
) (or (or var26
 var24
) var39
)) (or (not var1
) var20
)) (or var13
 var17
)) (or (or (not var24
) var36
) var25
)) (or (not var32
) (not var14
))) (or (not var35
) (not var36
))) (or (not var33
) var20
)) (or (or (not var25
) var33
) var36
)) (or (or var27
 var38
) var17
)) (or (not var39
) var12
)) (or (not var17
) var38
)) (or (or (not var8
) var4
) var41
)) (or (not var5
) var40
)) (or (not var8
) (not var4
))) (or (or (not var25
) var33
) (not var36
))) (or (or (not var35
) var36
) var38
)) (or (not var12
) var36
)) var0
) (or (not var28
) var11
)) (or (or (not var24
) var36
) (not var25
))) (or (or (not var19
) var16
) (not var40
))) (or (or (not var20
) var38
) (not var13
))) (or (or var27
 var38
) var17
)) (or var7
 (not var17
))) (or (or (not var18
) var41
) (not var22
))) (or (not var10
) (not var32
))) (or (not var33
) (not var20
))) (or (not var39
) var12
)) (or (not var10
) var32
)) (or (or (not var15
) var10
) var30
)) (or (or (not var19
) var16
) var40
)) (or var13
 (not var17
))) (or (not var17
) (not var38
))) (or var23
 (not var15
))) (or (or var29
 var9
) (not var30
))) var0
) (or (not var25
) (not var33
))) (or (not var1
) (not var20
))) (or (or (not var32
) var14
) var15
))
var3

(funcall var2
 (+ var3
 1
)))) (< 0
 (% (/ var3
 549755813888
) 2
)))) (< 0
 (% (/ var3
 274877906944
) 2
)))) (< 0
 (% (/ var3
 137438953472
) 2
)))) (< 0
 (% (/ var3
 68719476736
) 2
)))) (< 0
 (% (/ var3
 34359738368
) 2
)))) (< 0
 (% (/ var3
 17179869184
) 2
)))) (< 0
 (% (/ var3
 8589934592
) 2
)))) (< 0
 (% (/ var3
 4294967296
) 2
)))) (< 0
 (% (/ var3
 2147483648
) 2
)))) (< 0
 (% (/ var3
 1073741824
) 2
)))) (< 0
 (% (/ var3
 536870912
) 2
)))) (< 0
 (% (/ var3
 268435456
) 2
)))) (< 0
 (% (/ var3
 134217728
) 2
)))) (< 0
 (% (/ var3
 67108864
) 2
)))) (< 0
 (% (/ var3
 33554432
) 2
)))) (< 0
 (% (/ var3
 16777216
) 2
)))) (< 0
 (% (/ var3
 8388608
) 2
)))) (< 0
 (% (/ var3
 4194304
) 2
)))) (< 0
 (% (/ var3
 2097152
) 2
)))) (< 0
 (% (/ var3
 1048576
) 2
)))) (< 0
 (% (/ var3
 524288
) 2
)))) (< 0
 (% (/ var3
 262144
) 2
)))) (< 0
 (% (/ var3
 131072
) 2
)))) (< 0
 (% (/ var3
 65536
) 2
)))) (< 0
 (% (/ var3
 32768
) 2
)))) (< 0
 (% (/ var3
 16384
) 2
)))) (< 0
 (% (/ var3
 8192
) 2
)))) (< 0
 (% (/ var3
 4096
) 2
)))) (< 0
 (% (/ var3
 2048
) 2
)))) (< 0
 (% (/ var3
 1024
) 2
)))) (< 0
 (% (/ var3
 512
) 2
)))) (< 0
 (% (/ var3
 256
) 2
)))) (< 0
 (% (/ var3
 128
) 2
)))) (< 0
 (% (/ var3
 64
) 2
)))) (< 0
 (% (/ var3
 32
) 2
)))) (< 0
 (% (/ var3
 16
) 2
)))) (< 0
 (% (/ var3
 8
) 2
)))) (< 0
 (% (/ var3
 4
) 2
)))) (< 0
 (% (/ var3
 2
) 2
)))) (< 0
 (% (/ var3
 1
) 2
)))))) 1)
