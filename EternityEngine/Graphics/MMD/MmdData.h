#pragma once

#include "../../Includer.h"

namespace Eternity
{
	namespace Graphics
	{
		struct MMDVertex
		{
			Vector3 position;
			Vector3 normal;
			Vector4 color;
			Vector2 texture;
		};

		struct PmdHeader
		{
			char magic[3];
			float version;
			char modelName[20];
			char comment[256];
		};

		struct PmdVertex
		{
			float position[3];
			float normal[3];
			float uv[2];
			WORD boneNum[2];
			BYTE boneWeight;
			BYTE edgeFlag;
		};

		struct PmdMaterial
		{
			float diffuse[3];
			float alpha;
			float power;
			float specular[3];
			float ambient[3];
			BYTE toonIndex;
			BYTE edgeFlag;
			DWORD faceVertexCount;
			string textureFileName;
		};

		struct PmdBone
		{
			char boneName[20];
			WORD parentBoneIndex;
			WORD tailPosBoneIndex;
			BYTE boneType;
			WORD ikParentBoneIndex;
			float boneHeadPosition[3];
		};

		struct PmdIk
		{
			WORD boneIndex;
			WORD targetBoneIndex;
			BYTE chainCount;
			WORD recursiveCount;
			float controlWeight;
		};

		struct PmdBoneEx
		{
			int id;
			string name;
			BYTE type;
			PmdBoneEx* parent;
			PmdBoneEx* firstChild;
			PmdBoneEx* sibling;
			Matrix initMatrixBoneLocal;
			Matrix initMatrixModelLocal;
			Matrix boneMatrixBoneLocal;
			Matrix boneMatrixModelLocal;
			Matrix offsetMatrixModelLocal;
			PmdBoneEx()
				: type(), id(), parent(), firstChild(), sibling(),
				initMatrixBoneLocal(Matrix::Identity),
				initMatrixModelLocal(Matrix::Identity),
				boneMatrixBoneLocal(Matrix::Identity),
				boneMatrixModelLocal(Matrix::Identity),
				offsetMatrixModelLocal(Matrix::Identity) {};

			// モデルローカル座標系でのボーン行列を取得
			Matrix GetModelLocalBoneMatrix()
			{
				if (parent) return boneMatrixBoneLocal * parent->GetModelLocalBoneMatrix();
				else return boneMatrixBoneLocal;
			}

			// モデルローカル座標系でのボーン位置を取得
			Vector3 GetModelLocalPosition()
			{
				Vector3 result(0.0f);
				result = XMVector3TransformCoord(result, GetModelLocalBoneMatrix());
				return result;
			}
		};

		struct VmdHeader
		{
			char header[30];
			char modelName[20];
		};

		struct VmdMotion
		{
			char boneName[15];
			DWORD frameNo;
			float location[3]; //Vector
			float rotation[4]; //Quaternion
			BYTE interpolation[64]; //[4][4][4] | 補完
		};

		struct VmdSkin
		{
			char skinName[15];
			DWORD flameNo;
			float weight;
		};

		struct VmdCamera
		{
			DWORD flameNo;
			float length;
			float location[3];
			float rotation[3];
			BYTE interpolation;
			DWORD viewingAngle;
			BYTE perspective;
		};

		struct VmdLight
		{
			DWORD flameNo;
			float rgb[3];
			float location[3];
		};

		struct VmdSelfShadow
		{
			DWORD flameNo;
			BYTE mode;
			float distance;
		};
	}
}