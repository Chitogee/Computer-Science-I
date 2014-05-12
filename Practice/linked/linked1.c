#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Link.h"

struct linked * create( int val ){
    struct linked * made = (struct linked *)malloc(sizeof(struct linked));
    made->next = NULL ;
    made->data = val ;
    return made ;
}

/*  Insertion
 *   - Insert front
 *   - Insert back
 *   - Insert between
 */
struct linked * insertFront(struct linked * front, int data){
    if ( front != NULL ){
        struct linked * newFront = create(data);
        newFront->next = front ;
        return newFront ;
    }
    else{
        return create(data);
    }
}
// returns 2 for created and inserted, 1 for insertion point val not found, 0 for fail
int insertBetween(struct linked * front, int searchVal, int insertVal ){
    if ( front != NULL ){
        if (front->data == searchVal ){
            struct linked * list = create(insertVal);
            if (front->next != NULL ){
                list->next=front->next;
                front->next = list ;
                return 2 ;
            }
            else{
                front->next = list ;
                return 1 ;
            }
        }
        else{
            insertBetween(front->next,searchVal,insertVal);
        }
    }
    else {
        return 0;
    }
}

struct linked * insertBack(struct linked * front, int data){
    if ( front == NULL ){
        return create(data);
    }
    else{
        if ( front->next != NULL ){
            insertBack(front->next,data);
        }
        else{
            front->next = create(data);
        }
    }
    return front ; // Last operation should be the front if called last
}
struct linked * insertSorted(struct linked * front, int val){
    if ( front != NULL ){
        if ( front->data < val ){
            if ( front->next != NULL ){
                if ( front->next->data > val ){
                    struct linked * insert = create(val);
                    insert->next = front->next ;
                    front->next = insert ;
                }
                else{
                    insertSorted(front->next,val);
                }
            }

            else{
                front->next = create(val);
            }
        }
    }
    else {
        return create(val);
    }
    return front ;
}
void printLinked(struct linked * front){
    if ( front == NULL ){
        printf("-->NULL\n");
        return ;
    }
    printf("%d ",front->data);
    printLinked(front->next);

}
int main(){
    int i ;

    struct linked * front = create(5);
    /*
     * Testing InsertBack
     */
    //for ( i = 0 ; i < 10 ; i++ ) insertBack(front,i%13);
    //printLinked(front);
    /*
     * Testing InsertFront
     */
    //front = insertFront(front,20);
    //printLinked(front);
    /*
     * Testing insertBetween
     */
    int j = 3;
    for ( i = 0 ; i < 10 ; i++ ){
        insertSorted(front,i%j);
        printf("%d ",i%j);
        //printLinked(front);
    }
    //printLinked(front);

    return 0 ;
}