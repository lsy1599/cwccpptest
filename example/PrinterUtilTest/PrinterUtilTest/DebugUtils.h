#ifndef __DEBUG_UTILS__
#define __DEBUG_UTILS__

#if DBG
#define ASSERT(b)		{ if (!(b)) DebugBreak(); }
#else
#define ASSERT(b)
#endif

#endif