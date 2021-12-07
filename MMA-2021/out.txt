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
	L0 DWORD 45
	L1 DWORD 234
	L2 DWORD 34
	L3 DWORD 45
	L4 BYTE 'test string', 0
	L5 DWORD 50
	L6 DWORD 100
	L7 DWORD 6
	L8 DWORD 12814
	L9 DWORD 5
	L10 DWORD 5
	L11 BYTE '1234567890', 0
	L12 BYTE 'контрольный пример', 0
	L13 DWORD 0
.data
	_fiz		DWORD 0 ; int
	_fsc		DWORD 0 ; str
	_mainx		DWORD 0 ; int
	_mainy		DWORD 0 ; int
	_mainz		DWORD 0 ; int
	_scope_0x		DWORD 0 ; int
	_scope_1x		DWORD 0 ; int
	_mainsa		DWORD 0 ; str
	_mainsb		DWORD 0 ; str
	_mainsc		DWORD 0 ; str

.code
_fi PROC _y: DWORD, _x: DWORD
	push		_y
	push		L0

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	push		L1
	push		_x
	push		_x
	push		_y

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

	push		L2

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	push		L3

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

_fs PROC _b: DWORD, _a: DWORD
	push		offset L4
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

main PROC
	push		L5
	pop			_mainx

	push		L6
	pop			_mainx

	push		L7
	push		_mainx

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainz

	push		_mainz
	call		_outInt

	push		L8
	pop			_mainx

	push		L9
	push		L10

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainy

	push		offset L11
	pop			_mainsa

	push		offset L11
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

	push		_mainsc
	call		_strln
	push		eax
	pop			_mainx

	push		offset L12
	call		_out

	push		_mainz
	call		_outInt

	push		_mainsc
	call		_out

	push		_mainy
	call		_outInt



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
	push		L13
	call		ExitProcess

main ENDP
end main
