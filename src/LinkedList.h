struct node
{
    void * data;
    node * next;
}
struct LList
{
    node * head;
}

LList createLList(void);

void lListAdd(LList l, *void e);

void * remove(LList l);

void * get(LList l);