#include<stdio.h>

typedef union {
    float v;
    struct {
        unsigned F : 23;
        unsigned E : 8;
        unsigned S : 1;
    };
}Float;

Float FADD0(Float A, Float B)
{
    Float R;
    unsigned Ea, Eb, E;
    unsigned long Fb, Fb1, Fa;
    unsigned long Fa1, Fb2, F;
    int d;
    R.S = A.S;
    Ea = A.E;
    Eb = B.E;
    d = Ea - Eb;
    Fb = B.F | 0x800000;
    Fb1 = Fb >> d;
    Fa = A.F | 0x800000;
    Fa1 = (A.S) ? (~Fa + 1) : Fa;
    Fb2 = (B.S) ? (~Fb1 + 1) : Fb1;
    F = Fa1 + Fb2;
    if (F & 0x2000000) {
        R.S = 1;
        F = ~F + 1;
    }
    else {
        R.S = 0;
    }
    if (F & 0x1000000) {
        E = Ea + 1;
        F = F >> 1;
    }
    else {
        E = Ea;
        while (E > 0 && ((F & 0x800000) == 0)) {
            E = E - 1;
            F = F << 1;
        }
        if (E == 0)F = 0;
    }
    R.F = F;
    R.E = E;
    return R;
}
Float FADD(Float A, Float B)
{
    Float R;
    if (A.E < B.E) {
        R = FADD0(B, A);
    }
    else {
        R = FADD0(A, B);
    }
    return R;
}

int main()
{
    Float A, B, C;
    A.v = -2.5;
    B.v = -2.5;
    C = FADD(A, B);
    printf("%f+%f=%f\n", A.v, B.v, C.v);

    return 0;
}