
#include <stdio.h>
#include <malloc.h>

#define ERROR (NULL)

struct node_saver{
    /*
     * This structure saves all the fields the are common to all the nodes from the node structure.
     */
    int sum;
    int length;
    struct node *head;
    struct node *last;
};

struct node{
    /*
     * The struct node.
     * Has: value (int/union node_item), ptr to the next node, ptr to the previous node, ptr to the first node,
     * and ptr to the last node.
     */
    int value;
    struct node *next;
    struct node *previous;
    struct node_saver *common_fields;
};

struct node* starting_list(int value)
{
    struct node node_t;
    struct node_saver *node_saver_ptr;

    node_saver_ptr = malloc(sizeof(*node_saver_ptr));
    if(node_saver_ptr == NULL){
        return ERROR;
    }
    node_saver_ptr->head = malloc(sizeof(node_t));
    if(node_saver_ptr->head == NULL){
        return ERROR;
    }

    node_t.common_fields = node_saver_ptr;
    node_t.value = value;
    node_t.common_fields->sum = value;
    node_t.common_fields->length = 1;
    node_t.common_fields->last = node_t.common_fields->head;
    return node_t.common_fields->head;
}

void destroy_list(struct node node_t)
{
    struct node *first_node = node_t.common_fields->head;
    first_node->common_fields->sum = 0;
    free(first_node->common_fields->head);
    first_node->common_fields->last = NULL;
    first_node->common_fields->length = 0;
    while (first_node->next != NULL) {
        first_node->previous = NULL;
        first_node->value = 0;
        first_node = first_node->next;
        first_node->previous->next = NULL;
    }
    first_node->value = 0;
    first_node->previous = NULL;
}

void add_node(struct node add_to_node, struct node *node_to_add)
{
    // CHANGE
    node_to_add->previous = add_to_node.common_fields->last;
    add_to_node.common_fields->last->next = node_to_add;
    add_to_node.common_fields->last = node_to_add;
    node_to_add->common_fields = add_to_node.common_fields;
    node_to_add->common_fields->sum = add_to_node.common_fields->sum + node_to_add->value;
    ++node_to_add->common_fields->length;
}

void del_node(struct node *node_to_del)
{
    node_to_del->previous->next = node_to_del->next;
    node_to_del->common_fields->sum = node_to_del->common_fields->sum - node_to_del->value;
    node_to_del->value = 0;
    node_to_del->next = NULL;
    node_to_del->previous = NULL;
    --node_to_del->common_fields->length;
    node_to_del->common_fields = NULL;
}

int get_len(struct node node_t)
{
    return node_t.common_fields->length;
}

struct node* get_first(struct node node_t)
{
    return node_t.common_fields->head;
}

struct node* get_last(struct node node_t)
{
    return node_t.common_fields->last;
}

struct node* get_next(struct node *node_t)
{
    return node_t->next;
}

struct node* get_previous(struct node *node_t)
{
    return node_t->previous;
}

int get_value(struct node *node_t)
{
    return (*node_t).value;
}

float get_avg(struct node node_t)
{
    return (float)(node_t.common_fields->sum)/(node_t.common_fields->length);
}

int main() {
    struct node *head = starting_list(8);
    printf("value: %d\n", head);
    struct node *second = starting_list(10);
    printf("value: %d\n", get_value(second));
    printf("problem\n");
    add_node(*head, second);
    printf("no problem\n");
    printf("the avg of the list is %f/n", get_avg(*head));
    return 0;
}
