#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List list_global[10]; // The global list array to store list header, maximum size is 10.
Node node_global[100]; // The global node array to store node, maximum size is 100.
int list_index = 0; // Index of next list to be created.
int node_index = 0; // Index of next node to be created.
List* current_list; // Pointer to the current list that is available.
bool first = true; // The booling variable to test if it is the first time create the list.

List* List_create(){
    // First calling this function we need link all list in the list array for our furthur purpose.
    if (first) {
        for (int i = 0; i < LIST_MAX_NUM_HEADS - 1; i++) {
            list_global[i].next_Available = &list_global[i + 1];
            current_list = &list_global[0];
            first = false;
        }
    }

    // It has two cases:
    // Case1: List array already full, so we can not add more list to the list array.

    if (list_index >= LIST_MAX_NUM_HEADS) {
        return NULL;
    }

    // Case2: List array is not full, then we create new list to the current array position.
    List* curr = current_list;
    curr->length = 0;
    curr->header = NULL;
    curr->tail = NULL;
    curr->state = 2;
    current_list = current_list->next_Available;
    list_index ++;
    return curr;
}

int List_count(List* pList){
    // If pList is not NULL, we return the length of the list.
    if (pList != NULL) {
        return pList->length;
    }else {
        return 0; // If pList is NULL, we return 0.
    }
}

int List_append(List* pList, void* pItem){
    // If pList is null, then return fail.
    if (pList == NULL || pItem == NULL) {
        return LIST_FAIL;
    } else {
        // At first we create new node to the node array.
        node_global[node_index].item = pItem;
        node_global[node_index].next = NULL;
    }

    // If plist length is 0, means this is the first node in the list. We need to set this
    // node's haedAdd and tailAdd.
    if (pList->length == 0){
        pList->current = &node_global[node_index];
        pList->header = &node_global[node_index];
        pList->tail = &node_global[node_index];
        node_global[node_index].headAdd = &(pList->header);
        node_global[node_index].tailAdd = &(pList->tail);
        pList->length ++;
        node_index ++;
        pList->state = 2;
        return 0;
    } else{
        // If pList length is not 0, then we just add node to the end of the list as
        // normal and set thie node's tailAdd is enough(because this node is tail after append).
        Node* tail = pList->tail;
        tail->tailAdd = NULL;
        node_global[node_index].before = tail;
        pList->current = &node_global[node_index];
        pList->tail->next = &node_global[node_index];
        pList->tail = &node_global[node_index];
        node_global[node_index].tailAdd = &(pList->tail);
        pList->length ++;
        node_index ++;
        pList->state = 2;
        return 0;
    }
}

int List_prepend(List* pList, void* pItem){
    // If pList is null, then return fail.
    if (pList == NULL || pItem == NULL) {
        return LIST_FAIL;
    }else {
        // At first we create new node to the node array.
        node_global[node_index].item = pItem;
        node_global[node_index].before = NULL;
    }   

    // If plist length is 0, means this is the first node in the list. We need to set this
    // node's haedAdd and tailAdd.
    if (pList->length == 0){
        node_global[node_index].headAdd = &(pList->header);
        node_global[node_index].tailAdd = &(pList->tail);
        node_global[node_index].next = NULL;
        pList->current = &node_global[node_index];
        pList->header = &node_global[node_index];
        pList->tail = &node_global[node_index];
        pList->length ++;
        node_index ++;
        pList->state = 2;
        return LIST_SUCCESS;
    } else{
        // If pList length is not 0, then we just add node to the head of the list as
        // normal and set thie node's headAdd is enough(because this node is tail after append).
        Node* header = pList->header;
        header->headAdd = NULL;
        node_global[node_index].next = header;
        pList->current = &node_global[node_index];
        pList->header->before = &node_global[node_index];
        pList->header = &node_global[node_index];
        node_global[node_index].headAdd = &(pList->header);
        pList->length ++;
        node_index ++;
        pList->state = 2;
        return LIST_SUCCESS;
    }
}

void* List_first(List* pList){
    // If pList is null, then return fail.
    if (pList == NULL) {
        return NULL;
    } else{
        // Set current to the header of the list, and return its item.
        Node* node = pList->header;
        pList->current = node;
        pList->state = 2;
        return node->item;
    }
}

void* List_last(List* pList) {
    // If pList is null, then return fail.
    if (pList == NULL) {
        return NULL;
    } else{
        // Set current to the tail of the list, and return its item.
        Node* node = pList->tail;
        pList->current = node;
        pList->state = 2;
        return node->item;
    }
}

void* List_next(List* pList) {
    // If pList is null, then return fail.
    if (pList == NULL) {
        return NULL;
    } else if (pList->current == pList->tail) {
        // If current is the tail of list, then set current point ot NULL
        // and list state LIST_OOB_END.
        // Then return NULL.
        pList->state = LIST_OOB_END;
        pList->current = NULL;
        return NULL;
    } else if (pList->state == LIST_OOB_START) {
        // If list state is LIST_OOB_START, then set list state to 2(means normal state)
        // and set current to the header of the list.
        pList->state = 2;
        pList->current = pList->header;
        return pList->current->item;
    } else {
        // General case, just set current to current next.
        pList->state = 2;
        pList->current = pList->current->next;
        return pList->current->item;
    }
}

void* List_prev(List* pList) {
    // If pList is null, then return fail.
    if (pList == NULL) {
        return NULL;
    } else if (pList->current == pList->header) {
        // If current is the header of list, then set current point ot NULL
        // and list state LIST_OOB_START.
        // Then return NULL.
        pList->current = NULL;
        pList->state = LIST_OOB_START;
        return NULL;
    } else if (pList->state == LIST_OOB_END) {
        // If list state is LIST_OOB_END, then set list state to 2(means normal state)
        // and set current to the tail of the list.
        pList->state = 2;
        pList->current = pList->tail;
        return pList->current->item;
    } else {
        // General case, just set current to current before.
        pList->state = 2;
        pList->current = pList->current->before;
        return pList->current->item;
    }
}

void* List_curr(List* pList) {
    // If list is NULL, return NULL.
    if (pList == NULL) {
        return NULL;
    } else {
        // Else retuen the address of current item.
        return pList->current->item;
    }
}

int List_insert_after(List* pList, void* pItem) {
    // If list is NULL of state is LIST_OOB_END(after end),
    // then insert fail, return LIST_FAIL.
    if (pList == NULL || pList->state == LIST_OOB_END) {
        return LIST_FAIL;
    } else if (pList->current == pList->tail){
        // If current is the tail of the list, calling append function.
        List_append(pList, pItem);
    } else if (node_index >= LIST_MAX_NUM_NODES) {
        // If node list is full, return LIST_FAIL.
        return LIST_FAIL;
    }
    else {
        // Create node to the node array.
        node_global[node_index].item = pItem;

        // Get next item.
        Node* next = pList->current->next;

        // Link current item to the new item
        node_global[node_index].before = pList->current;
        pList->current->next = &node_global[node_index];

        // Link current next item to the new item
        node_global[node_index].next = next;
        next->before = &node_global[node_index];
        pList->current = &node_global[node_index];
        pList->length ++;
        node_index ++;
        // If state is LIST_OOB_START, reset header.
        if (pList->state == LIST_OOB_START) {
            pList->header = &node_global[node_index];
        }
        pList->state = 2;
        return LIST_SUCCESS;
    }
}

int List_insert_before(List* pList, void* pItem) {
    // If list is NULL of state is LIST_OOB_START(before start),
    // then insert fail, return LIST_FAIL.
    if (pList == NULL || pList->state == LIST_OOB_START) {
        return LIST_FAIL;
    } else if (pList->current == pList->header){
        // If current is the header of the list, calling prepend function.
        List_prepend(pList, pItem);
    } else if (node_index >= LIST_MAX_NUM_NODES){
        // If node list is full, return LIST_FAIL.
        return LIST_FAIL;
    } else {
        // Create node to the node array.
        node_global[node_index].item = pItem;

        // Get prev item.
        Node* prev = pList->current->before;

        // Link current item to the new item
        node_global[node_index].next = pList->current;
        pList->current->before = &node_global[node_index];

        // Link current prev item to the new item
        node_global[node_index].before = prev;
        prev->next = &node_global[node_index];
        pList->length ++;
        pList->current = &node_global[node_index];

        // If state is LIST_OOB_END, reset tail.
        if (pList->state == LIST_OOB_END) {
            pList->tail = &node_global[node_index];
        }
        pList->state = 2;
        node_index ++;
        return LIST_SUCCESS;
    }
}

void* List_remove(List* pList) {
    // Remove has 5 cases:
    //Case1: if list = NULL or current = NULL of state is not at normal case, then Return NULL.
    if (pList == NULL || pList->current == NULL || pList->state == LIST_OOB_END || pList->state == LIST_OOB_START) {
        return NULL;
    }   else if (pList->length == 1){
        // Case2: list only has 1 item
        Node* curr = pList->current;
        pList->header = NULL;
        pList->state = 2;
        pList->tail = NULL;
        pList->current = NULL;
        curr->before = node_global[node_index - 1].before;
        curr->next = node_global[node_index - 1].next;
        curr->item = node_global[node_index - 1].item;
        // If the latest node of node array is the tail of any list,
        // then we need to change address of tail of that list.
        if (node_global[node_index - 1].tailAdd != NULL) {
            node_global[node_index - 1].before->next= curr;
            *node_global[node_index - 1].tailAdd = curr;
        } else {
            // Else we link the node of latest node and its next node
            curr->next->before = curr;
        }
        // If the latest node of node array is the header of any list,
        // then we need to change address of header of that list.
        if (node_global[node_index - 1].headAdd != NULL) {
            node_global[node_index - 1].next->before = curr;
            *node_global[node_index - 1].headAdd = curr;
        } else {
            // Else we link the node of latest node and its prev node
            node_global[node_index - 1].before->next= curr;
        }
    } else if (pList->current == pList->header) {
        // Case3: if current is the header of the list
        Node* curr = pList->current;
        void* item = curr->item;
        Node* next = pList->current->next;
        next->before = NULL;
        next->headAdd = &next;
        //We need to reset header of the list.
        pList->header = next;
        if (next == &node_global[node_index - 1]) {
            pList->header = curr;
        }
        curr->before = node_global[node_index - 1].before;
        curr->next = node_global[node_index - 1].next;
        curr->item = node_global[node_index - 1].item;
        if (node_global[node_index - 1].tailAdd != NULL) {
            node_global[node_index - 1].before->next= curr;
            *node_global[node_index - 1].tailAdd = curr;
        } else {
            curr->next->before = curr;
        }
        if (node_global[node_index - 1].headAdd != NULL) {
            node_global[node_index - 1].next->before = curr;
            *node_global[node_index - 1].headAdd = curr;
        } else {
            node_global[node_index - 1].before->next= curr;
        }

        // Free node array of that node.
        node_global[node_index - 1].before = NULL;
        node_global[node_index - 1].next = NULL;
        node_global[node_index - 1].item = NULL;
        node_global[node_index - 1].headAdd = NULL;
        node_global[node_index - 1].tailAdd = NULL;
        pList->length --;
        pList->current = next;
        node_index --;
        pList->state = 2;
        return item;
    } else if (pList->current == pList->tail) {
        // Case4: eIf current is the tail of the list, then just call trim.
        void* item = List_trim(pList);
        return item;
    } else {
        // Case5: normal case, just remove the item.
        Node* curr = pList->current;
        Node* prev = pList->current->before;
        Node* next = pList->current->next;
        curr->before = node_global[node_index - 1].before;
        curr->next = node_global[node_index - 1].next;
        curr->item = node_global[node_index - 1].item;
        if (node_global[node_index - 1].tailAdd != NULL) {
            node_global[node_index - 1].before->next= curr;
            *node_global[node_index - 1].tailAdd = curr;
        } else {
            curr->next->before = curr;
        }
        if (node_global[node_index - 1].headAdd != NULL) {
            node_global[node_index - 1].next->before = curr;
            *node_global[node_index - 1].headAdd = curr;
        } else {
            node_global[node_index - 1].before->next= curr;
        }
        prev->next = next;
        next->before = prev;
        pList->length --;
        node_global[node_index - 1].before = NULL;
        node_global[node_index - 1].next = NULL;
        node_global[node_index - 1].item = NULL;
        node_global[node_index - 1].headAdd = NULL;
        node_global[node_index - 1].tailAdd = NULL;
        node_index --;
        pList->current = next;
        pList->state = 2;
        return curr->item;
    }
}

void* List_trim(List* pList) {
    // If list is NULL of current is NULL, return NULL.
    if (pList == NULL || pList->current == NULL) {
        return NULL;
    } else if (pList->length == 1) {
        // // if list only has 1 item, we just remove that item and reset plist header, tail and so on.
        void* item = pList->current->item;
        pList->header = NULL;
        pList->tail = NULL;
        pList->current = NULL;
        pList->length --;
        node_global[node_index - 1].before = NULL;
        node_global[node_index - 1].next = NULL;
        node_global[node_index - 1].item = NULL;
        node_global[node_index - 1].headAdd = NULL;
        node_global[node_index - 1].tailAdd = NULL;
        node_index --;
        pList->state = 2;
        return item;
    } else {
        Node* tail = pList->tail;
        Node* prev = pList->tail->before;
        void* item = tail->item;
        if (&node_global[node_index - 1] == pList->header) {
            // If the latest node add to node array is the header of list,
            // we need to reset header position to current position.
            tail->before = node_global[node_index - 1].before;
            tail->next = node_global[node_index - 1].next;
            tail->item = node_global[node_index - 1].item;
            node_global[node_index - 1].before = NULL;
            node_global[node_index - 1].next = NULL; 
            node_global[node_index - 1].item = NULL;
            node_global[node_index - 1].headAdd = NULL;
            node_global[node_index - 1].tailAdd = NULL;
            tail->next->before = tail;
            tail->before = NULL;
            pList->header = tail;
            prev->next = NULL;
            pList->tail = prev;
            pList->current = prev;
            pList->length --;
            node_index --;
            pList->state = 2;
            return item;
        } else {
            if (node_global[node_index - 1].next != NULL){
                // latest node add to node array is not the tail of the list.
                bool ifTrue = prev == &node_global[node_index - 1];
                tail->before = node_global[node_index - 1].before;
                tail->next = node_global[node_index - 1].next;
                tail->item = node_global[node_index - 1].item;
                tail->next->before = tail;
                if (ifTrue){
                    // if latest node add to node array is the prev of the list tail, then
                    // we set tail to the prev after trim.
                    pList->tail = tail;
                    pList->tail->next = NULL;
                } else {
                    pList->tail = prev;
                    prev->next = NULL;
                    tail->before = NULL;
                }
                if (node_global[node_index - 1].headAdd != NULL) {
                    *node_global[node_index - 1].headAdd = tail;
                }
                if (node_global[node_index - 1].tailAdd != NULL) {
                    *node_global[node_index - 1].tailAdd = tail;
                } else {
                    node_global[node_index - 1].before->next= tail;
                }
                // Free node array of that node.
                node_global[node_index - 1].before = NULL;
                node_global[node_index - 1].next = NULL; 
                node_global[node_index - 1].item = NULL;
                node_global[node_index - 1].headAdd = NULL;
                node_global[node_index - 1].tailAdd = NULL;
                pList->current = pList->tail;
                pList->length --;
                node_index --;
                pList->state = 2;
                return item;
            }else{
                // The general case of trim.
                tail->before = node_global[node_index - 1].before;
                tail->next = node_global[node_index - 1].next;
                tail->item = node_global[node_index - 1].item;
                if (node_global[node_index - 1].headAdd != NULL) {
                    *node_global[node_index - 1].headAdd = tail;
                }
                if (node_global[node_index - 1].tailAdd != NULL) {
                    Node* l2Prev = node_global[node_index - 1].before;
                    l2Prev->next = tail;
                    *node_global[node_index - 1].tailAdd = tail;
                    tail->before = l2Prev;
                }
                node_global[node_index - 1].before = NULL;
                node_global[node_index - 1].next = NULL; 
                node_global[node_index - 1].item = NULL;
                node_global[node_index - 1].headAdd = NULL;
                node_global[node_index - 1].tailAdd = NULL;
                prev->next = NULL;
                pList->tail = prev;
                pList->current = prev;
                pList->length --;
                node_index --;
                pList->state = 2;
                return item;
            }
        }
    }
}

void List_concat(List* pList1, List* pList2) {
    // If any list is NULL, just return.
    if (pList1 == NULL || pList2 == NULL) {
        return;
    }
    if (pList2 == &list_global[list_index - 1]) {
        // If latest list add to list array is corresponding to pList2,
        Node* tail = pList1->tail;
        Node* header = pList2->header;
        tail->next = header;
        pList1->tail = pList2->tail;
        pList1->length += pList2->length;
        header->before = tail;
        header->headAdd = NULL;
        tail->tailAdd = NULL;
        // Set current list to the position of plist2 in the list array.
        pList2->next_Available = current_list;
        current_list = pList2;
        // Free that position.
        list_global[list_index - 1].current = NULL;
        list_global[list_index - 1].header = NULL;
        list_global[list_index - 1].length = 0;
        list_global[list_index - 1].tail = NULL;
        list_index --;
    } else {
        Node* tail = pList1->tail;
        Node* header = pList2->header;
        tail->next = header;
        pList1->tail = pList2->tail;
        pList1->length += pList2->length;
        header->before = tail;
        header->headAdd = NULL;
        tail->tailAdd = NULL;
        pList2->next_Available = current_list;
        current_list = pList2;
        pList2->current = NULL;
        pList2->header = NULL;
        pList2->tail = NULL;
        pList2->length = 0;
        pList2->state = 2;
        list_index --;
    }
}

void List_free(List* pList, FREE_FN pItemFreeFn) {
    if (pList == NULL) {
        return;
    }
    // First set the curren list to the position of plist, which will be delete then.
    current_list = pList;
    Node* curr = pList->header;
    // From header traverse the plist and use pItemFreeFn = free the node.
    while (curr != NULL) {
        pItemFreeFn (curr->item);
        curr = curr->next;
    }
    pList->current = NULL;
    pList->header = NULL;
    pList->tail = NULL;
    pList->length = 0;
    pList->state = 2;
}

void* List_search(List* pList,  COMPARATOR_FN pComparator, void* pComparisonArg) {
    // If plist is NULL, just return.
    if (pList->state == LIST_OOB_START) {
        List_first(pList);
    }
    // Traverse the list and use pComparator to compare the current item with pComparisonArg.
    while (pList->current != NULL) {
        bool ifMatch = pComparator(pList->current->item, pComparisonArg);
        if (ifMatch) {
            return List_curr(pList);
        }
        List_next(pList);
    }
    return NULL;
}