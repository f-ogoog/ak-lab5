// SPDX-License-Identifier: UNLICENSED
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <hello1.h>

MODULE_AUTHOR("Oleg Tsuria IO-21 <tsurya.oleg@gmail.com>");
MODULE_DESCRIPTION("Part of structure for printing 'Hello, world!'");
MODULE_LICENSE("Dual BSD/GPL");

struct tOfiter {
	struct list_head list;
	ktime_t sTime;
	ktime_t eTime;
};

static LIST_HEAD(iterList);

void printHello(void)
{
	//Working with list and memory
	struct tOfiter *iter = kmalloc(sizeof(*iter),
		GFP_KERNEL);
	iter->sTime = ktime_get();
	pr_info("Hello, world!\n");
	iter->eTime = ktime_get();
	list_add_tail(&iter->list, &iterList);
}
EXPORT_SYMBOL(printHello);

static void __exit hello1_exit(void)
{
	struct tOfiter *iter;
	struct list_head *pos,  *tmp;

	// Travel the list
	list_for_each_safe(pos, tmp, &iterList) {
		iter = list_entry(pos, struct tOfiter, list);
		pr_info(" Time of printing: %lld ns\n",
		        ktime_to_ns(iter->eTime) - ktime_to_ns(iter->sTime));
		list_del(pos);
		kfree(iter);
	}
}
module_exit(hello1_exit);
