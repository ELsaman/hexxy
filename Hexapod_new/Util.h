#ifndef UTIL_H
#define UTIL_H

#define PULSE_TO_DEG(p, min, max) map(p, min, max, 0, 180);
#define DEG_TO_PULSE(p, min, max) map(p, 0, 180, min, max);

#endif