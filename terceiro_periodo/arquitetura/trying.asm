.data
image: .byte 197,199,199,199,199,200,202,205,202,205,205,203,203,204,203,200,201,198,195,195
space: .asciiz ", "
height: .word 4	#número de linhas
width: .word 5	#número de colunas
vector: .word 20

.text
.globl main
main:
    li $t0, 0              
    #lw $t3, vector        
    la $t1, image          
    li $s1, 255         

Activate_filter:
    lb $t2, ($t1)           
    #andi $t2, $t2, 0xFF     
	
	ble $t2, $s1, filter
	#la $t4, vector	#usado constantemente t0
	#lw $t5, width	#usado como t1
	#li $t6, 255	#t3
	#j loop
	
filter:
    sub $s3, $s1, $s2    
    move $a0, $s3    
    j print                 

#loop:
	#lb $t7, 0($t4)
	#li $t6, 255
	#sub $t7, $t6, $t7
	#sb $t7, 0($t4)	
	
	#lb $t7, 1($t4)
	#sub $t7, $t6, $t7
	#sb $t7, 1($t4)	
	
	#lb $t7, 2($t4)
	#sub $t7, $t6, $t7
	#sb $t7, 2($t4)	
	
	#addi $t4, $t4, 3
	#addi $t5, $t5, -1
	#bnez $t5, loop
	
print:
    li $v0, 1               
    syscall

    li $v0, 4               
    la $a0, space         
    syscall

    addi $t1, $t1, 1       
    addi $t0, $t0, 1       
    bne $t0, $t3, Activate_filter      

exit:
    li $v0, 10              
    syscall
