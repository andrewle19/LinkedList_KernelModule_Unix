// Andrew Le
// 9/5/17
// kernal project that uses  linked list to store 5 birthdays


#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>


typedef struct birthday
{
	int day;
	int month;
	int year;
	struct list_head list;
}birthday;


LIST_HEAD(bdayList);



/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
	// birthday ptr
	birthday *new;
	// loop to input data into each node and create each node
	for(int i = 0; i < 5; i++)
	{	
		new = kmalloc(sizeof(*new), GFP_KERNEL);
		// add value to new bdays
		new->day = i+1;
		new->month = i+1;
		new->year = i+2000;
		// init the list within struct
		INIT_LIST_HEAD(&new->list);
		// add to tail of the list
		list_add_tail(&new->list,&bdayList);
		
	}

	// display and traverse linked list
	birthday *ptr;

	list_for_each_entry(ptr,&bdayList,list)
	{
		printk(KERN_INFO "day:%i,month:%i,year:%i",ptr->day,ptr->month,ptr->year);
	}
	

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

	printk(KERN_INFO "Removing Module\n");
	birthday *ptr,*next;
	list_for_each_entry_safe(ptr,next,&bdayList,list)
	{
		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday");
MODULE_AUTHOR("Andrew Le");







