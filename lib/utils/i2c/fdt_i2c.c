/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2021 YADRO
 *
 * Authors:
 *   Nikita Shubin <n.shubin@yadro.com>
 *
 * derivate: lib/utils/gpio/fdt_gpio.c
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <libfdt.h>
#include <sbi/sbi_error.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/i2c/fdt_i2c.h>

#include <sbi/sbi_console.h>

static struct fdt_i2c_adapter *i2c_adapter_drivers[] = {
};

static int fdt_i2c_adapter_init(void *fdt, int nodeoff)
{
	int pos, rc;
	struct fdt_i2c_adapter *drv;
	const struct fdt_match *match;

	/* Try all I2C drivers one-by-one */
	for (pos = 0; pos < array_size(i2c_adapter_drivers); pos++) {
		drv = i2c_adapter_drivers[pos];
		match = fdt_match_node(fdt, nodeoff, drv->match_table);
		if (match && drv->init) {
			rc = drv->init(fdt, nodeoff, match);
			if (rc == SBI_ENODEV)
				continue;
			if (rc)
				return rc;
			return 0;
		}
	}

	return SBI_ENOSYS;
}

static int fdt_i2c_adapter_find(void *fdt, int nodeoff,
				struct i2c_adapter **out_adapter)
{
	int rc;
	struct i2c_adapter *adapter = i2c_adapter_find(nodeoff);

	if (!adapter) {
		/* I2C adapter not found so initialize matching driver */
		rc = fdt_i2c_adapter_init(fdt, nodeoff);
		if (rc)
			return rc;

		/* Try to find I2C adapter again */
		adapter = i2c_adapter_find(nodeoff);
		if (!adapter)
			return SBI_ENOSYS;
	}

	if (out_adapter)
		*out_adapter = adapter;

	return 0;
}

int fdt_i2c_adapter_get(void *fdt, int nodeoff,
			struct i2c_adapter **out_adapter)
{
	int rc;
	struct i2c_adapter *adapter;

	if (!fdt || (nodeoff < 0) || !out_adapter)
		return SBI_EINVAL;

	rc = fdt_i2c_adapter_find(fdt, nodeoff, &adapter);
	if (rc)
		return rc;

	*out_adapter = adapter;

	return 0;
}
