// SPDX-License-Identifier: GPL-3.0
/*
 * Copyright (C) 2021 Ryuichi Ueda. All rights reserved.
 * Copyright (C) 2021 Takumi Sakamoto. All rights reserved.
 */

#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/io.h>

MODULE_AUTHOR("Ryuichi Ueda and Takumi Sakamoto");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL; //アドレスをマッピングするための配列をグローバルで定義する

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos){
	char c; //読み込んだ字を入れる変数
	if(copy_from_user(&c,buf,sizeof(char)))
	return -EFAULT;

	if(c == '0'){
		gpio_base[10] = 1 << 25;
	}
	else if(c == '1'){
		gpio_base[7] = 1 << 25;
	}

	printk(KERN_INFO "receive %c\n", c);
	return 1; //読み込んだ文字数を返す(この場合はダミーの１)
}

static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos){
	int size = 0;
	char sunobo-[] ={'s', 'u', 'n', 'o', 'b', 'o', '-', 0x0A}; //スノボーの文字のバイナリ
	if(copy_to_user(buf+size,(const char *)sunobo-, sizeof(sunobo-))){
		printk(KERN_INFO "sunobo- : copy_to_user failed\n");
		return -EFAULT;
	}
	size += sizeof(sunobo-);
	return size;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read
};

static int __init init_mod(void){ //カーネルモジュール
	int retval;  
	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}

	printk(KERN_INFO "%s is locaded. major:%d\n",__FILE__,MAJOR(dev));
	
	cdev_init(&cdv, &led_fops);
 	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}
	
	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR"class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));

	gpio_base = ioremap_nocache(0xfe200000, 0xA0);

	const u32 led = 25;
	const u32 index = led/10; //GPFSEL2
	const u32 shift = (led%10)*3; //15bit
	const u32 mask = ~(0x7<<shift); //２進数を反転させる(１の場所を０に、０の場所を１にする)
	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift); 

	return 0;
}

static void __exit cleanup_mod(void){	
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod); //マクロで関数を登録
module_exit(cleanup_mod); //同上
