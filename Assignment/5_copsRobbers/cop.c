#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PI 3.14159265358979323846

struct robbers{
  /*
   * info[0]: initx
   * info[1]: inity
   * info[2]: speed
   * info[3]: direcition
   */
  int x , y , spd , dir ;
  struct robbers * next ;
  int num ;
};

struct robbers * init(int posx,int posy,int speed, int dir,int num);
float getNewPos(float initPos,int xOrY, float velocity,float time, float direction);
struct robbers * readIn(int numLines);
struct robbers * insertBack(struct robbers * root,struct robbers * toInsert);
float getMinTime(float cop[], float r0[]);
void print(struct robbers * rob);
int main(){
  int copSpeed;
  int numRobbers = 0 ;
  scanf("%d %d",&numRobbers,&copSpeed);
  struct robbers * rob = readIn(numRobbers);
  print(rob);
}

void print(struct robbers * rob){
  if (rob == NULL ) return ;
  else{
    printf("%d %d %d %d\n",rob->x,rob->y,rob->spd,rob->dir);
    print(rob->next);
  }
}
float getMinTime(float cop[], float r0[]){
  float minTime = 0.0 ;

  float rx = 30 ;
  float ry = 30 ;
  float distChase = 1;
  while ( cop[2]*minTime < distChase){
    minTime+=0.0000001 ;
    distChase = pow((pow((getNewPos(r0[0],0,r0[2],minTime,r0[3])-cop[0]),2)+pow((getNewPos(r0[1],1,r0[2],minTime,r0[3])-cop[1]),2)),0.5);
  }
  while ( cop[2]*minTime > distChase){
    minTime-=0.0000001 ;
    distChase = pow((pow((getNewPos(r0[0],0,r0[2],minTime,r0[3])-cop[0]),2)+pow((getNewPos(r0[1],1,r0[2],minTime,r0[3])-cop[1]),2)),0.5);
  }
  return minTime ;
}
float getNewPos(float initPos,int xOrY, float velocity,float time, float direction){
  float rtn[2] ;
  if ( xOrY == 0 )
    return initPos+velocity*time*cos((direction*2*PI)/360);
  else {
    return initPos+velocity*time*sin((direction*2*PI)/360);
  }
}
struct robbers * init(int posx,int posy,int speed, int dir,int num){
  struct robbers * rob = (struct robbers *)malloc(sizeof(struct robbers));
  rob->next = NULL ;
  rob->x=posx;
  rob->y=posy;
  rob->spd=speed;
  rob->dir=dir;
  rob->num = num ;
  return rob;
}

struct robbers * readIn(int numLines){
  int info[4] ;
  int i = 0 ;
  struct robbers * rob;
  int num = 0 ;

  int x, y , spd, dir;
  for ( i = 0 ; i < numLines ; i++ ){
    scanf("%d %d %d %d",&x,&y,&spd,&dir);
    rob = insertBack(rob,init(x,y,spd,dir,i));
  }
  return rob ;
}
struct robbers * insertBack(struct robbers * root,struct robbers * toInsert){
  if ( root == NULL ){
    return toInsert ;
  }
  else{
    root->next = insertBack(root->next,toInsert);
    return root ;
  }
}
