/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2022 Ventana Micro Systems Inc
 *
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_barrier.h>
#include <sbi/riscv_encoding.h>
#include <sbi/riscv_atomic.h>
#include <sbi/sbi_bitops.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_domain.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_hartmask.h>
#include <sbi/sbi_psm.h>
#include <sbi/sbi_init.h>
#include <sbi/sbi_ipi.h>
#include <sbi/sbi_scratch.h>
#include <sbi/sbi_system.h>
#include <sbi/sbi_timer.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_string.h>

static const struct sbi_psm_device *psm_dev = NULL;
static unsigned long cppc_offset;

int sbi_psm_cpc_read_ffh(unsigned long reg, unsigned long *val)
{
	struct sbi_scratch *scratch;
	struct perf_channel *cppc;
	unsigned long hartid;

	hartid = current_hartid();

	scratch = sbi_hartid_to_scratch(hartid);
	cppc = sbi_scratch_offset_ptr(scratch, cppc_offset);

	switch (reg) {
		case 0x0:
			break;
		case 0x1:
			break;
		case 0x2:
			break;
		case 0x3:
			break;
		case 0x4:
			break;
		case 0x5:
			*val = cppc->desired_perf;
			break;
		case 0x6:
			*val = cppc->minimum_perf;
			break;
		case 0x7:
			*val = cppc->maximum_perf;
			break;
		case 0x8:
			*val = cppc->perf_tolerance;
			break;
		case 0x9:
			break;
		case 0xA:
			break;
		case 0xB:
			*val = sbi_timer_value();
			break;
		case 0xC:
			*val = csr_read(CSR_MCYCLE);
			break;
		case 0xD:
			*val = cppc->perf_limited;
			break;
		case 0xE:
			break;
		case 0xF:
			break;
		case 0x10:
			break;
		case 0x11:
			break;
		case 0x12:
			break;
		case 0x13:
			break;
		case 0x14:
			break;
		default:
			sbi_printf("Unrecognized FFH register\n");
			break;
	}
	return SBI_SUCCESS;
}

int sbi_psm_cpc_write_ffh(unsigned long reg, unsigned long val)
{
	struct sbi_scratch *scratch;
	struct perf_channel *cppc;
	unsigned long hartid;

	hartid = current_hartid();

	scratch = sbi_hartid_to_scratch(hartid);
	cppc = sbi_scratch_offset_ptr(scratch, cppc_offset);

	switch (reg) {
		case 0x0:
			break;
		case 0x1:
			break;
		case 0x2:
			break;
		case 0x3:
			break;
		case 0x4:
			break;
		case 0x5:
			cppc->desired_perf = val;
			break;
		case 0x6:
			cppc->minimum_perf = val;
			break;
		case 0x7:
			cppc->maximum_perf = val;
			break;
		case 0x8:
			cppc->perf_tolerance = val;
			break;
		case 0x9:
			break;
		case 0xA:
			break;
		case 0xB:
			break;
		case 0xC:
			break;
		case 0xD:
			break;
		case 0xE:
			break;
		case 0xF:
			break;
		case 0x10:
			break;
		case 0x11:
			break;
		case 0x12:
			break;
		case 0x13:
			break;
		case 0x14:
			break;
		default:
			sbi_printf("Unrecognized FFH register\n");
			break;
	}

	return SBI_SUCCESS;
}

const struct sbi_psm_device *sbi_psm_get_device(void)
{
	return psm_dev;
}

void sbi_psm_set_device(const struct sbi_psm_device *dev)
{
	if (!dev || psm_dev)
		return;

	psm_dev = dev;
}

int sbi_psm_init(struct sbi_scratch *scratch, u32 hartid, bool cold_boot)
{
	u32 i;
	struct sbi_scratch *rscratch;
	struct perf_channel *cppc;

	if (cold_boot) {
		cppc_offset = sbi_scratch_alloc_offset(sizeof(*cppc));
		if (!cppc_offset)
			return SBI_ENOMEM;

		/* Initialize hart state data for every hart */
		for (i = 0; i <= sbi_scratch_last_hartid(); i++) {
			rscratch = sbi_hartid_to_scratch(i);
			if (!rscratch)
				continue;

			cppc = sbi_scratch_offset_ptr(rscratch,
						       cppc_offset);
			sbi_memset(cppc, 0, sizeof(*cppc));
		}
	}

	return 0;
}
