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
    if (q == NULL) {
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
    else if (q->head == q->tail) {
        free(q->head->value);
        free(q->head);
    } else {
        while (q->head != NULL) {
            q->tail = q->head;
            q->head = q->head->next;
            free(q->tail->value);
            free(q->tail);
        }
    }
    free(q);
}

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
    if (q == NULL || q->head->value == NULL || sp == NULL)
        return false;
    else {
        length--;
        size_t i;
        char *tmp;
        list_ele_t *link;
        tmp = q->head->value;
        for (i = 0; tmp[i] != '\0'; i++) {
            sp[i] = tmp[i];
            if (i == bufsize - 1) {
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
    if (q == NULL || q->head->value == NULL)
        return false;
    else { /*
         int size = 0;
         list_ele_t *tmp = q->head;
         while (tmp->next != NULL) {
             size++;
             tmp = tmp->next;
         }*/
        return length;
    }
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
    if (q != NULL && q->head->value != NULL) {
        list_ele_t *tmp = q->head, *tmp_end;
        int qsize = q_size(q) - 1;
        tmp_end = q->tail;
        while (qsize) {
            while (tmp->next != q->tail)
                tmp = tmp->next;
            q->tail->next = tmp;
            q->tail = tmp;
            tmp = q->head;
            qsize--;
        }
        q->head = tmp_end;
        q->tail->next = NULL;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || q->head->value == NULL)
        return;
    else if (q->head == q->tail)
        return;
    else {
        int size = q_size(q);
        list_ele_t *tmp, *curr, *prev;
        for (int i = size; i > 0; i--) {
            curr = prev = q->head;
            for (int j = 0; j < i - 1 && curr->next; j++) {
                if (strcmp(curr->value, curr->next->value) > 0) {
                    tmp = curr->next;
                    curr->next = tmp->next;
                    tmp->next = curr;
                    if (curr == q->head) {
                        q->head = tmp;
                        prev = tmp;
                    } else {
                        prev->next = tmp;
                        prev = prev->next;
                    }
                } else {
                    curr = curr->next;
                    if (j != 0)
                        prev = prev->next;
                }
            }
        }
        //    free(tmp);
        //    free(curr);
        //    free(prev);
    }
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
