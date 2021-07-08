// Macro
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = nullptr; }} // Create 할당 삭제
#define SAFE_DELETE(p)  { if(p) {delete (p); (p) = nullptr; }} // new 할당 삭제
#define SAFE_DELETE_ARRAY(p) { if(p) {delete[] (p); (p) = nullptr; }} // 배열 삭제
