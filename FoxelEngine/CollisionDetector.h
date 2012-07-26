#pragma once
#include "Vec3.h"
// Copy Paste :D________________________________________________________________________________
bool inline GetIntersection( float fDst1, float fDst2, Vec3 P1, Vec3 P2, Vec3 &Hit) {
	if ( (fDst1 * fDst2) >= 0.0f) return false;
	if ( fDst1 == fDst2) return false; 
	Hit = P1 + (P2-P1) * ( -fDst1/(fDst2-fDst1) );
	return true;
}

int inline InBox( Vec3 Hit, Vec3 B1, Vec3 B2, const int Axis) {
	if ( Axis==1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y) return true;
	if ( Axis==2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x) return true;
	if ( Axis==3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y) return true;
	return false;
}



class CollisionDetector
{
public:

	/**
	 * returns true if line (L1, L2) intersects with the box (B1, B2)
	 * returns intersection point in Hit
	 */
	static bool LineBox(Vec3 B1, Vec3 B2, Vec3 L1, Vec3 L2, Vec3 &Hit);
};

