/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2022 Ventana Micro Systems Inc
 *
 */

#ifndef __SBI_PSM_H__
#define __SBI_PSM_H__

#include <sbi/sbi_types.h>

int sbi_psm_init(struct sbi_scratch *scratch, u32 hartid, bool cold_boot);
int sbi_psm_cpc_read_ffh(unsigned long reg, unsigned long *val);
int sbi_psm_cpc_write_ffh(unsigned long reg, unsigned long val);

struct perf_channel
{
	u64 desired_perf;
	u64 minimum_perf;
	u64 maximum_perf;
	u64 perf_tolerance;
	u64 perf_limited;
};

#endif
