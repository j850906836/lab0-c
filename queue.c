#include "queue.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL && (sizeof(queue_t) > 0)) {
        return NULL;
    } else { /* What if malloc returned NULL? */
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return q;
    }
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    else if (q->size == 1) {
        q->size = 0;
        free(q->head->value);
        free(q->head);
        free(q);
    } else if (q->size == 0) {
        free(q);
    } else {
        while (q->head != NULL) {
            q->tail = q->head;
            q->head = q->head->next;
            free(q->tail->value);
            free(q->tail);
            q->size--;
        }
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
        q->size++;
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
        q->size++;
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
    if (q == NULL)
        return false;
    else if (q->size == 0 || q->head->value == NULL || sp == NULL) {
        return false;
    } else {
        q->size--;
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
    return q ? q->size : 0;
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
    if (q && q->size > 0) {
        list_ele_t *curr, *next;
        q->tail = curr = q->head;
        while (curr != NULL) {
            next = curr->next;
            curr->next = q->head;
            q->head = curr;
            curr = next;
        }
        q->tail->next = NULL;
        /*
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
        */
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || q->size <= 1)
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

    while (l1 && l2) {
        if (natur_cmp(l1->value, l2->value) <= 0) {
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
    return merge(head, fast);
}

int natur_cmp(char *a, char *b)
{
    if (strcasecmp(a, b) == 0)
        return 0;
    else {
        int i = 0, dig_numa = 0, dig_numb = 0;
        while (1) {
            while (a[i] == b[i] && !isdigit(a[i]) && !isdigit(b[i]))
                i++;
            while (isdigit(a[i])) {
                i++;
                dig_numa++;
            }
            i -= dig_numa;
            while (isdigit(b[i])) {
                i++;
                dig_numb++;
            }
            i -= dig_numb;
            if (dig_numa > dig_numb)
                return 1;
            else if (dig_numb > dig_numa)
                return -1;
            else if (dig_numa == dig_numb) {
                if (dig_numa == 0) {
                    return strcasecmp(a, b);
                } else {
                    int j = dig_numa + i;
                    for (; i < j; i++) {
                        if (a[i] > b[i])
                            return 1;
                        else if (a[i] < b[i])
                            return -1;
                        else
                            continue;
                    }
                    if (strlen(a) > dig_numa) {
                        dig_numa = 0;
                        dig_numb = 0;
                        i++;
                    } else
                        return 0;
                }
            }
        }
    }
    return false;
}