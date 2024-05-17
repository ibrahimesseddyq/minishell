#include "./../backend.h"
void ex()
{
	system("leaks a.out");
}
int main()
{
	atexit(ex);
	t_allocation *lst;
	void *t1;
	void *t2;

	lst = malloc(sizeof(t_allocation));
	initialize_gc(lst);
	t1 = gcalloc(40, lst);
	t2 = gcalloc(30, lst);

	// gc_free(lst);
}