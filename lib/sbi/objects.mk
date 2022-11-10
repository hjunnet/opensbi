#
# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (c) 2019 Western Digital Corporation or its affiliates.
#
# Authors:
#   Anup Patel <anup.patel@wdc.com>
#

libsbi-objs-y += riscv_asm.o
libsbi-objs-y += riscv_atomic.o
libsbi-objs-y += riscv_hardfp.o
libsbi-objs-y += riscv_locks.o

libsbi-objs-y += sbi_ecall.o
libsbi-objs-y += sbi_ecall_exts.o

# The order of below extensions is performance optimized
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_TIME) += ecall_time
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_RFENCE) += ecall_rfence
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_IPI) += ecall_ipi
carray-sbi_ecall_exts-y += ecall_base
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_HSM) += ecall_hsm
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_PSM) += ecall_psm
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_SRST) += ecall_srst
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_PMU) += ecall_pmu
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_LEGACY) += ecall_legacy
carray-sbi_ecall_exts-$(CONFIG_SBI_ECALL_VENDOR) += ecall_vendor

libsbi-objs-y += sbi_ecall_base.o
libsbi-objs-$(CONFIG_SBI_ECALL_HSM) += sbi_ecall_hsm.o
libsbi-objs-$(CONFIG_SBI_ECALL_PSM) += sbi_ecall_psm.o
libsbi-objs-$(CONFIG_SBI_ECALL_LEGACY) += sbi_ecall_legacy.o
libsbi-objs-$(CONFIG_SBI_ECALL_PMU) += sbi_ecall_pmu.o
libsbi-objs-y += sbi_ecall_replace.o
libsbi-objs-$(CONFIG_SBI_ECALL_VENDOR) += sbi_ecall_vendor.o

libsbi-objs-y += sbi_bitmap.o
libsbi-objs-y += sbi_bitops.o
libsbi-objs-y += sbi_console.o
libsbi-objs-y += sbi_domain.o
libsbi-objs-y += sbi_emulate_csr.o
libsbi-objs-y += sbi_fifo.o
libsbi-objs-y += sbi_hart.o
libsbi-objs-y += sbi_math.o
libsbi-objs-y += sbi_hfence.o
libsbi-objs-y += sbi_hsm.o
libsbi-objs-y += sbi_psm.o
libsbi-objs-y += sbi_illegal_insn.o
libsbi-objs-y += sbi_init.o
libsbi-objs-y += sbi_ipi.o
libsbi-objs-y += sbi_irqchip.o
libsbi-objs-y += sbi_misaligned_ldst.o
libsbi-objs-y += sbi_platform.o
libsbi-objs-y += sbi_pmu.o
libsbi-objs-y += sbi_scratch.o
libsbi-objs-y += sbi_string.o
libsbi-objs-y += sbi_system.o
libsbi-objs-y += sbi_timer.o
libsbi-objs-y += sbi_tlb.o
libsbi-objs-y += sbi_trap.o
libsbi-objs-y += sbi_unpriv.o
libsbi-objs-y += sbi_expected_trap.o
