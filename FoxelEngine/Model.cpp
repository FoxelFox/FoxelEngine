#define _CRT_SECURE_NO_WARNINGS	// to disable the fscanf warnings
#include "Model.h"
#include "ShaderProgram.h"

using namespace std;
using namespace GLSL;

GLuint Model::anzIndex, Model::anzVertex;
GLVertex* Model::vertices;
GLuint Model::vao, *Model::indices, Model::vbos[2];
bool Model::loaded = false;

Model::Model(){

}

Model::~Model(){

}

/*
	========================================================
	Load the objFile into the system Memory and converting
	the Model-Data to an usable Mesh. At the end it put that
	Mesh into thy GPU-RAM
	========================================================
*/
bool Model::load(char* objFile){
	if(!loaded){
		FILE* file = fopen(objFile,"r");
		if(file == NULL){
			cout << "Can't open model file: " << objFile << endl;
			return false;
		}
		vector<Vertex> v_Vertex; vector<unsigned int> v_VertexIndices;
		vector<Normal> v_Normal; vector<unsigned int> v_NormalIndices;
		vector<Textur> v_Textur; vector<unsigned int> v_TexturIndices;

		char lineTyp[256];
		bool done = false;
		Vertex cVertex;
		Normal cNormal;
		Textur cTextur;
		while(!done){
			if((fscanf(file, "%s",lineTyp) == EOF)){
				done = true;
				break;
			}else{
				if(strcmp(lineTyp, "v") == 0){
					fscanf(file,"%f %f %f\n",&cVertex.x,&cVertex.y,&cVertex.z);
					v_Vertex.push_back(cVertex);
				}else if(strcmp(lineTyp,"vt") == 0){
					fscanf(file,"%f %f\n",&cTextur.u,&cTextur.v);
					v_Textur.push_back(cTextur);
				}else if(strcmp(lineTyp,"vn") == 0){
					fscanf(file,"%f %f %f\n",&cNormal.a,&cNormal.b,&cNormal.c);
					v_Normal.push_back(cNormal);
				}else if(strcmp(lineTyp,"f") == 0){
					string vertex1,vertex2,vertex3;
					unsigned int vertexIndex[3], texturIndex[3], normalIndex[3];
					int matches = fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n",
								  &vertexIndex[0], &texturIndex[0], &normalIndex[0],
								  &vertexIndex[1], &texturIndex[1], &normalIndex[1],
								  &vertexIndex[2], &texturIndex[2], &normalIndex[2]);
					if (matches == 9){
						v_VertexIndices.push_back(vertexIndex[0]-1);
						v_VertexIndices.push_back(vertexIndex[1]-1);
						v_VertexIndices.push_back(vertexIndex[2]-1);
						v_TexturIndices.push_back(texturIndex[0]-1);
						v_TexturIndices.push_back(texturIndex[1]-1);
						v_TexturIndices.push_back(texturIndex[2]-1);
						v_NormalIndices.push_back(normalIndex[0]-1);
						v_NormalIndices.push_back(normalIndex[1]-1);
						v_NormalIndices.push_back(normalIndex[2]-1);
					}
				}
			}
		}

		// Now sorting the data
		anzVertex = (GLuint)v_Vertex.size();
		anzIndex = (GLuint)v_VertexIndices.size();
		vertices = new GLVertex[anzVertex];
		indices = new GLuint[anzIndex];
		for(unsigned int i = 0; i < anzVertex; i++){
			vertices[i].x = v_Vertex[i].x;
			vertices[i].y = v_Vertex[i].y;
			vertices[i].z = v_Vertex[i].z;
		}
		for(unsigned int i = 0; i < anzIndex; i++){
			indices[i] = v_VertexIndices[i];

			vertices[v_VertexIndices[i]].a = v_Normal[v_NormalIndices[i]].a;
			vertices[v_VertexIndices[i]].b = v_Normal[v_NormalIndices[i]].b;
			vertices[v_VertexIndices[i]].c = v_Normal[v_NormalIndices[i]].c;

			vertices[v_VertexIndices[i]].u = v_Textur[v_TexturIndices[i]].u;
			vertices[v_VertexIndices[i]].v = v_Textur[v_TexturIndices[i]].v;
		}

		glGenVertexArrays(1,&vao);
		glBindVertexArray(vao);
		glGenBuffers(3,vbos);

		const size_t normalOffset = sizeof(vertices->x);
		const size_t vertexSize = sizeof(vertices[0]);


		// vertex data
		glBindBuffer(GL_ARRAY_BUFFER,vbos[0]);
		glBufferData(GL_ARRAY_BUFFER,anzVertex*sizeof(GLVertex),vertices,GL_STATIC_DRAW);
		glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,sizeof(GL_FLOAT)*8,0);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT)*8,BUFFER_OFFSET(normalOffset));
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(GL_FLOAT)*8,BUFFER_OFFSET(3*sizeof(GLfloat)));

		// index data
		glBindBuffer(GL_ARRAY_BUFFER,vbos[1]);
		glBufferData(GL_ARRAY_BUFFER,anzIndex*sizeof(GL_UNSIGNED_INT),indices,GL_STATIC_DRAW);

		glBindVertexArray(0);
		loaded = true;
		return true;
	}
	return false;
}

void Model::draw(){

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
	glVertexAttrib4f(1,1.0f,0.25f,0.0125f,0.5f);
	glDrawElements(GL_TRIANGLES,anzIndex,GL_UNSIGNED_INT,indices);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

}