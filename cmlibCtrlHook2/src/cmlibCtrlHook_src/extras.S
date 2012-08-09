	.set noreorder

.global sceCtrlCommonFuncPatched
.ent	sceCtrlCommonFuncPatched
sceCtrlCommonFuncPatched:

	# backup register
	sw $s0, 0($sp)
	sw $s1, 4($sp)

	# backup argument
	move $s0, $a0

	# backup $ra
	move $s1, $ra

	# load ctrl_version
	lui $v0, %hi(ctrl_version)
	lw $v0, %lo(ctrl_version)($v0)

	# check version
	beqz $v0, $jump_old_patch_func
	nop

	# push
	addiu $sp, $sp, -48

	# The part invalid with a patch.
	sw $s1, 4($sp)
	lui $t0, 0x8000

	# jump
	j $jump_common_func_patched
	nop

$jump_old_patch_func:
	# push
	addiu $sp, $sp, -32

	# move argument
	move $a2, $a3

	# The part invalid with a patch.
	sw $a1, 4($sp)
	lui $a3, 0x8000

$jump_common_func_patched:
	# overwritten $ra
	lui $ra, %hi(sceCtrlCommonFuncLauncher)
	addiu $ra, $ra, %lo(sceCtrlCommonFuncLauncher)

	# jump sceCtrlCommonFunc
	lui $s1, %hi(ctrl_jump_addr)
	addiu $s1, $s1, %lo(ctrl_jump_addr)
	lw $s1, 0($s1)
	jr $s1
	nop

.end sceCtrlCommonFuncPatched

.global sceCtrlCommonFuncLauncher
.ent	sceCtrlCommonFuncLauncher
sceCtrlCommonFuncLauncher:

	# restore argument
	move $a0, $s0

	# set return_value($v0)
	move $a1, $v0

	# call
	jal sceCtrlCommonFuncControl
	nop

	# restore return_address($ra)
	move $ra, $s1

	# restore register
	lw $s0, 0($sp)
	lw $s1, 4($sp)

	# load ctrl_version
	lui $v1, %hi(ctrl_version)
	lw $v1, %lo(ctrl_version)($v1)

	# check version
	beqz $v1, $jump_launcher_func
	nop

	# set stack_value(48 - 32)
	li $v1, 16

$jump_launcher_func:

	# set stack_value
	addiu $v1, $v1, 32

	# pop
	addu $sp, $sp, $v1

	# return
	jr $ra
	nop

.end sceCtrlCommonFuncLauncher

.global sceCtrlCommonFunc
.ent	sceCtrlCommonFunc
sceCtrlCommonFunc:

	# load ctrl_version
	lui $v1, %hi(ctrl_version)
	lw $v1, %lo(ctrl_version)($v1)

	# check version
	beqz $v1, $jump_old_original_func
	nop

	# original_function_work
	addiu $sp, $sp, -48
	addiu $v1, $a1, -1
	sw $s1, 4($sp)
	lui $t0, 0x8000

	# jump
	j $jump_original_func
	nop

$jump_old_original_func:
	# move argument
	move $a2, $a3

	# original_function_work
	addiu $sp, $sp, -32
	addiu $v1, $a1, -1
	sw $s1, 4($sp)
	lui $a3, 0x8000

$jump_original_func:
	# jump sceCtrlCommonFunc
	lui $s1, %hi(ctrl_jump_addr)
	addiu $s1, $s1, %lo(ctrl_jump_addr)
	lw $s1, 0($s1)
	jr $s1
	nop

.end sceCtrlCommonFunc

