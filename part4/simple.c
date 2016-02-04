#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/string.h>

/* This function is called when the module is loaded. */
void dfs(struct task_struct *, int);
const int USER_SCALE = 3;
int simple_init(void)
{
        printk(KERN_INFO "Loading Module\n");
        printk(KERN_INFO "-- [%d]%s\n", init_task.pid, init_task.comm);
        dfs(&init_task, 1);
        return 0;
}


void dfs(struct task_struct *root, int indent)
{
    struct list_head *list;
    struct task_struct *task;
    char *p;
    int i = 0;
    list_for_each(list, &(root->children)) {
        task = list_entry(list, struct task_struct, sibling);
        p = kmalloc(sizeof(char) * (indent * USER_SCALE + 1), GFP_KERNEL);
        for( i = 0; i < indent * USER_SCALE; i++)
            p[i] = ' ';
        p[i] = '\0';
        printk(KERN_INFO "%s\\_[%d]%s\n", p, task->pid, task->comm);
        dfs(task, indent + 1);
        kfree(p);
    }
    return;
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
