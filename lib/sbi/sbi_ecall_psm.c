/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2022 Ventana Micro Systems Inc
 *
 */

#include <sbi/sbi_domain.h>
#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_trap.h>
#include <sbi/sbi_version.h>
#include <sbi/sbi_psm.h>
#include <sbi/sbi_scratch.h>
#include <sbi/riscv_asm.h>

static int sbi_ecall_psm_handler(unsigned long extid, unsigned long funcid,
				 const struct sbi_trap_regs *regs,
				 unsigned long *out_val,
				 struct sbi_trap_info *out_trap)
{
	int ret = SBI_SUCCESS;

	switch (funcid) {
	case SBI_EXT_PSM_CPC_READ_FFH:
		ret = sbi_psm_cpc_read_ffh(regs->a0, out_val);
		break;
	case SBI_EXT_PSM_CPC_WRITE_FFH:
		ret = sbi_psm_cpc_write_ffh(regs->a0, regs->a1);
		break;
	}

	return ret;
}

struct sbi_ecall_extension ecall_psm = {
	.extid_start = SBI_EXT_PSM,
	.extid_end = SBI_EXT_PSM,
	.handle = sbi_ecall_psm_handler,
};
