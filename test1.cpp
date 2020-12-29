#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

void swap_pair(node_t **head)
{
    for (node_t **node = head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

void reverse(node_t **head)
{
    node_t *cursor = NULL;
    while (*head) {
        node_t *next = (*head)->next;
        (*head)->next = cursor;
        cursor = *head;
        *head = next;
    }
    *head = cursor;
}

static node_t *rev_resursive(node_t *node)
{
    if (!node->next)
        return node;
    node_t *new_head = rev_resursive(node->next);
    node->next->next = node;
    return new_head;
}

void reverse_recursive(node_t **head)
{
    node_t *old_head = *head;
    *head = rev_resursive(*head);
    old_head->next = nullptr;
}

static void swap(node_t **v1, node_t **v2)
{
    node_t *tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

static void swap_node(node_t **n1_ind, node_t **n2_ind)
{
    if (n1_ind == n2_ind)
        return;
    if ((*n1_ind)->next == *n2_ind) {
        swap(&(*n1_ind), &(*n2_ind)->next);
        swap(&(*n1_ind), &(*n2_ind));
    } else {
        swap(&(*n1_ind), &(*n2_ind));
        swap(&(*n1_ind)->next, &(*n2_ind)->next);
    }
}

void fisher_yates_shuffle(node_t **head)
{
    int list_len = 0;
    node_t *cur = *head;
    while (cur) {
        list_len += 1;
        cur = cur->next;
    }

    while (--list_len) {
        int random_step = rand() % (list_len+1);
        if (random_step > 0) {
            node_t **node = head;
            while (random_step--) {
                node = &(*node)->next;
            }
            swap_node(head, node);
        }
        head = &(*head)->next;
    }
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    swap_pair(&head);
    print_list(head);

    // reverse(&head);
    reverse_recursive(&head);
    print_list(head);

    swap_node(&head, &(head->next));

    for (int i = 0; i < 100; ++i) {
        printf("fisher-yates %d\n", i);
        fisher_yates_shuffle(&head);
        print_list(head);
    }

    return 0;
}