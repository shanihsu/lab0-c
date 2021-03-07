#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q) {
        while (q->head) {
            list_ele_t *tmp;
            tmp = q->head;
            free(tmp->value);
            q->head = tmp->next;
            free(tmp);
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
    /* TODO: What should you do if the q is NULL? */
    if (!q)
        return false;
    if (!(newh = malloc(sizeof(list_ele_t))))
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    size_t len = strlen(s) + 1;
    if (!(newh->value = malloc(len * sizeof(char)))) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, len);
    newh->next = q->head;
    if (!q->head)
        q->tail = newh;
    q->head = newh;
    q->size++;
    return true;
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
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newh;
    if (!q)
        return false;
    if (!(newh = malloc(sizeof(list_ele_t))))
        return false;
    size_t len = strlen(s) + 1;
    if (!(newh->value = malloc(len * sizeof(char)))) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, len);
    newh->next = NULL;
    if (!q->head) {
        q->head = newh;
    } else {
        q->tail->next = newh;
    }
    q->tail = newh;
    q->size++;
    return true;
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
    if (!q || !q->head)
        return false;
    size_t len = strlen(q->head->value);
    if (sp) {
        if (len < bufsize) {
            memcpy(sp, q->head->value, len);
            sp[len] = '\0';
        } else {
            memcpy(sp, q->head->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        }
    }
    list_ele_t *tmp;
    tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head) {
        return 0;
    }
    return q->size;
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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!(!q || !q->head || !q->head->next)) {
        list_ele_t *current = q->head->next;
        list_ele_t *prev = q->head;
        prev->next = NULL;
        q->tail = prev;
        q->head = current;
        while (q->head->next) {
            current = q->head->next;
            q->head->next = prev;
            prev = q->head;
            q->head = current;
        }
        q->head->next = prev;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head || !q->head->next) {
        return;
    }
    q->head = mergeSortList(q->head);
    list_ele_t *tmp = q->head;
    while (tmp->next) {
        tmp = tmp->next;
    }
    q->tail = tmp;
}

list_ele_t *merge(list_ele_t *lhs, list_ele_t *rhs)
{
    list_ele_t *head = NULL, *tmp = NULL;
    if (lhs && rhs) {
        if (strcmp(lhs->value, rhs->value) < 0) {
            head = lhs;
            lhs = lhs->next;
        } else {
            head = rhs;
            rhs = rhs->next;
        }
    }
    tmp = head;
    while (lhs && rhs) {
        if (strcmp(lhs->value, rhs->value) < 0) {
            tmp->next = lhs;
            tmp = tmp->next;
            lhs = lhs->next;
        } else {
            tmp->next = rhs;
            tmp = tmp->next;
            rhs = rhs->next;
        }
    }
    if (lhs)
        tmp->next = lhs;
    if (rhs)
        tmp->next = rhs;
    return head;
}

list_ele_t *mergeSortList(list_ele_t *head)
{
    // merge sort
    if (!head || !head->next)
        return head;
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
    list_ele_t *lhs = mergeSortList(head);
    list_ele_t *rhs = mergeSortList(fast);
    // merge sorted lhs and sorted rhs
    return merge(lhs, rhs);
}
