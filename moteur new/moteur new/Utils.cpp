#include "Utils.h"

//Utils::DebugLogMessage((vertToDisplay == nullptr) ? "true" : "false");


void Utils::DebugLogMessage(const char* message)
{
    std::string txt = message;
    txt += "\n";
    OutputDebugStringA(txt.c_str());
}

void Utils::DebugLogMessage(std::string* message)
{
    *message += "\n";
    OutputDebugStringA(message->c_str());
}

void Utils::DebugLogMessage(int* message)
{
    char msgd[10];
    sprintf_s(msgd, "%d\n", *message);
    OutputDebugStringA(msgd);
}

void Utils::DebugLogMessage(int message)
{
    char msgd[10];
    sprintf_s(msgd, "%d\n", message);
    OutputDebugStringA(msgd);
}


float Utils::DegToRad(float Angle)  { return Angle * DEGTORAD; }
float Utils::RadToDeg(float Rad)    { return Rad * RADTODEG; }

D3DXVECTOR3* Utils::clamp(D3DXVECTOR3* vect, float max)
{
    vect->x = (vect->x > max) ? max : vect->x;
    vect->y = (vect->y > max) ? max : vect->y;
    vect->z = (vect->z > max) ? max : vect->z;
    return vect;
}

float Utils::distance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
    D3DXVECTOR3 distVec = pos1 - pos2;
    return D3DXVec3Length(&distVec);



}

float Utils::raycast(D3DXVECTOR3* pPoint, D3DXVECTOR3* pDir, triangle* pTri, D3DXVECTOR3* pIntersect, D3DXVECTOR3* pBary, FLOAT* pT, bool isPlane)
{
	assert(pPoint && pDir && pTri);

	D3DXVECTOR3 ab = pTri->B - pTri->A;
	D3DXVECTOR3 ac = pTri->C - pTri->A;
	//D3DXVECTOR3 qp = *pPoint - *pDir;
	D3DXVECTOR3 qp = -*pDir;
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &ab, &ac);
	FLOAT d = D3DXVec3Dot(&qp, &n);
	if (d <= 0.0f)
		return false;

	D3DXVECTOR3 ap = *pPoint - pTri->A;
	FLOAT t = D3DXVec3Dot(&ap, &n);
	if (t < 0.0f)
		return false;

	D3DXVECTOR3 e;
	D3DXVec3Cross(&e, &qp, &ap);
	FLOAT v = D3DXVec3Dot(&ac, &e);
	if (isPlane == false && (v<0.0f || v>d))
		return false;
	FLOAT w = -D3DXVec3Dot(&ab, &e);
	if (isPlane == false && (w<0.0f || v + w>d))
		return false;

	if (pIntersect == NULL && pBary == NULL && pT == NULL)
		return true;

	FLOAT ood = 1.0f / d;
	t *= ood;
	v *= ood;
	w *= ood;
	if (pIntersect)
	{
		*pIntersect = pTri->A * (1.0f - v - w);
		*pIntersect += pTri->B * v;
		*pIntersect += pTri->C * w;
	}
	if (pBary)
	{
		pBary->x = 1.0f - v - w;
		pBary->y = v;
		pBary->z = w;
	}
	if (pT)
		*pT = t;
	return true;
}

triangle* Utils::offsetTirangle(triangle tri, D3DXVECTOR3 offset)
{
	tri.A + offset;
	tri.B + offset;
	tri.C + offset;
	return &tri;
}

D3DXVECTOR3* Utils::triangleNormal(triangle* T)
{
	D3DXVECTOR3 u = T->B - T->A;
	D3DXVECTOR3 v = T->C - T->A;

	D3DXVECTOR3 N;	//TODO fix address return
	N.x = u.y * v.z - u.z * v.y;
	N.y = u.z * v.x - u.x * v.z;
	N.z = u.x * v.y - u.y * v.x;
	return &N;

}

