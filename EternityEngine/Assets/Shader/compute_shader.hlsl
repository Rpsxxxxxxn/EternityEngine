// 計算シェーダ
struct BufferType
{
	int testInteger;
	float testFloat;
};

StructuredBuffer<BufferType> BufferIn : register(t0);
RWStructuredBuffer<BufferType> BufferOut : register(u0);

[numthreads(1, 1, 1)]
void main()
{

}