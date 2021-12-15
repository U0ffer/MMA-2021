.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib MMA_Lib.lib
ExitProcess PROTO : DWORD
_compare PROTO : DWORD, :DWORD
_strln PROTO : DWORD
_out PROTO : DWORD
_outInt PROTO : DWORD


.stack 4096
.const
	_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0
	_OVERFLOW_ERROR BYTE 'Ошибка выполнения: переполнение', 0
	L0 DWORD -10
	L1 DWORD 45
	L2 DWORD 234
	L3 DWORD 34
	L4 DWORD 3
	L5 DWORD 2
	L6 DWORD 10
	L7 DWORD 5
	L8 BYTE 'jjhgjgjhjhg', 0
	L9 BYTE 'контрольный пример', 0
	L10 BYTE 'test string', 0
	L11 DWORD 6
	L12 DWORD 50
	L13 BYTE 255
	L14 DWORD 100
	L15 DWORD 1601
	L16 BYTE '1234567890', 0
	L17 BYTE 'x > y', 0
	L18 BYTE 'неправда', 0
	L19 DWORD 999999
	L20 DWORD 0
.data
	_fiz		DWORD 0 ; uint
	_fia		DWORD 0 ; uint
	_fib		DWORD 0 ; uint
	_fsc		DWORD ? ; str
	_fqx		DWORD 0 ; uint
	_mainnmm		DWORD 0 ; uint
	_mainx		DWORD 0 ; uint
	_mainy		DWORD 0 ; uint
	_maintest		BYTE 0 ; bool
	_mainz		DWORD 0 ; uint
	_scope_1x		DWORD 0 ; uint
	_scope_2x		DWORD 0 ; uint
	_mainsa		DWORD ? ; str
	_mainsb		DWORD ? ; str
	_mainsc		DWORD ? ; str
	_scope_3x		DWORD 0 ; uint

.code
_fi PROC _fiy: DWORD, _fix: DWORD
	push		_fix
	push		_fiy

	pop		ebx
	pop		eax
	sub		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	push		L0

	pop		ebx
	pop		eax
	sub		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_fiz

	push		_fiy
	push		L1

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	push		L2
	push		_fix
	push		_fix
	push		_fiy

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax


	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax


	pop		ebx
	pop		eax
	test		ebx, ebx
	jz		EXIT_DIV_ON_NULL
	cdq
	idiv		ebx
	jo		EXIT_OVERFLOW
	push		eax

	push		L3

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	push		L1

	pop		ebx
	pop		eax
	test		ebx, ebx
	jz		EXIT_DIV_ON_NULL
	cdq
	idiv		ebx
	jo		EXIT_OVERFLOW
	push		eax


	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_fiz

	push		L4
	pop			_fia

	push		L5
	pop			_fib

	push		L6
	push		L7
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jna		FALSE10
	push		offset L8
	call		_out

FALSE10: 
	push		offset L9
	call		_out



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	mov		eax, _fiz
	ret		8
_fi ENDP

_fs PROC _fsb: DWORD, _fsa: DWORD
	push		offset L10
	pop			_fsc



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	mov		eax, _fsc
	ret		8
_fs ENDP

_fq PROC _fqa: DWORD
	push		L11
	pop			_fqx

	push		_fqx
	call		_outInt

	push		_fqa
	push		L7

	pop		ebx
	pop		eax
	sub		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_fqx



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	mov		eax, _fqa
	ret		4
_fq ENDP

main PROC
	push		L6
	push		L12

	pop		ebx
	pop		eax
	test		ebx, ebx
	jz		EXIT_DIV_ON_NULL
	cdq
	idiv		ebx
	jo		EXIT_OVERFLOW
	push		edx

	pop			_mainnmm

	push		_mainnmm
	call		_outInt

	push		offset L13
	pop			dword ptr _maintest

	push		L12
	pop			_scope_1x

	push		L14
	pop			_scope_2x

	push		L11
	push		_scope_2x

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainz

	push		_mainz
	call		_outInt

	push		L15
	pop			_mainx

	push		L7
	push		L7

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainy

	push		offset L16
	pop			_mainsa

	push		offset L16
	pop			_mainsb

	push		_mainx
	push		_mainy
	call		_fi
	push		eax
	pop			_mainz

	push		_mainsa
	push		_mainsb
	call		_fs
	push		eax
	pop			_mainsc

	push		_mainx
	push		_mainy
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jna		FALSE60
	push		offset L13
	pop			_scope_3x

	push		offset L17
	call		_out

	push		_scope_3x
	call		_outInt

FALSE60: 
	push		_mainx
	push		_mainy
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jnb		FALSE69
	jna		TRUE69
TRUE69: 
	push		offset L17
	call		_out

	jmp		IFOUT69
FALSE69: 
	push		offset L18
	call		_out

IFOUT69: 
	push		offset L9
	call		_out

	push		_mainx
	call		_outInt

	push		_mainy
	call		_outInt

	push		L19
	call		_fq
	push		eax
	pop			_mainx



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	push		L20
	call		ExitProcess

main ENDP
end main
