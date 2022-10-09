#include <time.h>
#include <stdbool.h>

#define NSEC_PER_SEC 1000000000
#define MSEC_PER_SEC 1000

static inline void timespec_subtract(struct timespec *res, const struct timespec *a, const struct timespec *b)
{
	res->tv_sec = a->tv_sec - b->tv_sec;
	res->tv_nsec = a->tv_nsec - b->tv_nsec;
	if (res->tv_nsec < 0) {
		res->tv_sec--;
		res->tv_nsec += NSEC_PER_SEC;
	}
}

static inline int64_t timespec_subtract_ns(const struct timespec *a, const struct timespec *b)
{
	struct timespec res;
	timespec_subtract(&res, a, b);
	return (int64_t)res.tv_sec * NSEC_PER_SEC + res.tv_nsec;
}