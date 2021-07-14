# 충돌

Status: 게임

### **추가된 부분**

---

**1. Sprite 클래스**

1) Sprite 클래스 생성자 코드가 중복되어 길이가 길어져서 Sprite::Initialize(. . .)에서 처리

2) Initialize() 멤버 함수에서 텍스쳐(srv)를 가져오고(Sprites::Load()) 매개변수로 받아온

영역 정보를 D3DX11GetImageInfoFromFile() 함수를 통해서 얻어온 텍스처의 가로, 세로로

나누어 Uv 좌표(0~1)로 변환 해주고 정점을 설정하고 정점과 Uv 좌표를 매칭해준다.

다시 원래의 텍스처 사이즈로 만들기 위해 가로 세로를 다시 곱해주고 scale 값 변경

정점을 담아줄 버퍼(vertexBuffer)를 생성한다.

**2. Main.cpp**

1) Sprite 객체 생성

2) Sprite 객체 Update, Render

```cpp
//Effect.fx

/*
    보통 대부분의 전역 변수들은 하나뿐일지라도
    'cbuffer'이라고 불리는 버퍼 객체 타입에 넣게 된다.
 
    논리적으로 이 버퍼들을 조직하는 일은 셰이더의 효율적인 실행뿐만 아니라
    그래픽카드가 어떻게 이 버퍼들을 저장하는지와도 관련되기 때문에 중요하다.
*/
 
cbuffer CB_PerFrame
{
    // matrix는 float4x4 와 같다
    matrix World;
    matrix View;
    matrix Projection;
};
 
// --------------------------------------------------------
// Structure
// --------------------------------------------------------
 
struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
};
 
struct VertexOutput
{
    float4 Position : SV_POSITION0;
    float2 Uv : UV0;
};
 
// --------------------------------------------------------
// Vertex Shader
// --------------------------------------------------------
 
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);           // 물체 확대/축소, 회전, 이동
    output.Position = mul(output.Position, View);           // 물체를 뷰(카메라)공간으로 이동
    output.Position = mul(output.Position, Projection);     // 뷰공간으로 이동한 물체를 투영
    output.Uv = input.Uv;
 
    return output;
}
 
// --------------------------------------------------------
// Pixel Shader
// --------------------------------------------------------
    
// 텍스처 맵핑
Texture2D Map;
SamplerState Sampler;
float4 PS(VertexOutput input) : SV_TARGET0
{
    return Map.Sample(Sampler, input.Uv);
}
 
 
 
// --------------------------------------------------------
//     Blend State // 투명을 처리, 테두리 처리
// --------------------------------------------------------
 
BlendState AlphaBlend
{
    // 테두리 처리 : FALSE 일때
    AlphaToCoverageEnable = false;
 
    // 투명처리
    BlendEnable[0] = true;  // 블렌드 모드 사용, 8개의 이미지까지 사용 가능
 
    /*
        블렌딩 함수
        
        INV_SRC_ALPHA : 소스 텍스쳐의 알파를 역전시킨 것
        즉, 1에서 소스 텍스쳐의 알파만큼 뺀 것.
        
        ex) 만약 소스의 알파가 0.3이라면 목표의 알파는 0.7로 보고 목표 픽셀의 70%를 사용
    */
    
    DestBlend[0] = INV_SRC_ALPHA;   // 이미 그 자리에 그려져 있던 목표 픽셀의 색상
    SrcBlend[0] = SRC_ALPHA;        // 소스 텍스쳐의 색상을 계산하는데 사용, (블렌딩 함수)SRC_ALPHA : 텍스쳐가 가지고 있는 알파값 그대로 사용
    BlendOp[0] = Add;               // 연산 방법, Add : 더해서 최종 픽셀 색상 구함
 
    SrcBlendAlpha[0] = One;         // 한개 쓰겠다
    DestBlendAlpha[0] = One;        // 한개 쓰겠다
    RenderTargetWriteMask[0] = 0x0F;
};
 
 
 
// --------------------------------------------------------
// Techique Shader
// --------------------------------------------------------
 
technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
 
		// 투명 처리(텍스처 외의 뒷 배경색 제거)
        SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFF); // 0xFFFFFFFF = 0xFF 알아서 개수 맞춰넣어줌
    }
}
    〰

```