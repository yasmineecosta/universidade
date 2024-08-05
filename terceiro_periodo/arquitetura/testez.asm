.data
WIDTH:      .word 128
HEIGHT:     .word 96
FILTER_SIZE: .word 3
image: .byte 197,199,199,199,199,200,202,205,202,205,205,203,203,204,203,200,201,198,195,195,198,200,202,202,199,198,198,199,201,202,202,202,203,203,202,201,200,201,201,201,199,199,199,200,200,200,200,200,201,202,202,202,201,201,202,202,201,201,201,203,204,205,205,204,201,202,202,201,200,200,199,196,194,198,197,195,198,204,206,203,201,201,203,201,195,195,198,201,200,202,203,201,200,204,206,206,202,206,206,204,202,202,199,195,194,194,195,195,196,197,198,199,196,197,198,199,199,200,201,203,210,211,211,212,212,210,207,205,195,198,201,202,201,201,204,206,204,206,205,202,201,202,202,200,201,199,196,195,196,198,199,200,200,200,200,200,201,202,201,200,202,202,201,201,200,201,201,202,203,202,202,201,200,200,199,199,202,203,203,203,202,201,202,202,207,206,206,206,206,205,204,202,198,200,202,201,200,200,197,194,198,183,192
imageCopy: .space 1024
#image: .space 1024

.text
.globl applyMedianFilter
.globl main

applyMedianFilter:
    # Aloca espaço para as variáveis locais
    la $s3, FILTER_SIZE
    mul $s3, $s3, $s3
    #mflo $s3
    sll $s3, $s3, 2 #4*FILTER_SIZE*FILTER_SIZE
    subu $sp, $sp, $s3
    sw $ra, 0($sp)          # Salva o endereço de retorno
    sw $fp, 4($sp)          # Salva o ponteiro de frame

    # Criação do loop externo (i)
    li $t0, 0               # i = 0
    loop_i:
        lw $t2, HEIGHT        # Obtém o valor de HEIGHT
        bge $t0, $t2, end_apply_median_filter  # Se i >= HEIGHT, termina
        li $t1, 0           # j = 0

        # Criação do loop interno (j)
        loop_j:
            lw $t3, WIDTH       # Obtém o valor de WIDTH
            bge $t1, $t3, next_row  # Se j >= WIDTH, passa para a próxima linha
            la $t4, imageCopy     # Endereço base de imageCopy
            lw $t5, HEIGHT($t4)    # Obtém a altura da matriz

            # Cópia de image para imageCopy
            mul $t6, $t1, $t5      # Calcula a posição atual em imageCopy
            add $t6, $t6, $t0
            sll $t6, $t6, 2        # Multiplica por 4 (tamanho de uma palavra)
            add $t6, $t6, $t4      # Adiciona ao endereço base

            lw $t7, image($t6)    # Obtém o valor de image[i][j]
            sw $t7, 0($t6)         # Armazena em imageCopy[i][j]

            # Restante do loop interno
            addi $t1, $t1, 1       # Incrementa j
            j loop_j

        next_row:
        addi $t0, $t0, 1           # Incrementa i
        j loop_i

    end_apply_median_filter:

    # Libera o espaço alocado para variáveis locais
    lw $ra, 0($sp)          # Restaura o endereço de retorno
    lw $fp, 4($sp)          # Restaura o ponteiro de frame
    addu $sp, $sp, $s3
    jr $ra                   # Retorna

main:
    # Inicialização da matriz image
    la $t8, WIDTH
    lw $t9, HEIGHT

    # Chama applyMedianFilter(image)
    jal applyMedianFilter

    # Impressão da matriz resultante
    la $t0, image
    li $t1, 0
    loop_print:
        bge $t1, $t9, end_print   # Se i >= HEIGHT, termina
        li $t2, 0                 # j = 0

        loop_print_j:
            bge $t2, $t8, next_row_print  # Se j >= WIDTH, passa para a próxima linha
            la $t3, image            # Endereço base de image
            lw $t4, WIDTH($t3)        # Obtém a largura da matriz

            # Impressão de image[i][j]
            mul $t5, $t2, $t4         # Calcula a posição atual em image
            add $t5, $t5, $t1
            sll $t5, $t5, 2           # Multiplica por 4 (tamanho de uma palavra)
            add $t5, $t5, $t3         # Adiciona ao endereço base

            #lw $t6, 0($t5)            # Obtém o valor de image[i][j]
            #li $v0, 1
            lb $t6, 0($t5)            # Obtém o valor de image[i][j] como byte
            li $v0, 11
            move $a0, $t6
            syscall

            # Impressão de espaço
            li $v0, 11
            li $a0, ' '
            syscall

            addi $t2, $t2, 1        # Incrementa j
            j loop_print_j

        next_row_print:
        # Impressão de nova linha
        li $v0, 11
        li $a0, '\n'
        syscall

        addi $t1, $t1, 1           # Incrementa i
        j loop_print

    end_print:
    li $v0, 10                    # Termina o programa
    syscall
