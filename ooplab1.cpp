#include <stdlib.h>
#include <assert.h>

typedef enum {
    false,
    true
} bool;

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} stack_t;

stack_t make_empty() {
    stack_t stack;
    stack.data = NULL;
    stack.size = 0;
    stack.capacity = 0;
    return stack;
}

stack_t make_of_size(size_t size) {
    stack_t stack;
    stack.data = (int*)malloc(size * sizeof(int));
    stack.size = 0;
    stack.capacity = size;
    return stack;
}

stack_t make_from_array(const int arr[], size_t size) {
    stack_t stack = make_of_size(size);
    for (size_t i = 0; i < size; ++i) {
        stack.data[i] = arr[i];
    }
    stack.size = size;
    return stack;
}

stack_t make_copy(const stack_t* src) {
    stack_t dest = make_of_size(src->capacity);
    for (size_t i = 0; i < src->size; ++i) {
        dest.data[i] = src->data[i];
    }
    dest.size = src->size;
    return dest;
}

void clear(stack_t* stack) {
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}

int at(const stack_t* stack, int index) {
    if (index < 0) {
        index = (int)stack->size + index;
    }
    if (index < 0 || index >= (int)stack->size) {
        return (index < 0) ? stack->data[0] : stack->data[stack->size - 1];
    }
    return stack->data[index];
}

bool is_equal(const stack_t* a, const stack_t* b) {
    if (a->size != b->size) return false;
    for (size_t i = 0; i < a->size; ++i) {
        if (a->data[i] != b->data[i]) return false;
    }
    return true;
}

int main() {
    int array[] = { 1, 4, 7, 9 };

    stack_t a = make_from_array(array, 4);

    assert(9 == at(&a, 3));
    assert(9 == at(&a, -1));
    assert(9 == at(&a, 13));
    assert(1 == at(&a, -13));

    stack_t b = make_copy(&a);

    assert(is_equal(&a, &b));

    clear(&a);
    clear(&b);

    return 0;
}
