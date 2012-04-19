#include "Matrix4.h"
#include "Convert.h"
using namespace std;


Matrix4::Matrix4(void){
	for(int n = 0; n < M_SIZE; n++){
		for(int m = 0; m < M_SIZE; m++){
			matrix[M_SIZE*n+m] = 0.0f;
		}
	}
}

Matrix4::Matrix4(float* mat){
	for(int i = 0; i < 16; i++){
		matrix[i] = mat[i];
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