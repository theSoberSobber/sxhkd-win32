#define VDA_FEATURES

static void test(const Arg* arg);
static void quit(const Arg* arg);
static void spawn(const Arg* arg);
static void toggleexplorer(const Arg* arg);

#ifdef VDA_FEATURES
#include "VD/VD.h"
#endif