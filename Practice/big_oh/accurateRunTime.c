#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
- [x] @mentions, #refs, [links](), **formatting**, and <del>tags</del> supported
- [x] list syntax required (any unordered or ordered list supported)
- [x] this is a complete item
- [ ] this is an incomplete item
 */
int main(){
    int userIn ;
    printf("Enter a value: ");
    scanf("%d",&userIn);

    int i,j ;
    float start = clock();
    int sum = 0 ;

    for ( i = 0 ; i < userIn ; i++){

        for ( j = 0 ; j < i ; j++ ){
            sum++ ;
        }
    }
    float end = clock();
    printf("Run-Time: %f\n",(end-start)/CLOCKS_PER_SEC);
    return 0 ;
}
