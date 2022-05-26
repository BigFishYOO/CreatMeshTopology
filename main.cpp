

// author: Ma Liping 2021.1.1
// TianJin university

#include"header.h"
int main(int argc, char** argv)
{
	clock_t start, end;
	start = clock();
	if (mike) {
		readmesh();
	}
	else {
		readmsh();
	}
	

	initEdge();
	output_topo2();
	output_Side();
	output_Cell();
	end = clock();
	cout << (double)(end - start) / CLOCKS_PER_SEC << endl;

	return 0;
}

void readmsh() {

	int* Element_SNO, * in_or_out, * Boundary_trait, * Boundary_index;
	int Unimportant;

	Boundary_NO = 0;
	string name = "Mesh.msh";
	//	string type = ".dat";
	string filename = name; // file name including extentions	
	string line;
	ifstream FILE;
	int dum, dum1, dum2, dum3, dum4, dum5;
	n_edge = 0;
	FILE.open(filename.c_str());
	if (FILE.is_open()) {
		getline(FILE, line);
		getline(FILE, line);
		getline(FILE, line);
		getline(FILE, line);
		FILE >> n_node; getline(FILE, line);
		cout << n_node  << endl;
		for (int i = 0; i < n_node; i++)
		{
			Vertex ver;
			FILE >> dum >> ver.x >> ver.y >> ver.z; getline(FILE, line);
			vertex.push_back(ver);
		}
		getline(FILE, line); getline(FILE, line);
		FILE >> n_element; getline(FILE, line);
		Element_SNO = new int[n_element];
		in_or_out = new int[n_element];
		Boundary_trait = new int[n_element];
		Boundary_index = new int[n_element];
		cout << "n_element" << n_element << endl;
		for (int i = 0; i < n_element; i++) {
			FILE>> Element_SNO[i] >> in_or_out[i];
			if (in_or_out[i] == 1) {
				Boundary b;
				FILE >> Unimportant >> b.property >> Boundary_index[i] >> b.order[0] >> b.order[1]; getline(FILE, line);
				b.order[0] = b.order[0] - 1;
				b.order[1] = b.order[1] - 1;
			//	cout << b.property << " " << b.order[0] << " " << b.order[1] << endl;
				BoundaryEdge.push_back(b);
				Boundary_NO++;
				
			}
			else {
				Face f;
				FILE >> dum3 >> dum4 >> dum5 >> f.order[0] >> f.order[1] >> f.order[2]; getline(FILE, line);
				f.order[0] = f.order[0] - 1;
				f.order[1] = f.order[1] - 1;
				f.order[2] = f.order[2] - 1;
				face.push_back(f);
			}
			
		}

		n_face = n_element - Boundary_NO;

		//for (int i = 0; i < n_face; i++)
		//{
		//	Face f;
		//	FILE >> dum1 >> dum2 >> dum3 >> dum4 >> f.num >> f.order[0] >> f.order[1] >> f.order[2]; getline(FILE, line);
		//	f.order[0] = f.order[0] - 1;
		//	f.order[1] = f.order[1] - 1;
		//	f.order[2] = f.order[2] - 1;
		////	fgets(buffer, 1023, fp);
		////	sscanf(buffer, "%d%d%d%d", &f.num, &f.order[0], &f.order[1], &f.order[2]);
		//	face.push_back(f);
		//}
		cout << n_face << " " << n_element << " " << Boundary_NO << endl;
		cout << "msh�ļ���ȡ����" << endl;
	}
	FILE.close();
	//for(int i=0;i<n_node;i++)
	//{
	//	cout<<vertex[i].x<<" "<<vertex[i].y<<" "<<vertex[i].z<<endl;
	//}
	//for (int i = 0; i < n_face; i++)
	//{
	//	cout << face[i].order[0] << " " << face[i].order[1] << " " << face[i].order[2] << endl;
	//}

	
}

void readmesh() {


	Boundary_NO = 0;
	string name = "MeshTwo.mesh";
	//	string type = ".dat";
	string filename = name; // file name including extentions	
	string line;
	ifstream FILE;
	int dum, dum1, dum2, dum3, dum4, dum5;
	n_edge = 0;
	FILE.open(filename.c_str());
	if (FILE.is_open()) {
		FILE >> dum >> dum1>> n_node; getline(FILE, line);
		cout << n_node << endl;
		for (int i = 0; i < n_node; i++)
		{
			Vertex ver;
			FILE >> dum2 >> ver.x >> ver.y >> ver.z >> ver.p; getline(FILE, line);
			vertex.push_back(ver);
		}

		FILE >> n_element; getline(FILE, line);
		cout << "n_element" << n_element << endl;

		for (int i = 0; i < n_element; i++) {
			Face f;
			FILE >> dum3 >> f.order[0] >> f.order[1] >> f.order[2]; getline(FILE, line);
			f.order[0] = f.order[0] - 1;
			f.order[1] = f.order[1] - 1;
			f.order[2] = f.order[2] - 1;
			face.push_back(f);
		}
		n_face = n_element - Boundary_NO;

	}
	FILE.close();
	cout << "Mike mesh�ļ���ȡ����" << endl;
}

void initEdge()//���ɰ�ߴ���vector
{
	
	for (int i = 1; i < n_face+1; i++)  //֮���Զ����1��ʼ��ţ�����Ϊ�߽�ߵĶ�����Ϊ0�������0��ţ��׻���
	{


		HalfEdge* edges[3];
		for (int j = 0; j < 3; j++)
		{
			if (mike) {
				edges[j] = create_edge(face[i - 1].order[j % 3], face[i - 1].order[(j + 1) % 3], vertex[face[i - 1].order[j % 3]].p, vertex[face[i - 1].order[(j + 1) % 3]].p, sideNo); //create_edge���ص�ǰ���
			}
			else {
				edges[j] = create_edge(face[i - 1].order[j % 3], face[i - 1].order[(j + 1) % 3], 0.0f, 0.0f, sideNo); //create_edge���ص�ǰ���
			}
	
			if (edges[j] == NULL)
			{
				cout << "creat edge error" << endl;
			
			}
		}
	//	cout << i << endl;
		for (int j = 0; j < 3; j++)
		{
			edges[j]->IncEdge = j;
			edges[j]->next = edges[(j + 1) % 3];
			edges[j]->IncFace = i;
			edge.push_back(edges[j]); //m_edges �洢���еİ��

		}


		n_edge = edge.size();
	}

	cout<<n_edge<<endl;

	cout << "���˴������" << endl;

	create_boundary();

	//for (int i = 0; i < n_edge; i++) {
	//	cout <<i<<" "<< edge[i]->IncFace << " ";
	//		if (edge[i]->opposite == NULL) {
	//			cout << "�߽�ߣ�-37";
	//		}
	//		else {
	//			cout << edge[i]->opposite->IncFace << " "<< edge[i]->IncEdge<<" ";
	//		}
	//		cout << edge[i]->property << " " <<  endl;   //���ڱ߽�ߣ�����Ŀǰ�����
	//}

	cout<< "�߽紴�����" << endl;

		
}

HalfEdge* create_edge(int v1, int v2, float p1, float p2, int &sideNo)
{
	//input: ÿ�����id��x,y,z��������vertex

	//if (v1 == NULL || v2 == NULL)
	//{
	//	
	//	return NULL;
	//}
	HalfEdge* he = new HalfEdge();
	HalfEdge* he_op = new HalfEdge();
	//���Ȳ�ѯ�Ƿ��������v1 v2�����İ��
	EdgeKey key(v1, v2);   //idΪ�õ�ĵ�ţ���ʱ�룬v1Ϊ��㣬v2Ϊ�յ�
	if (m_hashmap_edge.find(key) != m_hashmap_edge.end()) //�������˵����֮ǰ�������˵ĶԱ�
	{
		return m_hashmap_edge[key];
	}
	//������ �򴴽�v1->v2�İ���Լ���Ա�( v2->v1�İ��),�Ա߱����ڹ�ϣ�����Ա���֮���������
	//����ʱ�Աߵ����ӹ�ϵ

	he->FirstPoint.id = v1;
	he->FirstPoint.p = p1;
	he->SecondPoint.id = v2;
	he->SecondPoint.p = p2;
	he->opposite = he_op;
	he->property = -10;
	he->IncCacu = 0;
	he->Side = sideNo;  //20210628 ����ƽ ����������������
//	v1->halfEdge = he;

	he_op->FirstPoint.id = v2;
	he_op->FirstPoint.p = p2;
	he_op->SecondPoint.id = v1;
	he_op->SecondPoint.p = p1;
	he_op->opposite = he;
	he_op->property = -10;
	he_op->IncCacu = 1;
	he_op->Side = sideNo;  //20210628 ����ƽ ����������������

	sideNo++;   
	/*   if(v2->halfEdge)
	   v2->halfEdge = he_op;*/
	   //�����ϣ��
	m_hashmap_edge[EdgeKey(v1, v2)] = he;
	m_hashmap_edge[EdgeKey(v2, v1)] = he_op;

	return he;
}

void create_boundary() {


	int Boundary = 0;
	for (int i = 0; i < n_edge; i++) {

		if (edge[i]->opposite->IncFace == 0) {
			edge[i]->property = 37;
			edge[i]->opposite->IncEdge = 3;
			if (mike) {
				for (int j = 2; j < 200; j++) {    //�߽�������ע��˴�������
					if (edge[i]->FirstPoint.p == j && edge[i]->SecondPoint.p == j) {
						edge[i]->property = j-1; //����mike�ı߽����Դ�2��ʼ���ʴ˴���2��ʼ�ж�
						Boundary++;
					}
				}			
			}
			else {
				
				for (int j = 0; j < Boundary_NO; j++) {
					//�˴�ע��߽�ߵ���ת�����Ƿ����ڲ�����һ�£������if����ȥ
					if (edge[i]->FirstPoint.id == BoundaryEdge[j].order[1] && edge[i]->SecondPoint.id == BoundaryEdge[j].order[0]) {
					//	cout << "����˲�" << endl;
						edge[i]->property = BoundaryEdge[j].property;
						Boundary++;
					}
				}
			}
		

		}
	}

	cout << "����" << Boundary << "���߽�" << endl;
}

void output_topo2() {

	string path = "Output";
	string name = path + "/Topo";
	string type = ".dat";
	string filename = name + type;
	ofstream outfile(filename.c_str());
	int a = 6;
	outfile.precision(6);

	for (int i = 0; i < n_edge; i++) {
		if (i%3==0&&i!=0) {
			outfile << endl;
		}
		outfile << edge[i]->IncFace-1 << " ";
	
		outfile << edge[i]->opposite->IncFace-1 << " " ;
		
		outfile << a << " " << edge[i]->property <<" ";

		if (edge[i]->opposite->IncEdge == 3) {
			outfile << "-1" << " ";
		}
		else {
			int b = edge[i]->opposite->IncEdge;
			outfile << b << " ";
		}

		
		outfile << edge[i]->IncCacu << " ";


	/*	if (edge[i]->opposite->IncEdge == 3) {
			cout << "�Ա�Ϊ3" << endl;
		}*/
	//	outfile << Edge_NL[i * 3] << " " << Edge_NR[i * 3] << " " << Edge_index[i * 3] << " " << Edge_P[i * 3] << " ";
	//	outfile << Edge_NL[i * 3 + 1] << " " << Edge_NR[i * 3 + 1] << " " << Edge_index[i * 3 + 1] << " " << Edge_P[i * 3 + 1] << " ";
	//	outfile << Edge_NL[i * 3 + 2] << " " << Edge_NR[i * 3 + 2] << " " << Edge_index[i * 3 + 2] << " " << Edge_P[i * 3 + 2] << endl;


		//	outfile << Edge_NL[i * 3] << " " << Edge_NL[i * 3 + 1] << " " << Edge_NL[i * 3 + 2] << " ";     //�ߵ����������
		//	outfile << Edge_NR[i * 3] << " " << Edge_NR[i * 3 + 1] << " " << Edge_NR[i * 3 + 2] << " ";     //�ߵ��ұ�������
		//	outfile << Edge_index[i * 3] << " " << Edge_index[i * 3 + 1] << " " << Edge_index[i * 3 + 2] << " ";    //��ǰ�ߵ�����ֵ
		//	outfile << Edge_P[i * 3] << " " << Edge_P[i * 3 + 1] << " " << Edge_P[i * 3 + 2] << endl;               //��ǰ�ߵ�����ֵ
	}

	outfile.close();
}

//20210628 ����ƽ ����������������
void output_Side() {
	string path = "Output";
	string name = path + "/Side";
	string type = ".dat";
	string filename = name + type;
	ofstream outfile(filename.c_str());
	int a = 6;
	outfile.precision(6);
	int EdgeSingle = 0;
	outfile << sideNo << endl;
	for (int i = 0; i < n_edge; i++) {
	
		if (edge[i]->IncCacu == 0) {
			
			double Length=pow((pow((vertex[edge[i]->FirstPoint.id].x - vertex[edge[i]->SecondPoint.id].x), 2) + pow((vertex[edge[i]->FirstPoint.id].y - vertex[edge[i]->SecondPoint.id].y), 2)), 0.5);
			

			outfile << edge[i]->Side << " ";
			outfile << edge[i]->IncFace - 1 << " ";
			outfile << edge[i]->opposite->IncFace - 1 << " ";
			outfile << edge[i]->IncEdge << " ";
			outfile << Length << " ";
			outfile << edge[i]->property << endl;
			
		}
	}

	cout << "����" << sideNo << "����" << endl;
	outfile.close();
}

void output_Cell() {
	string path = "Output";
	string name = path + "/Cell";
	string type = ".dat";
	string filename = name + type;
	ofstream outfile(filename.c_str());
	int a = 6;
	outfile.precision(6);
	int CellNO = 0;
	for (int i = 0; i < n_edge; i++) {
		if (i % 3 == 0 && i != 0) {
			outfile << endl;
		}

		if (i % 3 == 0) {
			outfile << CellNO << " ";
			CellNO++;
		}
	
		outfile << edge[i]->Side <<" ";
	
	}
	cout << "����" << CellNO << "����Ԫ" << endl;
	outfile.close();
}

