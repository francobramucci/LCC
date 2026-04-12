.global det2x2 

det2x2:
    @ s0 -> a, s1 -> b, s2 -> c, s3 -> d
    @ det(a b c d) = a * d - b * c

    vmul.f32 s0, s1, s3
    vmul.f32 s1, s1, s2
    vsub.f32 s0, s0, s1

    bx lr


