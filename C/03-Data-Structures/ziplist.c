//Do not modify starter code
//You may add helper functions if needed

/*
reorded a non-empty, singly linked list. Given a list of K nodes, the goal
is to rearrange its elements in such a way that the first node is followed by the last node,
then the second node is followed by the second-last node, and so on, until the list has been
completely rearranged.

Formally, the transformation produces the following sequence:
1st node → Kth node → 2nd node → (K−1)th node → 3rd node → (K−2)th node → . . .
Example 1
1 → 2 → 3 → 4 → 5 → 6
After zipping:
1 → 6 → 2 → 5 → 3 → 4
Example 2
1 → 2 → 3 → 4 → 5
After zipping:
1 → 5 → 2 → 4 → 3

pattern I see: 
  a loop from the first index to the half index, and then take the last - the index were on as the next node
  be careful to store the previous next node in the lop so we dont lose it.

Do not modify starter code. You may add additional helper functions if needed
*/

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
  int data;
  struct Node *next;
} Node;

// Create a new node
Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

// Insert at end
void insertEnd(Node **head, int data) {
  Node *newNode = createNode(data);
  if (!*head) {
    *head = newNode;
    return;
  }
  Node *temp = *head;
  while (temp->next)
    temp = temp->next;
  temp->next = newNode;
}

// Print list
void printList(Node *head) {
  while (head) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

Node *find_prev(Node *head, int v){
  while (head != NULL && head -> next != NULL){ //while we have things in our list and we have another node
    if (head -> data == v){
      return head;
    }
    if (head -> next -> data == v){ //if the current node value of next is equal to the one im trying to find 
      return head; // return it
    }
    head = head -> next; //otherwise move to the next one

  }
  return head; //return the node we're on if theres no previous
}
int amount(Node *head){
  int count = 0;
  while(head -> next!= NULL){
    count ++;
    head = head -> next;
  }
  return count;
}
void zipList(Node **headRef) {
  /*
  Example 1
  1 → 2 → 3 → 4 → 5 → 6
  After zipping:
  1 → 6 → 2 → 5 → 3 → 4
  Example 2
  1 → 2 → 3 → 4 → 5
  After zipping:
  1 → 5 → 2 → 4 → 3
  pattern I see: 
  a loop from the first index to the half index, and then take the last - the index were on as the next node
  be careful to store the previous next node in the lop so we dont lose it.
  
  */  
  // fill code here
  Node *head = *headRef;
  int len = amount(*headRef);

  for(int i = 0; i < len/2; i++){
    Node *current_next = head -> next;
    Node *temp = head;
    
    while(temp -> next != NULL){
      temp = temp -> next;
    }
    Node *prev = find_prev(*headRef, temp->data);
    prev -> next = NULL;
    head -> next = temp;
    temp -> next = current_next;
    head = current_next;
  }

}

int main(int argc, char *argv[]) {
  Node *head = NULL;

  if (argc < 2) {
    printf("Usage: %s <list of integers>\n", argv[0]);
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    int val = atoi(argv[i]);
    insertEnd(&head, val);
  }

  printf("Original list:\n");
  printList(head);


  zipList(&head);

  printf("Zipped list:\n");
  printList(head);
  
 //free the mallocs
  while (head != NULL) {
    Node *temp = head;
    head = head->next;
    free(temp);
}

  
  return 0;
}
