#include<stdio.h>
#include<stdlib.h>  //동적 할당 내장
#include<math.h>
#include<stddef.h>  //sizeof 연산자 내장

#define len 13  //무조건 홀수여야만 한다  4의배수 +1의 값만 가능하다

#define up maze[a-1][b]
#define down maze[a+1][b]
#define left maze[a][b-1]
#define right maze[a][b+1]
#define me maze[a][b]

#define ct_wall_len ((len-3)/2) //내부 고정벽 1열 개수
#define ct_void_len ((len-1)/2) //내부 고정공간 1열 개수

int route_sequence[1000];
int route_count=0;

typedef struct{
  int x;
  int y;
  int wall;
  int root;
  int path;
  int cline;
}block;
//adventure design용 미로그리는 차 경로 생성 함수
void trevel_route(int a,int b,block**maze,int back);
void route_numbering(int a);
void draw_route(block**maze);
int route_order(char*);
//미로 초기화 및 생성 함수
void block_build(block**);
//in the block_build
//1단계:미로 기본구조 생성
block** block_init();
void rand_wall(block**maze);
//2단계:root
void root_link(block**maze);
void root_pruning(block**maze);
int root_plus(int a,int b,block**maze);
int root_chain(int a,int b,block**maze);
//3단계:void
void void_seed(block** maze);
void void_pruning(block**maze);
int void_plus(int a,int b,block**maze);
int void_chain(int a,int b,block**maze);

//잡기능은 아니지만 미분류함수
void door_push(block**maze);//미로 출입구 문 여닫기--일부 함수작용시 에러 막기 위함
int turn(int dddd);  //미로 생성시 chain 탐색 순서 결정 함수
int connection(int a,int b, int level,int dddd,block**maze);//**chain 작용의 핵심--root와 void 에서 최중요 작용

void draw_route(block**maze){
  for(int a=2;a<len-1;a+=2){
    route_numbering(2);
    if(maze[1][a].wall==1){
      maze[1][a].root=1;
      maze[2][a].root=1;
      route_numbering(3); //down 명령
      trevel_route(2,a,maze,1); //up 회수
    }
  }
  route_numbering(2);
  for(int a=2;a<len-1;a+=2){
    route_numbering(3);
    if(maze[a][len-2].wall==1){
      maze[a][len-2].root=1;
      maze[a][len-3].root=1;
      route_numbering(4);
      trevel_route(a,len-3,maze,2);
    }
  }
  route_numbering(5);
  route_numbering(3);
  route_numbering(6);
  for(int a=len-3;a>1;a-=2){
    route_numbering(4);
    if(maze[len-2][a].wall==1){
      maze[len-2][a].root=1;
      maze[len-3][a].root=1;
      route_numbering(1);
      trevel_route(len-3,a,maze,3);
    }
  }
  route_numbering(4);
  for(int a=len-3;a>1;a-=2){
    route_numbering(1);
    if(maze[a][1].wall==1){
      maze[a][1].root=1;
      maze[a][2].root=1;
      route_numbering(2);
      trevel_route(a,2,maze,4);
    }
  }
}

void route_numbering(int a){
  route_sequence[route_count]=a;
  route_count++;
}

void trevel_route(int a,int b,block**maze,int back){
  if(up.wall==1){
    if(maze[a-2][b].root==0){
      up.root=1;
      maze[a-2][b].root=1;
      route_numbering(1); //up명령
      trevel_route(a-2,b,maze,3); //down회수
    }
  }
  if(right.wall==1){
    if(maze[a][b+2].root==0){
      right.root=1;
      maze[a][b+2].root=1;
      route_numbering(2);
      trevel_route(a,b+2,maze,4);
    }
  }
  if(down.wall==1){
    if(maze[a+2][b].root==0){
      down.root=1;
      maze[a+2][b].root=1;
      route_numbering(3);
      trevel_route(a+2,b,maze,1);
    }
  }
  if(left.wall==1){
    if(maze[a][b-2].root==0){
      left.root=1;
      maze[a][b-2].root=1;
      route_numbering(4);
      trevel_route(a,b-2,maze,2);
    }
  }
  route_numbering(back);
}

int route_order(char* direc_order){
  int a=0;
  while(route_sequence[a]){
    if(a%8==7){
      //Serial.print("\n\n");
    }
    if(route_sequence[a]>0 && route_sequence[a]<5){
      if(a==0){
        //Serial.print("go(%d)/",route_sequence[a]);
        direc_order[a]=1;
        a++;
        continue;
      }
      if(route_sequence[a-1]>0 && route_sequence[a-1]<5){
        int dif = route_sequence[a]-route_sequence[a-1];
        if(dif==0){
          //Serial.print("go(%d)/",route_sequence[a]);
          direc_order[a]=1;
          a++;
          continue;
        }
        if(dif == 2 || dif == -2){
          //Serial.print("backturn(%d)/",route_sequence[a]);
          direc_order[a]=3;
          a++;
          continue;
        }
        if(dif==1 || dif==-3){
          //Serial.print("right(%d)/",route_sequence[a]);
          direc_order[a]=2;
          a++;
          continue;
        }
        if(dif==-1 || dif==3){
        //  Serial.print("left(%d)/",route_sequence[a]);
          direc_order[a]=4;
          a++;
          continue;
        }
      }
      if(route_sequence[a-1]==5){
      //  Serial.print("go(%d)/",route_sequence[a]);
        direc_order[a]=1;
        a++;
        continue;
      }
      if(route_sequence[a-1]==6){
      //  Serial.print("right(%d)/",route_sequence[a]);
        direc_order[a]=2;
        a++;
        continue;
      }
    }
    if(route_sequence[a]==5){
  //    Serial.print("펜 떼기(%d)/",route_sequence[a]);
      direc_order[a]=5;
      a++;
      continue;
    }
    if(route_sequence[a]==6){
//      Serial.print("펜 찍기(%d)/",route_sequence[a]);
      direc_order[a]=6;
      a++;
      continue;
    }
//    Serial.print("에이 나오면 안됨 제발 이거 나오면 안됨");
  }
//  Serial.print("%d",a);
//  Serial.print("\n");
  return a;
}

void block_build(block**maze){
  rand_wall(maze);

  root_link(maze);      //외부벽으로부터 시작
  root_pruning(maze);//  wall_check(maze);
  Serial.print(" ");            //주의! 건들지 말것 이 프로그램의 영혼이 담김

  void_seed(maze);      //빈 공간의 중심에서부터 시작
  void_pruning(maze);//  wall_check(maze);
  Serial.print(" \r");          //빼면 root작업과 void 작업이 무시당한다 왜인지는 모르겠지만
      //중단:a부분에 (len-3)/2 상단:1 하단:len-2
}
//-------------------------------
block** block_init(){
  block** maze;   //**maze=변수 *maze 포인터 maze 이중포인터
  maze=(block**)calloc(len,sizeof(block));
  for(int a=0;a<len;a++){
    *(maze+a)=(block*)calloc(len,sizeof(block));
  }
  for(int a=0;a<len;a++){
    for(int b=0;b<len;b++){
      me.x=a;
      me.y=b;
    }
  }
  for(int a=0;a<len;a++){
    maze[0][a].wall=1;
    maze[a][0].wall=1;
    maze[len-1][a].wall=1;
    maze[a][len-1].wall=1;
  }
  for(int a=0;a<len;a+=2){
    for(int b=0;b<len;b+=2){
      me.wall=1;
    }
  }
  return maze;
}

void rand_wall(block**maze){  //if len=17
  
  int a,b,tap=0;
  while(1){
    a=1+random(len-2);             //a:1~15
    if(a%2){                          //a가 홀수라면
      b=2*(1+random(ct_wall_len));     //b:2,4,6...14 //총 7개
    }
    else{
      b=1+2*random(ct_void_len);          //b:1,3,5...15 //총 8개
    }
    if(me.wall==0){         //신규 설치일때
      tap++;
    }
    me.wall=1;
    if(tap>=(pow(len,2)-pow(ct_void_len,2)-pow(ct_wall_len,2))/3){
      break;
    }
  }
}

void root_link(block**maze){
  for(int a=0;a<len;a+=2){
    maze[0][a].root=1;
    maze[a][0].root=1;
    maze[len-1][a].root=1;
    maze[a][len-1].root=1;
  }
  for(int a=2;a<len-1;a+=2){
    if(maze[1][a].wall==1){
      maze[2][a].root=1;
      root_chain(2,a,maze);
    }
    if(maze[len-2][a].wall==1){
      maze[len-3][a].root=1;
      root_chain(len-3,a,maze);
    }
    if(maze[a][1].wall==1){
      maze[a][2].root=1;
      root_chain(a,2,maze);
    }
    if(maze[a][len-2].wall==1){
      maze[a][len-3].root=1;
      root_chain(a,len-3,maze);
    }
  }
}

void root_pruning(block**maze){
  int not_yet;
  int north;
  while(not_yet){
    not_yet=0;
    for(int a=2;a<len-2;a+=2){                //행, 열에 평행하게 뽑았는데, 대각선으로 검색해보도록 하자
      for(int b=2;b<len-2;b+=2){
        north = 2 + (a+b-4)%(len-3);          //len-3 =14 -- %최대=13
        if(maze[north][b].root==0){
          not_yet += root_plus(north,b,maze);
        }
      }
    }       //주석처리는 여기
  }
}

int root_plus(int a,int b,block**maze){
  
  int dddd,gogo,surround=0;
  dddd=random(4);                    //Serial.print("%d",dddd);
  for(int z=0;z<4;z++){
    gogo=connection(a,b,1,dddd,maze);
    if(gogo==-1){
      return 0;
    }
    else{
      surround+=gogo;
    }
    dddd = turn(dddd);
  }
  if(surround==0){
    switch (dddd) {
      case 0:{
        up.wall=1;
      }break;
      case 1:{
        right.wall=1;
      }break;
      case 2:{
        down.wall=1;
      }break;
      case 3:{
        left.wall=1;
      }break;
    }
  }
  return 1;
}

int root_chain(int a,int b,block**maze){
  if(up.wall==1){
    if(maze[a-2][b].root==0){
      maze[a-2][b].root=1;
      root_chain(a-2,b,maze);
    }
  }
  if(right.wall==1){
    if(maze[a][b+2].root==0){
      maze[a][b+2].root=1;
      root_chain(a,b+2,maze);
    }
  }
  if(down.wall==1){
    if(maze[a+2][b].root==0){
      maze[a+2][b].root=1;
      root_chain(a+2,b,maze);
    }
  }
  if(left.wall==1){
    if(maze[a][b-2].root==0){
      maze[a][b-2].root=1;
      root_chain(a,b-2,maze);
    }
  }
  return 0;
}

void void_seed(block** maze){
  maze[(len-3)/2][(len-3)/2].path=1;
  void_chain((len-3)/2,(len-3)/2,maze);
}

void void_pruning(block**maze){
  int not_yet;
  int north;
  while(not_yet){
    not_yet=0;
    for(int a=3;a<len+1;a+=2){                //행, 열에 평행하게 뽑았는데, 대각선으로 검색해보도록 하자
      for(int b=len-2;b>0;b-=2){
        north = 1 + (a+b-2)%(len-1);          //len-3 =14 -- %최대=13
        if(maze[north][b].path==0){
          not_yet += void_plus(north,b,maze);
        }
      }                       //이번엔 [3][3]이 지 멋대로 path값을 가짐 어떻게 처리좀
    }       //주석처리는 여기  //관계연산자 ==라고 쳐야되는데 =라고 쳐서 case=1 구멍 뚤린거 메꿈
  }  //Serial.print("끝났냐?\n");   //maze[-1] 이런거 건들여서 터지는거임 빨리 방법 생각좀 //처리해드렸습니다^^
}


int void_plus(int a,int b,block**maze){   //me.path==1, 상태한테 값주고 그놈 주변 통로 값 재조정
  
  int dddd,gogo,surround=0;
  dddd=random(4);                    //Serial.print("%d",dddd);
  for(int z=0;z<4;z++){
    dddd = turn(dddd);
    if(dddd==0 && a==1){
      surround++;
      continue;
    }
    if(dddd==1 && b==(len-2)){
      surround++;
      continue;
    }
    if(dddd==2 && a==(len-2)){
      surround++;
      continue;
    }
    if(dddd==3 && b==1){
      surround++;
      continue;
    }
    gogo=connection(a,b,0,dddd,maze);
    if(gogo==-1){
      return 0;
    }
    else{
      surround+=gogo;
    }
  }  //Serial.print("\n");
  if(surround==4){        //미로 크기가 엄청 클때는 효과를 줄 수도 있겠지만 크키 200 이내에서는 거의 쓰이지 않는 것 같다.
    int done=1;
    while(done){
      switch (dddd) {
        case 0:{
          if(a!=1){
            up.wall=0;
            done--;
          }
          else{
            dddd++;
          }
        }break;
        case 1:{
          if(b!=(len-2)){
            right.wall=0;
            done--;
          }
          else{
            dddd+=2;
          }
        }break;
        case 2:{
          if(a!=(len-2)){
            down.wall=0;
            done--;
          }
          else{
            dddd-=2;
          }
        }break;
        case 3:{
          if(b!=1){
            left.wall=0;
            done--;
          }
          else{
            dddd--;
          }
        }break;
      }
    }
  }
  return 1;
}

int void_chain(int a,int b,block**maze){
  if(up.wall==0){
    if(maze[a-2][b].path==0){
      maze[a-2][b].path=1;
      void_chain(a-2,b,maze);
    }
  }
  if(right.wall==0){
    if(maze[a][b+2].path==0){
      maze[a][b+2].path=1;
      void_chain(a,b+2,maze);
    }
  }
  if(down.wall==0){
    if(maze[a+2][b].path==0){
      maze[a+2][b].path=1;
      void_chain(a+2,b,maze);
    }
  }
  if(left.wall==0){
    if(maze[a][b-2].path==0){
      maze[a][b-2].path=1;
      void_chain(a,b-2,maze);
    }
  }
  return 0;
}

int turn(int dddd){
  switch(dddd){
    case 0:{    //up
      return dddd+1;
    }break;
    case 1:{  //right
      return dddd+2;
    }break;
    case 2:{  //down
      return dddd-2;
    }break;
    case 3:{  //left
      return dddd-1;
    }break;
  }
}

int connection(int a,int b, int level,int dddd,block**maze){
  int next[2][4];
  if(dddd==0){ //베열 음수 건들면 터짐 못건들게 if절로 막아둠
    next[0][0]=maze[a-2][b].path;
    next[1][0]=maze[a-2][b].root;
  }
  else if(dddd==1){
    next[0][1]=maze[a][b+2].path;
    next[1][1]=maze[a][b+2].root;
  }
  else if(dddd==2){
    next[0][2]=maze[a+2][b].path;
    next[1][2]=maze[a+2][b].root;
  }
  else if(dddd==3){
    next[0][3]=maze[a][b-2].path;
    next[1][3]=maze[a][b-2].root;
  }
  if(next[level][dddd]==1){
    switch (dddd) {
      case 0:{
        up.wall=level;  //동기화는 일치화가 아니다. = 붙여주고 둘이 완전히 일치하다고 생각하면 안됨
      }break;           //어디까지나 값을 주고받는 것이지 상수 너무 썼다고 변수도 상수취급하듯이 취급해버리니깐 몇시간 날려먹음
      case 1:{
        right.wall=level;
      }break;
      case 2:{
        down.wall=level;
      }break;
      case 3:{
        left.wall=level;
      }break;
    }
    if(level){
      me.root=1;
      root_chain(a,b,maze);
    }
    else{
      me.path=1;
      void_chain(a,b,maze);
    }
    return -1;
  }
  int wall_dr[4];
  wall_dr[0]=up.wall;
  wall_dr[1]=right.wall;
  wall_dr[2]=down.wall;
  wall_dr[3]=left.wall;
  int surround=0;
  if(wall_dr[dddd]==1){
    surround++;
  }
  return surround;
}

void door_push(block**maze){
  if(maze[1][0].wall){
    maze[1][0].wall=0;
    maze[len-2][len-1].wall=0;
  }
  else{
    maze[1][0].wall=1;
    maze[len-2][len-1].wall=1;
  }
}

int A_1A = 6;
int A_1B = 11;
int B_1A = 3;
int B_1B = 5;
/*
   HC-06 블루투스 모듈
   주의: 시리얼통신은 반드시 엇갈려 꽂혀야 합니다.
   HC-06 RX - D13
   HC-06 TX - D12
*/
int btRxPin = 12;
int btTxPin = 13;
int speed = 255;

  char direc_order[1000] = {0,};
  int a,t;
  
void setup() {
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);

  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  block** maze=block_init();
  block_build(maze);
  for(int a=1;a<len-1;a++){       //--루트값 초기화
    for(int b=1;b<len-1;b++){
      me.root=0;
    }
  }
  draw_route(maze);
  a = route_order(direc_order);
  t=0;
  /*
  for(t=0;t<a;t++){
    Serial.print((int)direc_order[t]);
  }
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  if(direc_order[t]){
    switch (direc_order[t]) {
      case 1:
        break;
      case 3:
        //모터A 역회전
        analogWrite(A_1A, speed);
        analogWrite(A_1B, 0);
        //모터B 역회전
        analogWrite(B_1A, 0);
        analogWrite(B_1B, speed);
        delay(1000);// 2번정도 회전을 함으로 delay계산을 해야함
        break;
      case 2:
        //모터A 정회전
        analogWrite(A_1A, 0);
        analogWrite(A_1B, speed);
        //모터B 역회전
        analogWrite(B_1A, speed);
        analogWrite(B_1B, 0);
        break;
      case 4:
        //모터A 역회전
        analogWrite(A_1A, speed);
        analogWrite(A_1B, 0);
        //모터B 정회전
        analogWrite(B_1A, 0);
        analogWrite(B_1B, speed);
        break;
      case 's':
        //모터A 정지
        analogWrite(A_1A, 0);
        analogWrite(A_1B, 0);
        //모터B 정지
        analogWrite(B_1A, 0);
        analogWrite(B_1B, 0);
        break;
    }
    delay(1000);
    //모터A 정회전
    analogWrite(A_1A, speed);
    analogWrite(A_1B, 0);
    //모터B 정회전
    analogWrite(B_1A, speed);
    analogWrite(B_1B, 0);
    t++;
  }
  delay(1000);
}
