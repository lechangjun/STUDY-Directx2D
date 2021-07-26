# Sprite -> Clip class add 
# clip 클래스 만들고 사용하기

* clip 클래스 task
1) sprite 이용하여 클립 클래스 생성
2) Frame 구조체 : sprite 와 time 저장
3) clip::addFrame(...) : vector에 Frame 구조체 저장
4) Update() : 경과시간을 받아와 sprite를 띄워준 시간과 비교하여 다음 sprite를 띄워줄지 결정,clip sprite의 position, scale, rotation, update 갱신


* Main.cpp

1) clip 객체 생성
    
        //  clip = new Clip(PlayMode::Loop);
2) clip 객체에 sprite 등록, 값 설정, 재생

        // clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 2, 32, 40), 0.3f);
        // clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 2, 64, 40), 0.3f);
        // clip->AddFrame(new Sprite(spriteFile, shaderFile, 64, 2, 92, 40), 0.3f);
        // clip->Position(200, 200);
        // clip->Scale(2.5f, 2.5f);
        // clip->Play();

 3) clip 객체 Update, Render 해주기

## clip 애니메이션 개념 설명 
<img width="482" alt="스크린샷 2021-07-26 오후 6 51 04" src="https://user-images.githubusercontent.com/68671394/126969964-29ab68ff-990b-416f-a761-a8da2d6f42fa.png">


현재 상황 -> 오류 발견 바닥이 사라짐

<img width="1440" alt="스크린샷 2021-07-26 오후 6 24 50" src="https://user-images.githubusercontent.com/68671394/126967885-b480cf8b-4c6d-44f3-a3d8-0f3340e5f958.png">
