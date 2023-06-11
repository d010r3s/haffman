#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NODE{ //структура дерева
    char sym;
    int frequency;
    int value;
    int data;
    int inform_sym;
    struct NODE * left;
    struct NODE * right;
    struct NODE * next;

}NODE;
typedef struct list_of_freq{
    char sym;
    int value;
    struct list_of_freq * next;
}list_of_freq;

void add_to_list_from_array(list_of_freq ** pphead, int value, char sym){
    list_of_freq **pp = pphead, *pnew;
    while(*pp){
        if (value < ((**pp).value)){
            break;
        }
        else{
            pp = &((*pp)->next);
        }
    }
    pnew = (list_of_freq*)malloc(sizeof(list_of_freq));
    pnew -> value = value;
    pnew->sym = sym;
    pnew->next = *pp;
    *pp = pnew;
}
void add_to_list(NODE ** pphead, int frequency){
    NODE **pp = pphead, *pnew;
    while(*pp){
        if (frequency < ((**pp).frequency)){
            break;
        }
        else{
            pp = &((*pp)->next);
        }
    }
    pnew = (NODE*)malloc(sizeof(NODE));
    pnew -> frequency = frequency;
    pnew->next = *pp;
    *pp = pnew;
}


void print(NODE * phead){
    NODE * p = phead;
    while(p){
        printf("%d %c\n", p->value, p->data);
        p = p->next;
    }
}



NODE * new_node(NODE * left,  NODE * right){
    NODE * new_node = (NODE*)malloc(sizeof(NODE));
    new_node->frequency = left->frequency + right->frequency;
    new_node->left = NULL;

    new_node->right = NULL;

    new_node->sym = 0;
    //new_node->next = NULL;
    new_node->inform_sym = 0;


    return new_node;
}




/*void add_to_list_from_tree(NODE * head){
    //while(head && head->next){
        NODE * left = head;
        NODE * right = head->next;
        add_to_list(&(head->next->next), new_node(left, right)->frequency);

        head = head->next->next;
    //}
    //return head;
}*/

void treeprint(NODE *head) {
    if (head!=NULL) {
        if(head->left){
            treeprint(head->left);
        }
        printf("%d\n", head->frequency);
        if(head->right){
            treeprint(head->right);
        }
    }
}

int main(){
    FILE * file;
    file = fopen("file.txt", "rb");
    if(!file){
        return -1;
    }
    long int len = 183;
    int frequency[191] = {0};
    for (int i = 0; i < len; i++){
        int index = fgetc(file);
        frequency[index] += 1;
    }

    NODE * head = NULL;
    list_of_freq * head_f = NULL;
    for (int i =0; i < 191; i++){
        if (frequency[i] > 0){
            add_to_list_from_array(&head_f, frequency[i], (char)i);
            add_to_list(&head, frequency[i]);
        }
    }



    NODE * left = head;
    NODE * right = head->next;
    NODE * top;
    while (head->next != NULL) {


        top = new_node(left, right);
        top->left = left;
        top->right = right;

        add_to_list(&(head->next->next), left->frequency + right->frequency);

        head = head->next->next;
        left = head;
        right = head->next;
        if (top->frequency == head->frequency){
            left = top;
            right = head->next;
        }
        else if(top->frequency == head->next->frequency){
            right = head;
            left = top;
        }

    }
    treeprint(top);


    fclose(file);

}