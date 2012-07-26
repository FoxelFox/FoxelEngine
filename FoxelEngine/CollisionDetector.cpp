#include "CollisionDetector.h"

bool CollisionDetector::LineBox(Vec3 B1, Vec3 B2, Vec3 L1, Vec3 L2, Vec3 &Hit){
	if (L2.x < B1.x && L1.x < B1.x){ return false;}
	if (L2.x > B2.x && L1.x > B2.x){ return false;}
	if (L2.y < B1.y && L1.y < B1.y){ return false;}
	if (L2.y > B2.y && L1.y > B2.y){ return false;}
	if (L2.z < B1.z && L1.z < B1.z){ return false;}
	if (L2.z > B2.z && L1.z > B2.z){ return false;}

	if (L1.x > B1.x && L1.x < B2.x 
	&&	L1.y > B1.y && L1.y < B2.y 
	&&	L1.z > B1.z && L1.z < B2.z){
		Hit = L1; 
		return true;
	}

	if ( (GetIntersection( L1.x-B1.x, L2.x-B1.x, L1, L2, Hit) && InBox( Hit, B1, B2, 1 ))
		|| (GetIntersection( L1.y-B1.y, L2.y-B1.y, L1, L2, Hit) && InBox( Hit, B1, B2, 2 )) 
		|| (GetIntersection( L1.z-B1.z, L2.z-B1.z, L1, L2, Hit) && InBox( Hit, B1, B2, 3 )) 
		|| (GetIntersection( L1.x-B2.x, L2.x-B2.x, L1, L2, Hit) && InBox( Hit, B1, B2, 1 )) 
		|| (GetIntersection( L1.y-B2.y, L2.y-B2.y, L1, L2, Hit) && InBox( Hit, B1, B2, 2 )) 
		|| (GetIntersection( L1.z-B2.z, L2.z-B2.z, L1, L2, Hit) && InBox( Hit, B1, B2, 3 ))){
		return true;
	}else{
		return false;
	}
}