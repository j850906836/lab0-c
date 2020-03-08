#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
int length = 0;
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL && (sizeof(queue_t) > 0)) {
        printf("malloc fail");
        return NULL;
    } else { /* What if malloc returned NULL? */
        q->head = NULL;
        q->tail = NULL;
        return q;
    }
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    else if (length == 1) {
        length = 0;
        free(q->head->value);
        free(q->head);
        free(q);
    } else if (length == 0) {
        free(q);
    } else {
        while (q->head != NULL) {
            q->tail = q->head;
            q->head = q->head->next;
            free(q->tail->value);
            free(q->tail);
        }
        length = 0;
        free(q);
    }
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* Solve: What should you do if the q is NULL? */
    if (q == NULL) {
        printf("queue is NULL\n");
        return false;
    } else {
        length++;
        newh = malloc(sizeof(list_ele_t));
        if (newh == NULL)
            return false;
        char *input;
        size_t string_size;
        string_size = strlen(s);
        input = malloc(string_size + 1);
        if (input == NULL) {
            free(newh);
            return false;
        }
        int i;
        for (i = 0; s[i] != '\0'; i++) {
            input[i] = s[i];
        }
        input[i] = '\0';
        newh->value = input;
        newh->next = q->head;
        if (q->head == NULL && q->tail == NULL)
            q->head = q->tail = newh;
        else
            q->head = newh;
        return true;
    }
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt;
    if (q == NULL) {
        return false;
    } else {
        length++;
        newt = malloc(sizeof(list_ele_t));
        if (newt == NULL)
            return false;
        char *input;
        size_t string_size;
        string_size = strlen(s);
        input = malloc(string_size + 1);
        if (input == NULL) {
            free(newt);
            return false;
        }
        int i;
        for (i = 0; s[i] != '\0'; i++) {
            input[i] = s[i];
        }
        input[i] = '\0';
        newt->value = input;
        newt->next = NULL;
        if (q->head == NULL && q->tail == NULL)
            q->head = q->tail = newt;
        else {
            q->tail->next = newt;
            q->tail = newt;
        }
        return true;
    }
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (length == 0 || q == NULL || q->head->value == NULL || sp == NULL) {
        return false;
    } else {
        length--;
        size_t i;
        char *tmp;
        list_ele_t *link;
        tmp = q->head->value;
        for (i = 0; tmp[i] != '\0'; i++) {
            sp[i] = tmp[i];
            if (i == bufsize - 2) {
                i++;
                break;
            }
        }
        sp[i] = '\0';
        link = q->head;
        q->head = q->head->next;
        free(link->value);
        free(link);
        return true;
    }
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || length == 0)
        return false;
    else
        return length;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q != NULL && length > 0) {
        list_ele_t *prev = NULL, *curr, *next = NULL, *tmp;
        tmp = curr = q->head;
        while (curr != NULL) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        q->tail = tmp;
        q->head = prev;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || length <= 1)
        return;
    else {
        q->head = mergeSortList(q->head);
        list_ele_t *tmp = q->head;
        while (tmp->next)
            tmp = tmp->next;
        q->tail = tmp;
    }
}
list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    // merge with pseudo node
    list_ele_t *temp = NULL;
    list_ele_t **p = &temp;
    int cmp;
    char *a = NULL, *b = NULL;
    while (l1 && l2) {
        a = l1->value;
        b = l2->value;
        cmp = 0;
        while (a[cmp] == b[cmp])
            cmp++;
        if (strlen(a) == strlen(b) && cmp == strlen(a))
            cmp = 0;
        else if (a[cmp] < b[cmp])
            cmp = -1;
        else
            cmp = 1;
        if (cmp <= 0) {
            *p = l1;
            l1 = l1->next;
        } else {
            *p = l2;
            l2 = l2->next;
        }
        p = &(*p)->next;
    }

    if (l1)
        *p = l1;
    if (l2)
        *p = l2;

    return temp;
}

list_ele_t *mergeSortList(list_ele_t *head)
{
    // merge sort
    if (!head || !head->next) {
        return head;
    }
    list_ele_t *fast = head->next;
    list_ele_t *slow = head;
    // split list
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;
    // sort each list
    head = mergeSortList(head);
    fast = mergeSortList(fast);
    //     list_ele_t* l1 = mergeSortList(head);
    //     list_ele_t* l2 = mergeSortList(fast);
    // merge sorted l1 and sorted l2
    return merge(head, fast);
}
/*
list_ele_t* merge (list_ele_t* l1, list_ele_t* l2) {
    // merge with recursive
        if(!l2)
            return l1;
        if(!l1)
            return l2;
        if(strcasecmp( l1->value ,l2->value) <= 0) {
            l1->next = merge(l1->next, l2);
            return l1;
        }
        else {
            l2->next = merge(l1, l2->next);
            return l2;
        }
    }

list_ele_t* mergeSortList (list_ele_t* head) {
        // merge sort
        if(!head || !head->next) {
            return head;
        }
        list_ele_t* fast = head->next;
        list_ele_t* slow = head;
        // split list
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        slow->next = NULL;
        // sort each list
        head = mergeSortList(head);
        fast = mergeSortList(fast);
   //     list_ele_t* l1 = mergeSortList(head);
   //     list_ele_t* l2 = mergeSortList(fast);
        // merge sorted l1 and sorted l2
        return merge(head, fast);
}*/