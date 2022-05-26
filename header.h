//2021.1.1
//Copy right: Ma Liping TianJin University
//E-mail: LipingMa1206@outlook.com 


#pragma once

#include <iostream>
#include <stdio.h>  
#include <stdlib.h>
#include <math.h> 
#include <assert.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "header.h"
#include <unordered_map>
using namespace std;

#define PI 3.1415926536

typedef struct Vertex
{
	double x, y, z, p; //p for mike mesh
}Vertex;

typedef struct Face
{
	int num;
	int order[3];
}Face;

typedef struct Boundary
{
	int property;
	int order[2];
}Boundary;

typedef struct PointP
{
	int id;
	int p; //p for mike mesh
}PointP;

typedef struct HalfEdge//半边结构
{
	PointP FirstPoint;
	PointP SecondPoint;
	struct HalfEdge* next;
	struct HalfEdge* opposite;
	int IncFace;
	int property;
	int IncEdge;
	int IncCacu;
	int Side;
//	HalfEdge() :origin(NULL), next(NULL), IncFace(NULL), property(NULL), IncEdge(NULL) {}
}HalfEdge;

typedef struct Map
{
	int vs, ve, e;

}Map;


struct EdgeKey {
	int v1, v2;
	EdgeKey(int vd1 = -1, int vd2 = -1) :v1(vd1), v2(vd2) {}

	bool operator==(const EdgeKey& key) const { return v1 == key.v1 && v2 == key.v2; }

};

struct EdgeKeyHashFuc
{
	std::size_t operator()(const EdgeKey& key) const
	{
		return std::hash<int>()(key.v1) + std::hash<int>()(key.v2);
	}
};

std::unordered_map<EdgeKey, HalfEdge*, EdgeKeyHashFuc> m_hashmap_edge;
HalfEdge* create_edge(int v1, int v2, float p1, float p2, int& sideNo);
vector<Vertex> vertex;
vector<Face> face;
vector<HalfEdge*> edge;
vector<Boundary> BoundaryEdge;

//不用hash表来实现查找 2021/10/21
struct EdgeKRY {
	int v1, v2;
	EdgeKRY(int vd1 = -1, int vd2 = -1) :v1(vd1), v2(vd2) {}

};
vector<EdgeKRY> KEY;

//


//-------------------

int n_face, n_edge;
int n_node;
int n_element;
int Boundary_NO;
int sideNo = 0;   //边的个数
//mike file
bool mike = true;

void readmsh();
void readmesh();   
void initEdge();
HalfEdge* create_edge();
void create_boundary();
void output_topo2();
void output_Side();
void output_Cell();