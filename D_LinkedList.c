#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct node *addToEmpty(struct node *head, int data);
struct node *add_at_beg(struct node *head, int data);
struct node *add_at_end(struct node *head, int data);
struct node *add_after_pos(struct node *head, int data, int pos);
struct node *add_before_pos(struct node *head, int data, int pos);
struct node *createList(struct node *head);
struct node *delFirst(struct node *head);
struct node *delLast(struct node *head);
struct node *del_at_pos(struct node *head, int pos);
struct node *getTail(struct node *head);
struct node *shuffle(struct node *head);
struct node *printNodes(struct node *head);
int numberOfNodes(struct node *head);
int getRandomNums(int i);
int commands(int option);

struct node
{
    struct node *prev;
    int data;
    struct node *next;
};

int main()
{
    struct node *head = malloc(sizeof(struct node));
    head = createList(head);
    
    return 0;
}
struct node *printNodes(struct node *head)
{
    printf("\nActual list: ");
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    return head;
}
struct node *addToEmpty(struct node *head, int data)
{
    struct node *temp = malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;

    head = temp;
    return head;
}

struct node *add_at_beg(struct node *head, int data)
{
    struct node *temp = malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;
    temp->next = head;
    head->prev = temp;

    head = temp;
    return head;
}

struct node *add_at_end(struct node *head, int data)
{
    struct node *tp;
    struct node *temp = malloc(sizeof(struct node));
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;
    tp = head;
    while (tp->next != NULL)
    {
        tp = tp->next;
    }
    tp->next = temp;
    temp->prev = tp;

    return head;
}

struct node *add_after_pos(struct node *head, int data, int pos)
{
    struct node *newPos = NULL;
    struct node *temp = head;
    struct node *temp2 = NULL;
    newPos = addToEmpty(newPos, data);

    while (pos != 1)
    {
        temp = temp->next;
        pos--;
    }
    if (temp->next == NULL)
    {
        temp->next = newPos;
        newPos->prev = temp;
    }
    else
    {
        temp2 = temp->next;
        temp->next = newPos;
        temp2->prev = newPos;
        newPos->next = temp2;
        newPos->prev = temp;
    }

    return head;
}

struct node *add_before_pos(struct node *head, int data, int pos)
{
    struct node *newPos = NULL;
    struct node *temp = head;
    struct node *temp2 = NULL;
    newPos = addToEmpty(newPos, data);

    while (pos > 2)
    {
        temp = temp->next;
        pos--;
    }
    if (pos == 1)
    {
        head = add_at_beg(head, data);
    }
    else
    {
        temp2 = temp->next;
        temp->next = newPos;
        temp2->prev = newPos;
        newPos->next = temp2;
        newPos->prev = temp;
    }

    return head;
}

int commands(int option)
{
    do
    {
        printf("\n\nWhat action would you like to perform?\n");
        printf("1. Shuffle\n");
        printf("2. AddBefore\n");
        printf("3. AddAfter\n");
        printf("4. DeleteItem\n");
        printf("Select an option: ");
        scanf_s("%d", &option);
    } while (option < 1 || option > 4);
    return option;
}
struct node *createList(struct node *head)
{

    int n, data, i, d, pos, option;
    char command[5];

    printf("Enter the number of nodes: ");
    scanf_s("%d", &n);

    if (n == 0)
        return head;

    printf("Enter the element for the node 1: ");
    scanf_s("%d", &data);
    head = addToEmpty(head, data);

    for (i = 1; i < n; i++)
    {
        printf("Enter the element for the node %d: ", i + 1);
        scanf_s("%d", &data);
        head = add_at_end(head, data);
    }
    printNodes(head);

    for (;;)
    {
        option = commands(option);
        switch (option)
        {
        case (1):
            head = shuffle(head);
            break;
        case 2:
            printNodes(head);
            printf("\ninsert a number: ");
            scanf_s("%d", &d);
            printf("Insert the position to add before after: ");
            scanf_s("%d", &pos);
            head = add_before_pos(head, d, pos);
            break;
        case 3:
            printNodes(head);
            printf("\ninsert a number: ");
            scanf_s("%d", &d);
            printf("Insert the position to add after: ");
            scanf_s("%d", &pos);
            head = add_after_pos(head, d, pos);
            break;
        case 4:
            printf("\nInsert the position to remove: ");
            scanf_s("%d", &pos);
            head = del_at_pos(head, pos);
        default:
            break;
        }
        printNodes(head);
    }

    return head;
}

struct node *delFirst(struct node *head)
{
    struct node *temp = head;
    head = head->next;
    free(temp);
    temp = NULL;
    head->prev = NULL;

    return head;
}

struct node *delLast(struct node *head)
{
    struct node *temp = head;
    struct node *temp2;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp2 = temp->prev;
    temp2->next = NULL;
    free(temp);

    return head;
}

struct node *del_at_pos(struct node *head, int pos)
{
    struct node *temp = head;
    struct node *temp2 = NULL;

    if (pos == 1)
    {
        head = delFirst(head);
        return head;
    }
    while (pos > 1)
    {
        temp = temp->next;
        pos--;
    }
    if (temp->next == NULL)
        head = delLast(head);
    else
    {
        temp2 = temp->prev;
        temp2->next = temp->next;
        temp->next->prev = temp2;
        free(temp);
        temp = NULL;
    }
    return head;
}

int numberOfNodes(struct node *head)
{
    int count = 0;
    if (head == NULL)
        printf("Linked List is empty");
    struct node *temp = NULL;
    temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

int getRandomNums(int i)
{
    srand(time(NULL));
    int x = 0;
    x = (rand() % i);

    return x;
}

struct node *getTail(struct node *head)
{

    struct node *curr = head;
    struct node *lastnode = NULL;

    while (curr)
    {
        lastnode = curr;
        curr = curr->next;
    }

    return lastnode;
}

struct node *shuffle(struct node *head)
{
    int length = numberOfNodes(head);
    struct node *current = head;
    struct node *temp = NULL;
    int index = 0;

    for (int i = length; i > 0; i--)
    {
        temp = getTail(current);
        index = getRandomNums(i);

        for (int j = 0; j < index; j++)
        {
            current = current->next;
        }

        if (current->next == NULL)
        {
            // do nothing
        }
        else if (current->prev == NULL)
        {
            current->next->prev = NULL;
        }
        else
        {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        if (current->next != NULL)
        {
            current->next = NULL;
            current->prev = temp;
            temp->next = current;
        }

        for (int j = 0; j < length - 1; j++)
        {
            if (current->prev == NULL)
            {
                break;
            }
            current = current->prev;
        }
    }
    return current;
}
