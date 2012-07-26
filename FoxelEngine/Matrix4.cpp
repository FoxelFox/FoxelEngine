#include "Matrix4.h"
#include "Convert.h"
using namespace std;


Matrix4::Matrix4(void){
	for(int n = 0; n < M_SIZE*M_SIZE; n++){
		if(n % 5 == 0) matrix[n] = 0.0f;	// identity
		else matrix[n] = 0.0f;
	}
}


Matrix4::~Matrix4(void)
{
}

Matrix4 Matrix4::Identity(){
	Matrix4 id;
	for(int i = 0; i < M_SIZE*M_SIZE; i+=5){
		id.matrix[i] = 1.0f;
	}
	return id;
}

void Matrix4::scale(float x, float y, float z){
	Matrix4 scaly = Matrix4::Identity();
	scaly.matrix[ 0] = x;
	scaly.matrix[ 5] = y;
	scaly.matrix[10] = z;
	*this = *this * scaly;
}

/*  =========================
	Transponierte Translation
	=========================
*/
void Matrix4::translate(float x,float y,float z){
	Matrix4 trans = Matrix4::Identity();
	trans.matrix[12] = x;
	trans.matrix[13] = y;
	trans.matrix[14] = z;
	*this = *this * trans;
}
/*  =========================
	Transponierte Translation
	=========================
*/
void Matrix4::translate(Vec3 vector){
	Matrix4 trans = Matrix4::Identity();
	trans.matrix[12] = vector.x;
	trans.matrix[13] = vector.y;
	trans.matrix[14] = vector.z;
	*this = *this * trans;
}
/*	======================
	Transponierte Rotation
	======================
*/
void Matrix4::rotate(float angle, float x, float y, float z){
	angle = Convert::degToRad(&angle);
	if(x > 0.001){
		Matrix4 rotX = Matrix4::Identity();
		rotX.matrix[ 5] =  cos(angle);
		rotX.matrix[ 9] = -sin(angle);
		rotX.matrix[ 6] =  sin(angle);
		rotX.matrix[10] =  cos(angle);
		*this = *this * rotX;
	}
	if(y > 0.001){
		Matrix4 rotY = Matrix4::Identity();
		rotY.matrix[ 0] =  cos(angle);
		rotY.matrix[ 8] =  sin(angle);
		rotY.matrix[ 2] = -sin(angle);
		rotY.matrix[10] =  cos(angle);
		*this = *this * rotY;
	}
	if(z > 0.001){
		Matrix4 rotZ = Matrix4::Identity();			
		rotZ.matrix[0] =  cos(angle);
		rotZ.matrix[4] = -sin(angle);
		rotZ.matrix[1] =  sin(angle);
		rotZ.matrix[5] =  cos(angle);
		*this = *this * rotZ;
	}
}

Matrix4 Matrix4::RotateX(float angle){
	Matrix4 rotX = Matrix4::Identity();
	rotX.matrix[ 5] =  cos(angle);
	rotX.matrix[ 9] = -sin(angle);
	rotX.matrix[ 6] =  sin(angle);
	rotX.matrix[10] =  cos(angle);
	return rotX;
}

Matrix4 Matrix4::RotateY(float angle){
	Matrix4 rotY = Matrix4::Identity();
	rotY.matrix[ 0] =  cos(angle);
	rotY.matrix[ 8] =  sin(angle);
	rotY.matrix[ 2] = -sin(angle);
	rotY.matrix[10] =  cos(angle);
	return rotY;
}

Matrix4 Matrix4::RotateZ(float angle){
	Matrix4 rotZ = Matrix4::Identity();			
	rotZ.matrix[0] =  cos(angle);
	rotZ.matrix[4] = -sin(angle);
	rotZ.matrix[1] =  sin(angle);
	rotZ.matrix[5] =  cos(angle);
	return rotZ;
}

Matrix4 Matrix4::CreateFromAxisAngle(Vec3 axis, float angle){
	Matrix4 mat;
	angle = Convert::degToRad(angle);
	float num = cos(-angle);
    float num2 = sin(-angle);
    float num3 = 1.0f - num;
    axis.normalize();
	mat.matrix[0]  = ((num3 * axis.x) * axis.x) + num;
	mat.matrix[1]  = ((num3 * axis.x) * axis.y) - (num2 * axis.z);
	mat.matrix[2]  = ((num3 * axis.x) * axis.z) + (num2 * axis.y);
	mat.matrix[3]  = 0.0f;
	mat.matrix[4]  = ((num3 * axis.x) * axis.y) + (num2 * axis.z);
	mat.matrix[5]  = ((num3 * axis.y) * axis.y) + num;
	mat.matrix[6]  = ((num3 * axis.y) * axis.z) - (num2 * axis.x);
	mat.matrix[7]  = 0.0f;
	mat.matrix[8]  = ((num3 * axis.x) * axis.z) - (num2 * axis.y);
	mat.matrix[9]  = ((num3 * axis.y) * axis.z) + (num2 * axis.x);
	mat.matrix[10] = ((num3 * axis.z) * axis.z) + num;
	mat.matrix[11] = 0.0f;
	mat.matrix[12] = 0.0f;
	mat.matrix[13] = 0.0f;
	mat.matrix[14] = 0.0f;
	mat.matrix[15] = 1.0f;
	return mat;
}

float* Matrix4::getMatrix(){
	return matrix;
}
/*	============================
	Transponierte Multiplikation
	============================
*/
Matrix4 Matrix4::operator*(Matrix4 B){
	Matrix4 C;
	for(int i = 0; i < M_SIZE; i++){
		for(int s = 0; s < M_SIZE; s++){
			for(int z = 0; z < M_SIZE; z++){
				C.matrix[M_SIZE*s+i] += matrix[M_SIZE*z+i] * B.matrix[M_SIZE*s+z];
			}
		}
	}
	return C;
}

void Matrix4::printMatrix(){
	cout << endl << "_________________________" << endl;
	for(int i = 0; i < M_SIZE*M_SIZE; i++){
		if(i != 0 && i % 4 == 0) cout << "\n\n\n\n\n";
		cout << matrix[i] << "\t";
	}
	cout << endl << "_________________________" << endl;
}