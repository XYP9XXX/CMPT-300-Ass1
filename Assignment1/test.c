#include <stdio.h>
#include "list.h"

bool comparator(void* pItem, void* pComparisonArg) {
    if (pItem == pComparisonArg) {
        return 1;
    }
    return 0;
}

int main(){
    //Create some int values for testing.
    int num = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;
    int num6 = 6;
    int num7 = 7;
    int num8 = 8;
    int num9 = 9;
    int num10 = 10;
    int num11 = 11;
    int num12 = 12;

    printf("---------------------------Test for create---------------------------\n");
    // The size of the list array is 10, we create 11 list here, so only first 10 lists will be
    // created successfully.
    List* list = List_create();
    List* list2 = List_create();
    List* list3 = List_create();
    List* list4 = List_create();
    List* list5 = List_create();
    List* list6 = List_create();
    List* list7 = List_create();
    List* list8 = List_create();
    List* list9 = List_create();
    List* list10 = List_create();
    List* list11 = List_create();
    // If list10 is not empty, meaning it is created successfully as well as the previous 9 lists.
    // And if list11 is empty, meaning it is not created successfully. Let's test.
    if (list10 == NULL) {
        printf("list 10 not being created successfully!\n");
    } else {
        printf("The address of list10 is %p\n", list10);
    }
    if (list11 == NULL) {
        printf("list 11 not being created successfully!\n");
    } else {
        printf("The address of list11 is %p\n", list11);
    }

    printf("---------------------------Test for count---------------------------\n");
    // When  we create a new list and not add any node into it, the count of this list should be 0
    // If we add 1 item after that, the count of the list should be 1. We just use list1 for testing.
    printf("Before add item to list1, the length of list1 is: %d\n", List_count(list));
    List_append(list, &num);
    printf("After add 1 item to list1, the length of list1 is: %d\n", List_count(list));


    printf("---------------------------Test for append---------------------------\n");
    // The purpose of append function is add an item to the end of list. List1 already has one item
    // with value 1, if we append 2, 3 then the items in list1 should be 1, 2, 3. Let's test.
    List_append(list, &num2);
    List_append(list, &num3);
    List_first(list);
    printf("After append 2, 3, list1 has item:   ");
    printf("%d ", *(int*)(List_curr(list)));
    while (List_next(list) != NULL) {
        printf("%d ", *(int*)(List_curr(list)));
    }
    printf("\n");
    // Edge case: if we call append for a list that is NULL, then append will not successfully append,
    // and will return LIST_FAIL(-1).
    int append_state = List_append(list11, &num);
    if (append_state == LIST_FAIL) {
        printf("Append failed!\n");
    }


    printf("---------------------------Test for prepend---------------------------\n");
    // The purpose of prepend function is add an item to the first of list. List1 already has one item
    // with value 1, 2, 3 if we prepend 4 then the items in list1 should be 4 1, 2, 3. Let's test.
    List_first(list);
    List_prepend(list, &num4);
    printf("After prepend 4, list1 has item:   ");
    printf("%d ", *(int*)(List_curr(list)));
    while (List_next(list) != NULL) {
        printf("%d ", *(int*)(List_curr(list)));
    }
    printf("\n");
    // Edge case: if we call prepend for a list that is NULL, then append will not successfully append,
    // and will return LIST_FAIL(-1).
    int prepend_state = List_prepend(list11, &num);
    if (prepend_state == LIST_FAIL) {
        printf("Prepend failed!\n");
    }


    printf("---------------------------Test for List_first---------------------------\n");
    // Calling List_first for a list will set the current pointer of that list to header.
    // List1 has list struct 4->1->2->3, after calling List_first for list1, the current item
    //should be 4. Let's test.
    List_first(list);
    printf("After calling List_first to list1, the current item is: %d\n", *(int*)(List_curr(list)));
    // Edge case: if we call List_first for a list that is NULL, then function will return NULL.
    void* first_state = List_first(list11);
    if (first_state == NULL) {
        printf("Calling List_first to a NULL list return NULL!\n");
    }


    printf("---------------------------Test for List_last---------------------------\n");
    // Calling List_last for a list will set the current pointer of that list to tail.
    // List1 has list struct 4->1->2->3, after calling List_last for list1, the current item
    //should be 3. Let's test.
    List_last(list);
    printf("After calling List_last to list1, the current item is: %d\n", *(int*)(List_curr(list)));
    // Edge case: if we call List_last for a list that is NULL, then function will return NULL.
    void* last_state = List_last(list11);
    if (last_state == NULL) {
        printf("Calling List_last to a NULL list return NULL!\n");
    }


    printf("---------------------------Test for List_next---------------------------\n");
    // Calling List_next will set the current pointer of list to the next item.
    // List1 has list struct 4->1->2->3, if we first call List_first then List_next, the current item should be 1.
    List_first(list);
    List_next(list);
    printf("After calling List_first and List_next to list1, the current item is: %d\n", *(int*)(List_curr(list)));
    // Edge case: if the current pointer is point to tail, then calling List_next will set current pointer as Null
    // and function will return NULL, the state of the list will set to be LIST_OOB_END.
    List_last(list);
    void* next_state = List_next(list);
    if (next_state == NULL) {
        printf("The current pointer before calling List_next is tail, NULL pointer is returned, and current item is set to be beyond end of pList.\n");
    }
    // Edge case: if the current pointer is before the header, then calling List_next will set current pointer to header.
    // The state of the list will set to be 2 means the current state is normal.
    List_first(list);
    List_prev(list);
    List_next(list);
    printf("After calling List_next when current is before the header, current pointer will pointer to its header, which is equal to %d\n", *(int*)(List_curr(list)));
    // Edge case: if we calling List_next to a list which is NULL, function will return NULL.
    next_state = List_next(list11);
    if (next_state == NULL) {
        printf("Calling List_next to a NULL list will return NULL.\n");
    }


    printf("---------------------------Test for List_prev---------------------------\n");
    // Calling List_prev will set the current pointer of list to the prev item.
    // List1 has list struct 4->1->2->3, if we first call List_last then List_prev, the current item should be 2.
    List_last(list);
    List_prev(list);
    printf("After calling List_last and List_prev to list1, the current item is: %d\n", *(int*)(List_curr(list)));
    // Edge case: if the current pointer is point to header, then calling List_next will set current pointer as Null
    // and function will return NULL, the state of the list will set to be LIST_OOB_START.
    List_first(list);
    void* prev_state = List_prev(list);
    if (prev_state == NULL) {
        printf("The current pointer before calling List_prev is header, NULL pointer is returned, and current item is set to be before start of pList.\n");
    }
    // Edge case: if the current pointer is after the tail, then calling List_next will set current pointer to tail.
    // The state of the list will set to be 2 means the current state is normal.
    List_last(list);
    List_next(list);
    List_prev(list);
    printf("After calling List_prev when current is after the tail, current pointer will pointer to its tail, which is equal to %d\n", *(int*)(List_curr(list)));
    // Edge case: if we calling List_prev to a list which is NULL, function will return NULL.
    prev_state = List_prev(list11);
    if (prev_state == NULL) {
        printf("Calling List_prev to a NULL list will return NULL.\n");
    }

    printf("---------------------------Test for List_insert_after---------------------------\n");
    // Inser after function add a new item after the current pointer.
    // List1 now has list struct 4->1->2->3. If we set current = 2 and call insert after for value 5,
    // list1 will become 4->1->2->5->3. Les's test.
    List_last(list);
    List_prev(list);
    List_insert_after(list, &num5);
    List_first(list);
    printf("After List_insert_after item 2 for value 5, list1 has item:   ");
    printf("%d ", *(int*)(List_curr(list)));
    while (List_next(list) != NULL) {
        printf("%d ", *(int*)(List_curr(list)));
    }
    printf("\n");
    // Edge case:
    // 1. If list state is LIST_OOB_END or LIST_OOB_START, means current pointer is not at normal state,
    // in this case we can not add item to the list and just return LIST_FAIL
    // 2. if list is NULL, then we just return LIST_FAIL.
    List_last(list);
    List_next(list);
    int insert_after_state = List_insert_after(list, &num5);
    if (insert_after_state == LIST_FAIL) {
        printf("Current state is not at normal state, can not insert item.\n");
    }
    insert_after_state = List_insert_after(list11, &num5);
    if (insert_after_state == LIST_FAIL) {
        printf("Can not insert item for a NULL list!\n");
    }


    printf("---------------------------Test for List_insert_before---------------------------\n");
    // Inser before function add a new item before the current pointer.
    // List1 now has list struct 4->1->2->5->3. If we set current = 1 and call insert before for value 6,
    // list1 will become 4->6->1->2->5->3. Les's test.
    List_first(list);
    List_next(list);
    List_insert_before(list, &num6);
    List_first(list);
    printf("After List_insert_before item 1 for value 6, list1 has item:   ");
    printf("%d ", *(int*)(List_curr(list)));
    while (List_next(list) != NULL) {
        printf("%d ", *(int*)(List_curr(list)));
    }
    printf("\n");
    // Edge case:
    // 1. If list state is LIST_OOB_END or LIST_OOB_START, means current pointer is not at normal state,
    // in this case we can not add item to the list and just return LIST_FAIL
    // 2. if list is NULL, then we just return LIST_FAIL.
    List_last(list);
    List_next(list);
    int insert_before_state = List_insert_after(list, &num6);
    if (insert_before_state == LIST_FAIL) {
        printf("Current state is not at normal state, can not insert item.\n");
    }
    // insert_before_state = List_insert_after(list11, &num6);
    // if (insert_before_state == LIST_FAIL) {
    //     printf("Can not insert item for a NULL list!\n");
    // }

    printf("---------------------------Test for List_remove---------------------------\n");
    // Remove function remove the current item, and make current pointer point to next item.
    // List1 has list struct 4->6->1->2->5->3. If we set current = 4, then calling remove,
    // list1 will become 6->1->2->5->3. Let's test.
    List_first(list);
    List_remove(list);
    List_first(list);
    printf("After remove first item of list1, list1 has item:   ");
    printf("%d ", *(int*)(List_curr(list)));
    while (List_next(list) != NULL) {
        printf("%d ", *(int*)(List_curr(list)));
    }
    printf("\n");


    printf("---------------------------Test for List_trim---------------------------\n");
    // Trim just delete the last item in the list. list1 now has list struct 6->1->2->5.
    // After calling trim to list1, it will becomes to 6->1. Let's test.
    List_first(list);
    List_trim(list);
    List_first(list);
    printf("After trim for list1, list1 has item:   ");
    printf("%d ", *(int*)(List_curr(list)));
    while (List_next(list) != NULL) {
        printf("%d ", *(int*)(List_curr(list)));
    }
    printf("\n");


    printf("---------------------------Test for List_concat---------------------------\n");
    // The purpose of function concat is put pList2 to the end of pList1.
    // list1 has struct 6->1->2->5, let's create a list2 with 7->8->9.
    List_append(list2,&num7);
    List_append(list2,&num8);
    List_append(list2,&num9);
    // The put list2 to the end of list1, list 1 will become to 6->1->2->5->7->8->9.
    List_concat(list, list2);
    List_first(list);
    printf("After concat for list2 to list1, list1 has item:   ");
    printf("%d ", *(int*)(List_curr(list)));
    while (List_next(list) != NULL) {
        printf("%d ", *(int*)(List_curr(list)));
    }
    printf("\n");


    printf("---------------------------Test for List_search---------------------------\n");
    // This function search if the item and comparisonArg match, list1 has list struct 6->1->2->5->7->8->9.
    // If we search for 8:
    List_first(list);
    if (List_search(list, comparator, &num8) != NULL) {
        printf("We find it!\n");
    } else {
        printf("Not found!\n");
    }

    // If we searh for 10:
    if (List_search(list, comparator, &num10) != NULL) {
        printf("We find it!\n");
    } else {
        printf("Not found!\n");
    }
    return 0;
}