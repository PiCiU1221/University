#include <stdio.h>
#include <cstdint>

void kolos1() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 3;
			unsigned char b : 2;
			unsigned char c : 3;
		}bits;
	}un_X;

	un_X x;

	x.bits.a = 2;
	x.bits.b = 0;
	x.bits.c = 3;

	printf("przed:\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	while (x.bits.c < 4) x.bits.c = 3 * x.bits.a++;

	printf("\nw C po:\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	x.bits.a = 2;
	x.bits.b = 0;
	x.bits.c = 3;

	__asm {
		XOR AL, AL
		XOR BL, BL
		XOR CL, CL
		XOR DL, DL

		MOV AL, x.BYTE
		AND AL, 0xE0
		SHR AL, 5

		MOV BL, x.BYTE
		AND BL, 0x07 // a w bl
		MOV CL, BL // oryginalne a w cl

		MOV DL, AL
		SUB DL, 0x04

		JZ KONIEC

		KONTYNUUJ :

		MOV DL, 0x03

			MNOZENIE :

			ADD BL, CL
			SUB DL, 0x01
			JNC MNOZENIE

			AND BL, 0x07

			MOV AL, BL // c = 3 * a
			ADD BL, 0x01 // a++
			AND BL, 0x07

			MOV DL, AL // kopia c do dl
			SUB DL, 4

			JNC KONTYNUUJ

			KONIEC :
		MOV CL, x.BYTE
			AND CL, 0x18

			SHL AL, 5
			OR CL, AL
			OR CL, BL

			MOV x.BYTE, CL
	}

	printf("\nw asseblerze\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);
}

void kolos2(uint8_t a) {
	uint8_t y = 0x00;

	__asm {
		MOV AL, 0
		MOV BL, 0

		MOV AL, a
		AND AL, 0x11
		SHL AL, 3

		OR BL, AL

		MOV AL, a
		AND AL, 0x22
		SHL AL, 1

		OR BL, AL

		MOV AL, a
		AND AL, 0x44
		SHR AL, 1

		OR BL, AL

		MOV AL, a
		AND AL, 0x88
		SHR AL, 3

		OR BL, AL

		MOV y, BL
	}

	printf("Wynik: %#x\n", y);
}

void kolos3() {
	uint8_t a = 0x2B;
	uint16_t b = 0x00;

	if (a <= 42) {
		b = 13 * a;
	}
	else {
		b = 4 * a + 8;
	}

	printf("Wynik: %d\n", b);

	b = 0;

	__asm {
		MOV CX, 0
		MOV AL, a

		CMP AL, 42
		JA ELSE

		MOV BL, 13

		LOOP1:
		ADD CX, AX
			SUB BL, 1
			JNZ LOOP1
			JZ KONIEC

			ELSE :
		MOV BL, 4

			LOOPELSE :
			ADD CX, AX
			SUB BL, 1
			JNZ LOOPELSE

			ADD CX, 8

			KONIEC :
			MOV b, CX
	}

	printf("Wynik: %d\n", b);
}

void kolos4() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 3;
			unsigned char b : 3;
			unsigned char c : 2;
		}bits;
	}un_X;

	un_X x;

	x.bits.a = 6;
	x.bits.b = 4;
	x.bits.c = 2;

	printf("przed:\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	while (x.bits.b & x.bits.a) x.bits.c ^= x.bits.b++;

	printf("\nw C po:\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	x.bits.a = 6;
	x.bits.b = 4;
	x.bits.c = 2;

	__asm {
		MOV AL, x.BYTE
		AND AL, 0x07

		MAINLOOP:

		MOV BL, x.BYTE
			AND BL, 0x38
			SHR BL, 3

			AND BL, AL
			JZ KONIEC

			MOV BL, x.BYTE
			AND BL, 0x38
			SHR BL, 3

			MOV CL, x.BYTE
			AND CL, 0xC0
			SHR CL, 6

			XOR CL, BL
			ADD BL, 1
			AND BL, 0x07

			SHL BL, 3
			SHL CL, 6

			MOV DL, x.BYTE
			AND DL, 0x07

			OR DL, BL
			OR DL, CL
			MOV x.BYTE, DL

			JMP MAINLOOP

			KONIEC :
	}

	printf("\nw asseblerze\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);
}

void zadanie1a() {
	uint8_t a = 15;
	uint16_t y = 0;

	y = a * 20;

	printf("Wynik: %d \n", y);

	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX

		MOV AL, a
		SHL AX, 4
		MOV BL, a
		SHL BX, 2

		ADD AX, BX
		MOV y, AX
	}

	printf("Wynik: %d \n", y);
}

void zadanie1c() {
	uint8_t a = 15;
	uint16_t y = 0;

	y = a * 20;

	printf("Wynik: %d \n", y);

	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV AL, a
		MOV CL, a

		MOV BL, 20

		PETLA:
		ADD BL, -1
			JZ KONIEC
			ADD AX, CX
			JNZ PETLA

			KONIEC :
		MOV y, AX
	}

	printf("Wynik: %d \n", y);
}

void zadanie2a() {
	uint8_t a = 0x33;
	uint8_t y = 0;

	if (a == 0x32) {
		y = 0;
	}
	else {
		y = 1;
	}

	printf("Wynik: %d \n", y);

	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV AL, a
		SUB AL, 0x32
		JZ KONIEC

		MOV y, 1

		KONIEC:
	}

	printf("Wynik: %d \n", y);
}

void zadanie2b() {
	uint8_t a = 0x31;
	uint8_t y = 0;

	if (a == 0x32) {
		y = 0;
	}
	else {
		y = 1;
	}

	printf("Wynik: %d \n", y);

	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV AL, a
		CMP AL, 0x32
		JZ KONIEC

		MOV y, 1

		KONIEC:
	}

	printf("Wynik: %d \n", y);
}

void zadanie2c() {
	uint8_t a = 0x32;
	uint8_t y = 0;

	if (a == 0x32) {
		y = 0;
	}
	else {
		y = 1;
	}

	printf("Wynik: %d \n", y);

	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV AL, a
		ADD AL, -0x32
		JZ KONIEC

		MOV y, 1

		KONIEC:
	}

	printf("Wynik: %d \n", y);
}

void zadanie4a() {
	uint32_t i = 0;
	uint32_t y = 0;

	for (int i = 0; i != 5; i++) {
		y += i;
	}

	printf("Wynik: %d \n", y);

	i = 0;
	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		PETLA :
		MOV CL, BL
			SUB CL, 5
			JZ KONIEC
			ADD AL, BL
			ADD BL, 1
			JMP PETLA

			KONIEC :
		MOV y, EAX
	}

	printf("Wynik: %d \n", y);
}

void zadanie4c() {
	uint32_t i = 0;
	uint32_t y = 0;

	for (int i = 5; i != 0; i--) {
		y -= i;
	}

	printf("Wynik: %d \n", y);

	i = 0;
	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV BL, 5

		PETLA :
		MOV CL, BL
			CMP CL, 0
			JZ KONIEC
			SUB AX, BX
			SUB BX, 1
			JMP PETLA

			KONIEC :
		MOV y, EAX
	}

	printf("Wynik: %d \n", y);
}

void zadanie4b() {
	uint32_t i = 0;
	uint32_t y = 0;

	for (int i = 0; i != 5; i++) {
		y += i;
	}

	printf("Wynik: %d \n", y);

	i = 0;
	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		PETLA :
		MOV CL, BL
			CMP CL, 5
			JZ KONIEC
			ADD AL, BL
			ADD BL, 1
			JMP PETLA

			KONIEC :
		MOV y, EAX
	}

	printf("Wynik: %d \n", y);
}

void zadanie5a() {
	uint32_t y = 0;

	while (y != 5) y += 1;

	printf("Wynik: %d \n", y);

	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV EAX, y
		MOV BX, AX
		SUB BX, 5
		JZ KONIEC

		PETLA :
		ADD AX, 1
			MOV BX, AX
			SUB BX, 5
			JNZ PETLA

			KONIEC :
		MOV y, EAX
	}

	printf("Wynik: %d \n", y);
}

void zadanie5b() {
	uint32_t y = 0;

	while (y != 5) y += 1;

	printf("Wynik: %d \n", y);

	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV EAX, y
		MOV BX, AX
		SUB BX, 5
		JZ KONIEC

		PETLA :
		ADD AX, 1
			MOV BX, AX
			CMP BX, 5
			JNZ PETLA

			KONIEC :
		MOV y, EAX
	}

	printf("Wynik: %d \n", y);
}

void zadanie6b() {
	uint8_t a = 0x80;
	uint8_t y = 8;
	char temp = 0;

	for (int i = 0; i < 8; i++) {
		temp = a & 0x01;
		y -= temp;
		a = a >> 1;
	}

	printf("Wynik: %d \n", y);

	a = 0x80;
	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV CL, 8
		MOV AL, a
		MOV DL, 8

		PETLA:
		MOV BL, AL
			AND BL, 0x01
			SUB CL, BL
			SHR AL, 1
			SUB DL, 1
			JNZ PETLA

			MOV y, CL
	}

	printf("Wynik: %d \n", y);
}

void zadanie7() {
	uint8_t a = 0x88;
	uint8_t y = 8;
	char temp = 0;

	for (int i = 0; i < 8; i++) {
		temp = a & 0x01;
		y -= temp;
		a = a >> 1;
	}

	temp = 1 - (y & 0x01);
	y = temp;

	printf("Wynik: %d \n", y);

	a = 0x88;
	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV CL, 8
		MOV AL, a
		MOV DL, 8

		PETLA:
		MOV BL, AL
			AND BL, 0x01
			SUB CL, BL
			SHR AL, 1
			SUB DL, 1
			JNZ PETLA

			MOV DL, CL
			AND DL, 0x01
			MOV CL, 1
			SUB CL, DL
			MOV y, CL
	}

	printf("Wynik: %d \n", y);
}

void zadanie8a() {
	uint8_t a = 0xAA;
	uint8_t holder = 0, helper = 0;

	for (int i = 0; i < 8; i++) {
		helper = a & 0x01;
		holder = holder << 1;
		holder = holder | helper;
		a = a >> 1;
	}

	a = holder;

	printf("Wynik: %#x \n", a);

	a = 0xAA;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX

		MOV AL, a
		AND AL, 0xF0
		SHR AL, 4

		MOV BL, a
		AND BL, 0x0F
		SHL BL, 4

		OR AL, BL
		MOV a, AL

		MOV AL, a
		AND AL, 0xCC
		SHR AL, 2

		MOV BL, a
		AND BL, 0x33
		SHL BL, 2

		OR AL, BL
		MOV a, AL

		MOV AL, a
		AND AL, 0xAA
		SHR AL, 1

		MOV BL, a
		AND BL, 0x55
		SHL BL, 1

		OR AL, BL
		MOV a, AL
	}

	printf("Wynik: %#x \n", a);
}

void zadanie9() {
	uint8_t a = 10;
	uint8_t b = 10;
	uint8_t holder = 0;
	uint16_t y = 0;

	for (int i = 0; i < 8; i++) {
		holder = b & 0x01;
		if (holder == 1) {
			y += a << i;
		}
		b = b >> 1;
	}

	printf("Wynik: %d \n", y);

	a = 10;
	b = 10;
	y = 0;

	__asm {
		XOR EAX, EAX
		XOR EBX, EBX
		XOR ECX, ECX
		XOR EDX, EDX

		MOV AL, a

		PETLA :
		MOV BL, b
			AND BL, 0x01
			TEST BL, 1
			JNZ ZERO

			MOV y, CX
			MOV CL, DL
			SHL AL, CL
			MOV CX, y
			ADD CX, AX

			ZERO :
		MOV BL, b
			SHR BL, 1
			MOV b, BL
			ADD DL, 1
			CMP DL, 8
			JNZ PETLA

			MOV y, CX
	}

	printf("Wynik: %d \n", y);
}

void zadanie13() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 2;
			unsigned char b : 3;
			unsigned char c : 3;
		}bits;
	}un_X;

	un_X x;

	x.bits.a = 1;
	x.bits.b = 3;
	x.bits.c = 1;

	printf("\nprzed\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	if (x.bits.c == 1) x.bits.a = x.bits.b;

	printf("\nw c\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	x.bits.a = 1;
	x.bits.b = 3;
	x.bits.c = 1;

	__asm {
		MOV CL, x.BYTE
		MOV BL, CL

		AND CL, 0xE0
		SHR CL, 5
		SUB CL, 1
		JNZ KONIEC

		AND BL, 0x1C
		SHR BL, 2

		AND BL, 0x03
		MOV AL, x.BYTE
		AND AL, 0xFC
		OR AL, BL

		MOV x.BYTE, AL

		KONIEC :
	}

	printf("\nw asseblerze\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);
}

void zadanie14() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 1;
			unsigned char b : 3;
			unsigned char c : 4;
		}bits;
	}un_X;

	un_X x;

	x.bits.a = 1;
	x.bits.b = 5;
	x.bits.c = 3;

	printf("\nprzed\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	x.bits.c = x.bits.a * x.bits.b;

	printf("\nw c\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	x.bits.a = 1;
	x.bits.b = 5;
	x.bits.c = 3;

	__asm {
		MOV AL, x.BYTE
		MOV BL, AL
		AND AL, 0x01
		AND BL, 0x0E
		SHR BL, 1

		SUB AL, 1
		JZ PRZYPIS

		MOV BL, 0

		PRZYPIS:
		SHL BL, 4

			MOV CL, x.BYTE
			AND CL, 0x0F
			OR CL, BL

			MOV x.BYTE, CL
	}

	printf("\nw asseblerze\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);
}

void kolos10() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 3;
			unsigned char b : 3;
			unsigned char c : 2;
		}bits;
	}un_X;

	un_X x;

	x.bits.a = 2;
	x.bits.b = 2;
	x.bits.c = 3;

	printf("\nprzed\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	while (x.bits.b & x.bits.a) x.bits.c ^= x.bits.b++;

	printf("\nw c\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);

	x.bits.a = 2;
	x.bits.b = 2;
	x.bits.c = 3;

	__asm {
		XOR AL, AL
		XOR BL, BL
		XOR CL, CL

		MOV AL, x.BYTE
		MOV BL, AL
		MOV CL, AL

		AND AL, 0x07
		AND BL, 0x38
		SHR BL, 3
		AND CL, 0xC0
		SHR CL, 6

		PETLAWHILE:
		MOV DL, BL
			AND DL, AL
			JZ KONIEC

			MOV DL, BL
			AND DL, 0x03
			XOR CL, BL
			ADD BL, 1

			JNC PETLAWHILE

			KONIEC :
		SHL BL, 3
			SHL CL, 6

			MOV DL, AL
			OR DL, BL
			OR DL, CL

			MOV x.BYTE, DL
	}

	printf("\nw asseblerze\n");
	printf("BYTE : %#x \n", x.BYTE);
	printf("bits.a : a: %#x\n", x.bits.a);
	printf("bits.b : b: %#x\n", x.bits.b);
	printf("bits.c : c: %#x\n", x.bits.c);
}

void kolos11() {
	typedef union {
		unsigned char BYTE;
		struct {
			unsigned char a : 3;
			unsigned char b : 2;
			unsigned char c : 3;
		}bits;
	}un_X;

	un_X x;

	x.bits.a = 4;
	x.bits.b = 2;
	x.bits.c = 3;

	printf("PRZED:\n");
	printf("x.bits.a = %d\n", x.bits.a);
	printf("x.bits.b = %d\n", x.bits.b);
	printf("x.bits.c = %d\n", x.bits.c);

	while (x.bits.c < 4) x.bits.c = 3 * x.bits.a++;

	printf("C PO:\n");
	printf("x.bits.a = %d\n", x.bits.a);
	printf("x.bits.b = %d\n", x.bits.b);
	printf("x.bits.c = %d\n", x.bits.c);

	x.bits.a = 4;
	x.bits.b = 2;
	x.bits.c = 3;

	__asm {
		MOV AL, x.BYTE
		AND AL, 0x07
		MOV CL, AL
		AND CL, 0xE0
		SHR CL, 5

		PETLAWHILE:
		MOV DL, CL
			SHR DL, 2
			SUB DL, 1
			JZ KONIEC

			MOV DL, AL
			OR DL, AL
			OR DL, AL
			OR AL, 1

			AND AL, 0x07
			AND DL, 0x07

			MOV CL, DL
			JNC PETLAWHILE

			KONIEC :
		MOV DL, x.BYTE
			AND DL, 0x18
			SHL CL, 5
			OR DL, AL
			OR DL, CL

			MOV x.BYTE, DL
	}

	printf("ASM PO:\n");
	printf("x.bits.a = %d\n", x.bits.a);
	printf("x.bits.b = %d\n", x.bits.b);
	printf("x.bits.c = %d\n", x.bits.c);
}

void zadanie12() {
	uint8_t y = 0;

	for (int i = 0; i < 5; i++) y += i;

	printf("WYNIK: %d\n", y);

	y = 0;

	__asm {
		MOV CL, 0
		MOV AL, 0

		PETLA:
		ADD AL, CL

			ADD CL, 1
			MOV DL, CL
			SUB DL, 5
			JC PETLA

			MOV y, AL
	}

	printf("WYNIK: %d\n", y);
}

void zadanie11() {
	uint8_t y = 0, a = 4;

	if (a < 0x05) {
		y = 0;
	}
	else {
		y = 1;
	}

	printf("WYNIK: %d\n", y);

	y = 0;

	__asm {
		MOV AL, a
		SUB AL, 0x05
		JNC ELSE
		MOV y, 0
		JMP KONIEC

		ELSE :
		MOV y, 1
			KONIEC :
	}

	printf("WYNIK: %d\n", y);
}

void zadanie9a() {
	uint8_t a = 20, b = 20;
	uint16_t y = 0;

	y = a * b;

	printf("WYNIK: %d\n", y);

	y = 0;

	__asm {
		XOR AL, AL
		XOR BL, BL
		XOR CL, CL
		XOR DL, DL

		MOV CL, 0
		MOV BL, b

		PETLA :
		MOV AL, a
			MOV DL, BL
			AND DL, 0x01
			SUB DL, 1
			JNZ DALEJ

			SHL AX, CL
			MOV DX, y
			ADD DX, AX
			MOV y, DX

			DALEJ :

		ADD CL, 1
			MOV DL, CL
			SUB DL, 7
			SHR BL, 1
			JNZ PETLA
	}

	printf("WYNIK: %d\n", y);
}

int main()
{
	//kolos1();

	//kolos2(0x2c);
	//kolos2(0xb5);

	//kolos3();

	//kolos4();

	//zadanie1a();

	//zadanie1c();

	//zadanie2a();

	//zadanie2b();

	//zadanie2c();

	//zadanie4a();

	//zadanie4b();

	//zadanie4c();

	//zadanie5a();

	//zadanie5b();

	//zadanie6b();

	//zadanie7();

	//zadanie8a();

	//zadanie9();

	//zadanie13();

	//zadanie14();

	//kolos10();

	//kolos11();

	//zadanie12();

	//zadanie11();

	zadanie9a();
}