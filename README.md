Hello, world!!!!
arduino_study



한양대학교 3학년 2학기  

# adventur design1_ (201809~2018012)
# Due: 2018/12/14
### 2016003954 진하림----
---------------------
### microbit를 사용한 미로 찾기 로봇 코드
<!-- ### c를 사용한 랜덤 미로를 만드는 코드 -->
1. 블록코딩으로 만든 로봇 영상
2. 로봇이 바닥에 그린 그림
3. 로봇 형태


사용된 재료: 하드보드지4장, 절연테이프, microbit, line trancer senser 2개, DC 모터 2개 등..

============================
1. 모든 재료를 구입
2. 미로를 만드는 코드를 사용해서 정해진 크기의 미로를 생성
3. 생성된 미로를 보고 하드보드지 연결하고, 절연테이프로 미로의 벽을 생성을 함.
4. microbit를 사용하여 line tracer senser를 사진과 같이 조립를 함.
5. 로봇에게 정해진 규칙을 만들어서 오른벽을 계속 따라가서 출구로 나간다는 기본적인 솔루션을 가지고 코딩을 함.
    a) 1: 바닥일 경우, 0: 벽일 경우 - line tracer senser가 인식하는 digital value
    b) line senser 두개 - 오른쪽에 위치(right), 로봇의 앞부분에 위치(left)
    c) if right = 1 and left = 1 , then moters forward
    d) else if right = 1 and left = 0, then  moters turn right and forward 
    e) else if right = 0 and left = 1, then moters turn left
    f) else if right = 0 and left = 0, then moters turn right
6. 전원을 연결하고, 실행을 한다.
================================== 
