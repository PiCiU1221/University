// pp53828
// WT/220A

#include <iostream>

void zamianaKolejnosciBitowWBajcie() {
    uint8_t a1, a2;
    uint8_t helper1 = 0, helper2 = 0;

    a1 = a2 = 0xF0;

    helper1 = a1 & 0xF0;
    helper2 = a1 & 0x0F;
    helper1 >>= 4;
    helper2 <<= 4;

    a1 = 0;
    a1 |= helper1;
    a1 |= helper2;

    helper1 = a1 & 0xCC;
    helper2 = a1 & 0x33;
    helper1 >>= 2;
    helper2 <<= 2;

    a1 = 0;
    a1 |= helper1;
    a1 |= helper2;

    helper1 = a1 & 0xAA;
    helper2 = a1 & 0x55;
    helper1 >>= 1;
    helper2 <<= 1;

    a1 = 0;
    a1 |= helper1;
    a1 |= helper2;

    printf("Zadanie 1:\n");
    printf("Wynik w C: %d\n", a1);

    __asm {
        XOR EAX, EAX
        XOR EBX, EBX
        XOR EDX, EDX

        MOV AL, a2

        MOV BL, AL
        MOV DL, AL
        AND BL, 0xF0
        AND DL, 0x0F
        SHR BL, 4
        SHL DL, 4

        MOV AL, 0
        OR AL, BL
        OR AL, DL

        MOV BL, AL
        MOV DL, AL
        AND BL, 0xCC
        AND DL, 0x33
        SHR BL, 2
        SHL DL, 2

        MOV AL, 0
        OR AL, BL
        OR AL, DL


        MOV BL, AL
        MOV DL, AL
        AND BL, 0xAA
        AND DL, 0x55
        SHR BL, 1
        SHL DL, 1

        MOV AL, 0
        OR AL, BL
        OR AL, DL

        MOV a2, AL
    }

    printf("Wynik w ASM: %d\n\n", a2);
}

void petlaForWAsm() {
    uint32_t i = 0, y = 0;

    for (int i = 0; i != 0xA; i++) y += 1;

    printf("Zadanie 2:\n");
    printf("Wynik w C: %d\n", y);

    y = 0;

    __asm {
        XOR EAX, EAX
        XOR ECX, ECX

        PETLA:
        ADD EAX, 1

        ADD ECX, 1
        CMP ECX, 0xA
        JNZ PETLA

        MOV y, EAX
    }

    printf("Wynik w ASM: %d\n", y);
}

int main()
{
    zamianaKolejnosciBitowWBajcie();

    petlaForWAsm();
    
    return 0;
}