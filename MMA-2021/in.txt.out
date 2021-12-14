.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/MMA_Lib.lib
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
	L4 DWORD 45
	L5 DWORD 3
	L6 DWORD 2
	L7 DWORD 10
	L8 DWORD 5
	L9 BYTE 'jjhgjgjhjhg', 0
	L10 BYTE 'контрольный пример', 0
	L11 BYTE 'test string', 0
	L12 DWORD 6
	L13 DWORD 5
	L14 DWORD 50
	L15 DWORD 100
	L16 DWORD 6
	L17 DWORD 1601
	L18 DWORD 5
	L19 DWORD 5
	L20 BYTE '1234567890', 0
	L21 DWORD 1
	L22 BYTE 'x > y', 0
	L23 BYTE 'неправда', 0
	L24 DWORD 999999
	L25 DWORD 0
.data
	_fiz		DWORD 0 ; int
	_fia		DWORD 0 ; int
	_fib		DWORD 0 ; int
	_fsc		DWORD 0 ; str
	_fqx		DWORD 0 ; int
	_mainx		DWORD 0 ; int
	_mainy		DWORD 0 ; int
	_mainz		DWORD 0 ; int
	_scope_1x		DWORD 0 ; int
	_scope_2x		DWORD 0 ; int
	_mainsa		DWORD 0 ; str
	_mainsb		DWORD 0 ; str
	_mainsc		DWORD 0 ; str
	_scope_3x		DWORD 0 ; int

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

	push		L4

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

	push		L5
	pop			_fia

	push		L6
	pop			_fib

	push		L7
	push		L8
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jna		FALSE10
	push		offset L9
	call		_out

FALSE10: 
	push		offset L10
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
	push		offset L11
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
	push		L12
	pop			_fqx

	push		_fqx
	call		_outInt

	push		_fqa
	push		L13

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
	push		L14
	pop			_scope_1x

	push		L15
	pop			_scope_2x

	push		L16
	push		_scope_2x

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainz

	push		_mainz
	call		_outInt

	push		L17
	pop			_mainx

	push		L18
	push		L19

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainy

	push		offset L20
	pop			_mainsa

	push		offset L20
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
	jna		FALSE56
	push		L21
	pop			_scope_3x

	push		offset L22
	call		_out

	push		_scope_3x
	call		_outInt

FALSE56: 
	push		_mainx
	push		_mainy
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jnb		FALSE65
	jna		TRUE65
TRUE65: 
	push		offset L22
	call		_out

	jmp		IFOUT65
FALSE65: 
	push		offset L23
	call		_out

IFOUT65: 
	push		offset L10
	call		_out

	push		_mainx
	call		_outInt

	push		_mainy
	call		_outInt

	push		L24
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
	push		L25
	call		ExitProcess

main ENDP
end main
