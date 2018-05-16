#include "treeclass.hpp"

using namespace std;

template<typename T>
struct tree<T> * treeclass<T>::newelement (T element)//protected
{
    struct tree<T> * head = (struct tree<T>*)malloc(sizeof(struct tree<T>));
    head->val = element;
    head->deep = 0;
    head->left = NULL;
    head->right = NULL;
    head->back = NULL;
    return head;
}

template<typename T>
void treeclass<T>::printtree(struct tree<T> * node)//protected
{
        if (node == NULL)
                return;
        if (node->left != NULL)
        printtree(node->left);
                cout<<node->val<< " ("<< node->deep<< ") "<<endl;
        if (node->right != NULL)
                printtree(node->right);
}

template<typename T>
int treeclass<T>::setdeep(struct tree<T>  * head)//protected
{
    if (head == NULL)
         return -1;

        int left = setdeep(head->left);
    int right = setdeep(head->right);
        if ( ((head->left)==NULL) && ((head->right)==NULL) )
    {
         head->deep = 0;
         return 0;
    }
    if (left > right)
        head->deep = left + 1;
    if (left <= right)
        head->deep = right + 1;

   return head->deep;
}

template<typename T>
int treeclass<T>::deep(struct tree<T>  * node)//protected
{
        if (node == NULL)
                return -1;
        return node->deep;
}

template<typename T>
void treeclass<T>::addelement (struct tree<T> * head, struct tree<T> * element)
{
        if (element == NULL)
                return;
        if (head == NULL)
                return;

    if (head->val <= element->val)
    {
        if (head->right == NULL)
        {
            head->right = element;
            element->back = head;
            head = head->right;
            return;
        }
        if (head->right != NULL)
            addelement(head->right, element);
    }

    if (head->val > element->val)
    {
        if (head->left == NULL)
        {
            head->left = element;
            element->back = head;
            head = head->left;
            return;
        }
        else
            addelement(head->left, element);
    }
    setdeep(head);
}

template<typename T>
struct tree<T> * treeclass<T>::searchbyval(struct tree<T> * head, int x)//protected
{
        struct tree<T> * res = NULL;
    if (head->val == x)
    {
        return head;
    }
    if ( (head->val > x) && (head->left != NULL) )
    {
       res = searchbyval(head->left, x);
    }

    if (head->val < x)
    {
        if (head->right != NULL)
                res = searchbyval(head->right, x);
    }

    return res;
}

template<typename T>
T treeclass<T>::deltree(struct tree<T>  * *phead)//protected
{
        if (*phead == NULL)
                return 0;

        int res = (*phead)->val;
        if ((*phead)->back != NULL)
        {
                struct tree<T> * back = (*phead)->back;
                struct tree<T> * left = (*phead)->left;
                struct tree<T> * right = (*phead)->right;

            if ((*phead)->back->right == (*phead))
                {
                (*phead)->back->right = NULL;
            }
            if ((*phead)->back->left == (*phead))
            {
                (*phead)->back->left = NULL;
            }
            free(*phead);

            if (right != NULL)
            {
                addelement (back, right);
                }
            if ((*phead)->left != NULL)
                {
                        addelement (back, left);
            }
        }
        if ((*phead)->back == NULL)
        {
                if ((*phead)->left != NULL)
                {
                        addelement ((*phead)->left, (*phead)->right);
                        (*phead) = (*phead)->left;
                        free((*phead)->back);
                }
                if ((*phead)->right != NULL)
                {
                        addelement ((*phead)->right, (*phead)->left);
                        (*phead) = (*phead)->right;
                        free((*phead)->back);
                }
                free(*phead);
        }
    return res;
}

template<typename T>
void treeclass<T>::destroy(struct tree<T>  * head)//protected
{
        struct tree<T> * right = (head)->right;
        struct tree<T> * left = (head)->left;
        if (left)
                destroy(left);
        if (right)
                destroy(right);
        free(head);
        return;
}

template<typename T>
void treeclass<T>::smallright(struct tree<T> ** phead)//protected
{
        if (*phead == NULL)
                return;
        if ((*phead)->left == NULL)
                return;

        struct tree<T> * a = *phead;
        struct tree<T> * b = (*phead)->left;
        a->left = b->right;

        if(b->right != NULL)
        {
                b->right->back = a;
        }
        b->right = a;
        if (a->back != NULL)
        {
                if (a->val >= a->back->val)
                {
                        a->back->right = b;
                }

                if (a->val < a->back->val)
                {
                        a->back->left = b;
                }
        }	b->back = a->back;
        a->back = b;
        *phead = b;
        setdeep(*phead);
}

template<typename T>
void treeclass<T>::smallleft(struct tree<T>  ** phead)//protected
{
        if (*phead == NULL)
                return;
        if ((*phead)->right == NULL)
                return;

        struct tree<T> * a = *phead;
        struct tree<T> * b = (*phead)->right;
        a->right = b->left;

        if(b->left != NULL)
        {
                b->left->back = a;
        }
        b->left = a;
        if (a->back != NULL)
        {
                if (a->val >= a->back->val)
                {
                        a->back->right = b;
                }

                if (a->val < a->back->val)
                {
                        a->back->left = b;
                }
        }
        b->back = a->back;
        a->back = b;
        *phead = b;
        setdeep(*phead);
}

template<typename T>
void treeclass<T>::bigleft(struct tree<T>  ** phead)//protected
{
        if ((*phead)->right == NULL)
                return;
        if ((*phead)->right->left == NULL)
                return;
        struct tree<T> * a = *phead;
        struct tree<T> * b = (*phead)->right;
        struct tree<T> * c = (*phead)->right->left;
        a->right = c->left;
        c->back = a->back;

        if (a->back != NULL)
        {
                if (a->val >= a->back->val)
                {
                        a->back->right = b;
                }

                if (a->val < a->back->val)
                {
                        a->back->left = b;
                }
        }	a->back = c;
        b->back = c;
        b->left = c->right;
        c->right = b;
        c->left = a;
        if (a->right != NULL)
        {
                a->right->back = a;
        }
        if (b->left != NULL)
        {
                b->left->back = b;
        }
        *phead = c;
        setdeep(*phead);
}

template<typename T>
void treeclass<T>::bigright(struct tree<T>  ** phead)//protected
{
        if ((*phead)->left == NULL)
                return;
        if ((*phead)->left->right == NULL)
                return;
        struct tree<T> * a = *phead;
        struct tree<T> * b = (*phead)->left;
        struct tree<T> * c = (*phead)->left->right;
        a->left = c->right;
        c->back = a->back;

        if (a->back != NULL)
        {
                if (a->val >= a->back->val)
                {
                        a->back->right = b;
                }

                if (a->val < a->back->val)
                {
                        a->back->left = b;
                }
        }	a->back = c;
        b->back = c;
        b->right = c->left;
        c->left = b;
        c->right = a;
        if (a->left != NULL)
        {
                a->left->back = a;
        }
        if (b->right != NULL)
        {
                b->right->back = b;
        }
        *phead = c;
        setdeep(*phead);
}

template<typename T>
int treeclass<T>::bal(struct tree<T>  ** phead)//protected
{

        if ((deep((*phead)->right) - deep((*phead)->left) >= 2) &&
        (deep((*phead)->right->left) <= deep((*phead)->right->right)))
        {
                //printf("smallleft[%d]    ",((*phead)->val));
                setdeep(*phead);
                smallleft(phead);
                setdeep(*phead);
                return 1;
        }

        if ((deep((*phead)->left) - deep((*phead)->right) >= 2) &&
        (deep((*phead)->left->right) <= deep((*phead)->left->left)))
        {
                //printf("smallright[%d]    ",((*phead)->val));
                setdeep(*phead);
                smallright(phead);
                setdeep(*phead);
                return 1;
        }

        if ((deep((*phead)->right) - deep((*phead)->left) >= 2) &&
                (deep((*phead)->right->left) > deep((*phead)->right->right)))
        {
                //printf("bigleft[%d]    ",((*phead)->val));
                setdeep(*phead);
                bigleft(phead);
                setdeep(*phead);
                return 1;
        }

        if ((deep((*phead)->left) - deep((*phead)->right) >= 2) &&
        (deep((*phead)->left->right) > deep((*phead)->left->left)))
        {
                //printf("bigright[%d]    ",((*phead)->val));
                setdeep(*phead);
                bigright(phead);
                setdeep(*phead);
                return 1;
        }
        setdeep(*phead);
        return 0;
}

template<typename T>
int treeclass<T>::balance(struct tree<T>  ** phead, int * res)//protected
{
        if ((*phead)->left != NULL)
        balance(&((*phead)->left), res);

        *res = bal(phead);

        if ((*phead)->right != NULL)
        balance(&((*phead)->right), res);
    return *res;
}

template<typename T>
int treeclass<T>::balanceall(struct tree<T>  * *phead)//protected
{
        int res = 0;
        while (balance(phead, &res) != balance(phead, &res))
                ;
}

template<typename T>
treeclass<T>::treeclass()//public
{
    this->root = NULL;
};

template<typename T>
void treeclass<T>::insert(T val)//public
{
        struct tree<T> * t = newelement (val);
        if (this->root != NULL)
                addelement (this->root, t);

        if (this->root == NULL)
                this->root = t;
}

template<typename T>
bool treeclass<T>::exists(T val)//public
{
        struct tree<T> * t = searchbyval(this->root, val);
        if (t != NULL)
                return true;
        if (t == NULL)
                return false;
}

template<typename T>
void treeclass<T>::remove(T val)//public
{
        struct tree<T> * t = searchbyval(this->root, val);
        //printf("t->val = %d\n", t->val);
        deltree(&t);
}

template<typename T>
void treeclass<T>::printtree()//public
{
        printtree(this->root);
}

template<typename T>
void treeclass<T>::balancetree()//public
{
        balanceall(&(this->root));
}

template<typename T>
treeclass<T>::~treeclass()//public
{
        destroy(this->root);
}

template class treeclass <int>;
template class treeclass <float>;
template class treeclass <double>;
template class treeclass <long int>;
template class treeclass <unsigned int>;
template class treeclass <long long int>;
template class treeclass <unsigned long long int>;
