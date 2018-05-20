#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#ifndef treeclass_H
#define treeclass_H
  
template<typename T>
struct tree
{
    struct tree<T> * left;
    struct tree<T> * right;
    struct tree<T> * back;
    int deep;
    T val;
};

template<typename T>
class treeclass
{
public:
    treeclass();
    void insert(T value);
    bool exists(T value);
    void remove(T value);
	void printtree();
	void balancetree();
    ~treeclass();



protected:
    struct tree<T>* newelement (T element);
	void printtree(struct tree<T>* node);
        int setdeep(struct tree<T> * head);
        int deep(struct tree<T> * node);
	void addelement (struct tree<T>* head, struct tree<T>* element);
	struct tree<T>* searchbyval(struct tree<T>* head, int x);
	T deltree(struct tree<T>** phead);
	void destroy(struct tree<T>* head);
	
	void smallright(struct tree<T>** phead);
	void smallleft(struct tree<T>** phead);
	void bigleft(struct tree<T>** phead);
	void bigright(struct tree<T>** phead);
	int bal(struct tree<T>** phead);
	int balance(struct tree<T>** phead, int * res);
	int balanceall(struct tree<T>** phead);
	
        struct tree<T> * root;
};

#endif
