.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/MMA_Lib.lib
ExitProcess PROTO : DWORD
_compare PROTO : DWORD, :DWORD
_strln PROTO : DWORD
_out PROTO : DWORD
_outBool PROTO : DWORD
_outInt PROTO : DWORD


.stack 4096
.const
	_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0
	_OVERFLOW_ERROR BYTE 'Ошибка выполнения: переполнение', 0
	L0 BYTE 'hello', 0
	L1 BYTE 'a', 0
	L2 DWORD 0
	L3 DWORD 100
	L4 DWORD 78
	L5 DWORD 1
	L6 BYTE 'helloi43p', 0
	L7 BYTE 'Working!!', 0
	L8 DWORD 10
.data
	_maintest		DWORD 0 ; bool
	_maintes		DWORD 0 ; bool
	_mainui		DWORD ? ; str

.code
_fi PROC _fio: DWORD, _fix: DWORD
	push		_fix
	call		_outBool



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
	mov		eax, offset L0
	ret		8
_fi ENDP

main PROC
	push		offset L1
	push		offset L1

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		NOTEQUAL35
	push		0
	je		EQUAL35
EQUAL35:
	push		1
NOTEQUAL35:
	push		L2

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		NOTEQUAL37
	push		0
	je		EQUAL37
EQUAL37:
	push		1
NOTEQUAL37:
	pop			_maintest

	push		L3
	push		L4

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jb		LESS45
	push		0
	ja		MORE45
LESS45:
	push		1
MORE45:
	push		L5

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		NOTEQUAL47
	push		0
	je		EQUAL47
NOTEQUAL47:
	push		1
EQUAL47:
	pop			_maintes

	push		_maintest
	call		_outBool

	push		_maintes
	call		_outBool

	push		offset L6
	pop			_mainui

	push		L5
	pop		eax
	cmp		eax, 1
	push		offset L7
	call		_out

FALSE14: 


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
	push		L8
	call		ExitProcess

main ENDP
end main
