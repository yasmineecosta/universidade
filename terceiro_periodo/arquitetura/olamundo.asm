.data
	#area de especificações de variáveis, lida com os dados na memória principal
	#área para dados na memória principal
	msg: .asciiz "ola mundo!"	#msg a ser exibida para o usuário
.text
	#instruções do programa
	
	#instrução para impressão de string
	li $v0, 4
	la $a0, msg ##indicar o endereço em que está a msg
	syscall #faça, imprima