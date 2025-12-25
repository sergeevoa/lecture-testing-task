#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

static int total_tests = 0;
static int passed_tests = 0;

#define RUN_TEST(t) do { \
    total_tests++; \
    if (t()) { \
        printf(#t " PASSED\n"); \
        passed_tests++; \
    } else { \
        printf(#t " FAILED\n"); \
    } \
} while(0)

/* ===== Tests ===== */

bool create_node_test() {
    Node* n = createNode(42);
    if (!n) return false;
    if (n->data != 42) return false;
    if (n->next != NULL) return false;
    free(n);
    return true;
}

bool init_stack_test() {
    Stack s;
    s.top = (Node*)0x1234;
    initStack(&s);
    return s.top == NULL;
}

bool push_pop_test() {
    Stack s;
    initStack(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    if (pop(&s) != 3) return false;
    if (pop(&s) != 2) return false;
    if (pop(&s) != 1) return false;
    if (pop(&s) != -1) return false;

    return isEmpty(&s);
}

bool search_test() {
    Stack s;
    initStack(&s);
    push(&s, 10);
    push(&s, 20);
    push(&s, 30); // top

    Node* n1 = searchByValue(&s, 20);
    if (!n1 || n1->data != 20) return false;

    if (searchByValue(&s, 999) != NULL) return false;

    Node* n2 = searchByIndex(&s, 0);
    if (!n2 || n2->data != 30) return false;

    if (searchByIndex(&s, 10) != NULL) return false;
    if (searchByIndex(&s, -1) != NULL) return false;

    return true;
}

bool is_empty_test() {
    Stack s;
    initStack(&s);
    if (!isEmpty(&s)) return false;

    push(&s, 5);
    if (isEmpty(&s)) return false;

    pop(&s);
    return isEmpty(&s);
}

bool get_top_test() {
    Stack s;
    initStack(&s);
    if (getTop(&s) != NULL) return false;

    push(&s, 7);
    if (!getTop(&s) || getTop(&s)->data != 7) return false;

    push(&s, 9);
    if (getTop(&s)->data != 9) return false;

    return true;
}

int getSize(Stack* s) {
    int count = 0;
    Node* cur = s ? s->top : NULL;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

bool get_size_test() {
    Stack s;
    initStack(&s);
    if (getSize(&s) != 0) return false;

    push(&s, 1);
    push(&s, 2);
    if (getSize(&s) != 2) return false;

    pop(&s);
    if (getSize(&s) != 1) return false;

    return true;
}

bool destroy_stack_test() {
    Stack s;
    initStack(&s);
    push(&s, 1);
    push(&s, 2);

    destroyStack(&s);
    return s.top == NULL;
}

bool null_safety_test() {
    if (isEmpty(NULL) != true) return false;
    if (getTop(NULL) != NULL) return false;
    if (searchByValue(NULL, 1) != NULL) return false;
    if (searchByIndex(NULL, 0) != NULL) return false;
    pop(NULL);
    push(NULL, 1);
    destroyStack(NULL);
    return true;
}

/* ===== Main ===== */

int main(void) {
    printf("Running tests...\n");

    RUN_TEST(create_node_test);
    RUN_TEST(init_stack_test);
    RUN_TEST(push_pop_test);
    RUN_TEST(search_test);
    RUN_TEST(is_empty_test);
    RUN_TEST(get_top_test);
    RUN_TEST(get_size_test);
    RUN_TEST(destroy_stack_test);
    RUN_TEST(null_safety_test);

    printf("Total passed: %d/%d\n", passed_tests, total_tests);
    return (passed_tests == total_tests) ? 0 : 1;
}
