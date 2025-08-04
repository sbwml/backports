#ifndef __BACKPORT_LINUX_HRTIMER_H
#define __BACKPORT_LINUX_HRTIMER_H
#include <linux/version.h>
#include_next <linux/hrtimer.h>

#if LINUX_VERSION_IS_LESS(4,16,0)

#define HRTIMER_MODE_ABS_SOFT HRTIMER_MODE_ABS
#define HRTIMER_MODE_REL_SOFT HRTIMER_MODE_REL

#endif /* < 4.16 */

#if LINUX_VERSION_IS_LESS(6,13,0)

static inline enum hrtimer_restart hrtimer_dummy_timeout(struct hrtimer *unused)
{
	return HRTIMER_NORESTART;
}

static inline void
hrtimer_update_function(struct hrtimer *timer,
			enum hrtimer_restart (*function)(struct hrtimer *))
{
	timer->function = function;
}

static inline void
hrtimer_setup(struct hrtimer *timer, enum hrtimer_restart (*function)(struct hrtimer *),
	      clockid_t clock_id, enum hrtimer_mode mode)
{
	hrtimer_init(timer, clock_id, mode);
	if (WARN_ON_ONCE(!function))
		timer->function = hrtimer_dummy_timeout;
	else
		timer->function = function;
}

#endif

#endif /* __BACKPORT_LINUX_HRTIMER_H */
