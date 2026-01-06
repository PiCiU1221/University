.data

    literal_0: .asciiz "Testy dynamicznych tablic"
    literal_1: .asciiz "Wynikami powinny byc 11, 12, 13"
    n: .word 20
    result2: .word 0
    result3: .word 0
    test1: .word 0
    test2: .word 0
    test3: .word 0
    x: .word 0
    y: .word 0

.text

    li $v0, 9
    li $a0, 10
    syscall
    sw $v0, x

    li $v0, 9
    lw $a0, n
    syscall
    sw $v0, y

    la $a0, literal_0
    li $v0, 4
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    la $a0, literal_1
    li $v0, 4
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    li $t6, 6

    li $t7, 1

    add $t2, $t6, $t7

    sw $t2, result2

    la $t4, x
    li $t5, 0
    lw $t0, result2
    li $t1, 4
    mul $t0, $t0, $t1
    add $t5, $t5, $t0
    add $t4, $t4, $t5
    li $t0, 11
    sw $t0, ($t4)

    la $t4, y
    li $t5, 0
    li $t0, 11
    li $t1, 4
    mul $t0, $t0, $t1
    add $t5, $t5, $t0
    add $t4, $t4, $t5
    li $t0, 12
    sw $t0, ($t4)

    la $t4, x
    li $t5, 0
    li $t0, 7
    li $t1, 4
    mul $t0, $t0, $t1
    add $t5, $t5, $t0
    add $t4, $t4, $t5
    lw $t0, ($t4)
    sw $t0, test1

    la $t4, y
    li $t5, 0
    li $t0, 11
    li $t1, 4
    mul $t0, $t0, $t1
    add $t5, $t5, $t0
    add $t4, $t4, $t5
    lw $t0, ($t4)
    sw $t0, test2

    lw $a0, test1
    li $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    lw $a0, test2
    li $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    la $t4, x
    li $t5, 0
    li $t0, 1
    li $t1, 4
    mul $t0, $t0, $t1
    add $t5, $t5, $t0
    add $t4, $t4, $t5
    li $t0, 9
    sw $t0, ($t4)

    la $t4, y
    li $t5, 0
    li $t0, 2
    li $t1, 4
    mul $t0, $t0, $t1
    add $t5, $t5, $t0
    add $t4, $t4, $t5
    li $t0, 4
    sw $t0, ($t4)

    la $t4, x
    li $t5, 0
    li $t0, 1
    li $t1, 4
    mul $t0, $t0, $t1
    add $t5, $t5, $t0
    add $t4, $t4, $t5
    lw $t6, ($t4)

    la $t4, y
    li $t5, 0
    li $t0, 2
    li $t1, 4
    mul $t0, $t0, $t1
    add $t5, $t5, $t0
    add $t4, $t4, $t5
    lw $t7, ($t4)

    add $t2, $t6, $t7

    sw $t2, result3

    lw $t0, result3
    sw $t0, test3
    lw $a0, test3
    li $v0, 1
    syscall
    li $a0, '\n'
    li $v0, 11
    syscall

    li $v0, 10
    syscall
