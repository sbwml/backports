#ifndef __BACKPORT_DEBUGFS_H_
#define __BACKPORT_DEBUGFS_H_
#include_next <linux/debugfs.h>
#include <linux/version.h>
#include <linux/device.h>

#ifndef DEFINE_DEBUGFS_ATTRIBUTE
#define DEFINE_DEBUGFS_ATTRIBUTE(__fops, __get, __set, __fmt) \
	DEFINE_SIMPLE_ATTRIBUTE(__fops, __get, __set, __fmt)
#define debugfs_create_file_unsafe(name, mode, parent, data, fops) \
	debugfs_create_file(name, mode, parent, data, fops)
#endif

#if LINUX_VERSION_IS_LESS(5,5,0)
static inline void debugfs_create_xul(const char *name, umode_t mode,
				      struct dentry *parent,
				      unsigned long *value)
{
	if (sizeof(*value) == sizeof(u32))
		debugfs_create_x32(name, mode, parent, (u32 *)value);
	else
		debugfs_create_x64(name, mode, parent, (u64 *)value);
}
#endif

#if LINUX_VERSION_IS_LESS(6,7,0)
/**
 * struct debugfs_cancellation - cancellation data
 * @list: internal, for keeping track
 * @cancel: callback to call
 * @cancel_data: extra data for the callback to call
 */
struct debugfs_cancellation {
	struct list_head list;
	void (*cancel)(struct dentry *, void *);
	void *cancel_data;
};

static inline void
debugfs_enter_cancellation(struct file *file,
			   struct debugfs_cancellation *cancellation)
{
}

static inline void
debugfs_leave_cancellation(struct file *file,
			   struct debugfs_cancellation *cancellation)
{
}
#endif /* <6.7 */

#endif /* __BACKPORT_DEBUGFS_H_ */
