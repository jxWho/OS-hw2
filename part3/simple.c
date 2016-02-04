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
//static LIST_HEAD(birthday_list);
static struct list_head birthday_list = {.prev=&birthday_list,
                                        .next=&birthday_list};
int simple_init(void)
{
        int i ;
        struct birthday *p;
        struct birthday *cur;
        struct list_head *tail, *head_cur, *hprev, *hnext;
        int cnt = 0;
        size_t temp_offset;
        printk(KERN_INFO "Loading Module\n");
        for(i = 0; i < 5; i++) {
            p = kmalloc(sizeof(*p), GFP_KERNEL);
            p->day = i;
            p->month= i+1;
            p->year = 2016;
            //initial
            //INIT_LIST_HEAD(&(p->list));
            p->list.next = &p->list;
            p->list.prev = &p->list;
            //insert
            tail = birthday_list.prev;
            tail-> next = &p->list;
            (p->list).next = &birthday_list;
            birthday_list.prev = &p->list;
            (p->list).prev = tail;

            //printk(KERN_DEBUG "%d", p->day);
        }
        head_cur = birthday_list.next;
        while(head_cur != &birthday_list) {
            // get the current entry
            temp_offset = (size_t)&(((struct birthday *)0)->list);
            cur = (struct birthday*)((char *)head_cur -
                                temp_offset);
            head_cur = head_cur->next;
            printk(KERN_INFO "day:%d, month:%d, year:%d\n",
                    cur->day, cur->month, cur->year);
        }

        // free memory
        head_cur = birthday_list.next;
        while(head_cur != &birthday_list) {
            temp_offset = (size_t)&(((struct birthday *)0)->list);
            cur = (struct birthday*)((char *)head_cur -
                                temp_offset);

            hprev = head_cur->prev;
            hnext = head_cur->next;
            head_cur = hnext;
            hprev->next = hnext;
            kfree(cur);
        }
        return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
