// SPDX-License-Identifier: UNLICENSED
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <hello1.h>

MODULE_AUTHOR("Oleg Tsuria IO-21 <tsurya.oleg@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_PARM_DESC(counter, "Counter of 'Hello, world!'");
extern void printHello(void);

static unsigned int counter = 1;
module_param(counter, uint, 0444);

static int __init hello2_init(void)
{
	unsigned int i = 0;

	if (counter == 0 || (counter >= 5 && counter <= 10))
		pr_warn("Warning: Continuing\n");

	if (counter > 10) {
		pr_err("Error: EINVAL (bad value)!\n");
		// Module load error
		return -EINVAL;
	}

	// Print "Hello, world!" counter times
	for (i = 0; i < counter; i++) {
		printHello();
	}
	return 0;
}
static void __exit hello2_exit(void)
{
	pr_info("Module Hello2.ko was removed.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
