#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/types.h>

struct birthday {
  int day;
  int month;
  int year;
  struct list_head list;
};
/* This function is called when the module is loaded. */
static LIST_HEAD(birthday_list);
int simple_init(void)
{
        int i ;
        struct birthday *p;
        struct birthday *cur;
        printk(KERN_INFO "Loading Module\n");
        for(i = 0; i < 5; i++) {
            p = kmalloc(sizeof(*p), GFP_KERNEL);
            p->day = i;
            p->month= i+1;
            p->year = 2016;
            INIT_LIST_HEAD(&(p->list));
            list_add_tail(&(p->list), &birthday_list);
            //printk(KERN_DEBUG "%d", p->day);
        }
        list_for_each_entry(cur, &birthday_list, list) {
            printk(KERN_INFO "day:%d, month:%d, year:%d\n",
                    cur->day, cur->month, cur->year);
        }


        return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
    struct birthday *cur, *next;
    int cnt = 0;
    list_for_each_entry_safe(cur, next, &birthday_list, list) {
        list_del(&cur->list);
        kfree(cur);
    }
    cnt = 0;
    list_for_each_entry(cur, &birthday_list, list) {
        cnt++;
    }
    printk(KERN_INFO "%d entry left\n", cnt);
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
