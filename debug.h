#ifdef DEBUG
void dbg(const char *errstr, ...) {
	va_list ap;
	va_start(ap, errstr);
	vfprintf(stdout, errstr, ap);
	fflush(stdout);
	va_end(ap);
}
#else
#define dbg
#endif