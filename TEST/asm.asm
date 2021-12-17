.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib MMA_Lib.lib
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
	L0 DWORD 15
	L1 DWORD 10
	L2 DWORD 20
	L3 DWORD 3
	L4 BYTE 'a', 0
	L5 DWORD 0
	L6 DWORD 1678
	L7 DWORD 11
	L8 DWORD 0
	L9 BYTE 'block else works!!!', 0
.data
	_fay		DWORD ? ; str
	_fbz		DWORD 0 ; uint
	_fcresult		DWORD 0 ; bool
	_maintest		DWORD 0 ; bool
	_mainx		DWORD 0 ; uint
	_mainy		DWORD 0 ; uint
	_mainz		DWORD 0 ; uint
	_scope_2z		DWORD 0 ; uint

.code
_fa PROC _fax: DWORD
	push		_fax
	pop			_fay



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
	mov		eax, _fay
	ret		4
_fa ENDP

_fb PROC _fby: DWORD
	push		L0
	pop			_fbz

	push		_fby
	push		L1
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jna		FALSE9
	jnb		TRUE9
TRUE9: 
	push		_fbz
	push		L2

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_fbz

	jmp		IFOUT9
FALSE9: 
	push		L3
	pop			_fbz

IFOUT9: 


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
	mov		eax, _fbz
	ret		4
_fb ENDP

_fc PROC _fcstr: DWORD
	push		_fcstr
	push		offset L4

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		NOTEQUAL73
	push		0
	je		EQUAL73
EQUAL73:
	push		1
NOTEQUAL73:
	pop			_fcresult



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
	mov		eax, _fcresult
	ret		4
_fc ENDP

main PROC
	push		L5
	pop			_maintest

	push		L6
	pop			_mainx

	push		L7
	pop			_mainy

	push		L8
	pop			_mainz

	push		_mainx
	push		_mainy

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainz

	push		_mainz
	call		_outInt

	push		_mainx
	push		_mainy

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainz

	push		_mainz
	call		_outInt

	push		_mainx
	push		_mainy

	pop		ebx
	pop		eax
	sub		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainz

	push		_mainz
	call		_outInt

	push		_mainx
	push		_mainy

	pop		ebx
	pop		eax
	test		ebx, ebx
	jz		EXIT_DIV_ON_NULL
	cdq
	idiv		ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainz

	push		_mainz
	call		_outInt

	push		_mainx
	push		_mainy

	pop		ebx
	pop		eax
	test		ebx, ebx
	jz		EXIT_DIV_ON_NULL
	cdq
	idiv		ebx
	jo		EXIT_OVERFLOW
	push		edx

	pop			_mainz

	push		_mainz
	call		_outInt

	push		_mainx
	push		_mainy

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jb		LESS154
	push		0
	ja		MORE154
LESS154:
	push		1
MORE154:
	pop			_maintest

	push		_maintest
	call		_outBool

	push		_mainx
	push		_mainy

	pop		ebx
	pop		eax
	cmp		eax, ebx
	ja		MORE163
	push		0
	jb		LESS163
MORE163:
	push		1
LESS163:
	pop			_maintest

	push		_maintest
	call		_outBool

	push		L1
	push		_mainx

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		NOTEQUAL172
	push		0
	je		EQUAL172
EQUAL172:
	push		1
NOTEQUAL172:
	pop			_maintest

	push		_maintest
	call		_outBool

	push		L1
	push		_mainx

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jne		NOTEQUAL181
	push		0
	je		EQUAL181
NOTEQUAL181:
	push		1
EQUAL181:
	pop			_maintest

	push		_maintest
	call		_outBool

	push		_mainy
	push		L7

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jbe		LESSOREQUALS190
	push		0
	jna		MORE190
LESSOREQUALS190:
	push		1
MORE190:
	pop			_maintest

	push		_maintest
	call		_outBool

	push		_mainy
	push		L7

	pop		ebx
	pop		eax
	cmp		eax, ebx
	jae		MOREOREQUAL199
	push		0
	jnb		LESS199
MOREOREQUAL199:
	push		1
LESS199:
	pop			_maintest

	push		_maintest
	call		_outBool

	push		_mainx
	push		_mainy
	pop		ebx
	pop		eax
	cmp		eax, ebx
	jna		FALSE54
	jnb		TRUE54
TRUE54: 
	push		_mainx
	push		_mainy

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_scope_2z

	push		_scope_2z
	call		_outInt

	jmp		IFOUT54
FALSE54: 
	push		offset L9
	call		_out

IFOUT54: 


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
