.data
	#area de especifica��es de vari�veis, lida com os dados na mem�ria principal
	#�rea para dados na mem�ria principal
	msg: .asciiz "ola mundo!"	#msg a ser exibida para o usu�rio
.text
	#instru��es do programa
	
	#instru��o para impress�o de string
	li $v0, 4
	la $a0, msg ##indicar o endere�o em que est� a msg
	syscall #fa�a, imprima