#ifndef OJ_POLY_H
#define OJ_POLY_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm>

using namespace std;

//����ʽÿһ��
struct polyNode {
	double coef;    //ϵ��
	int exp;        //����
	polyNode *next; //��һ���ڵ�
};

//��������ʽ
class Poly {
	private:
		polyNode *head;
		polyNode *tail;
	public:
		Poly() {};              //���캯�� ����
		Poly(string);           //���캯�� ����

		~Poly() {               //�������� �ͷ�
			polyNode *s = head, *r;
			while (s && s != nullptr) {
				r = s;
				s = s->next;
				delete r;
				r = nullptr;
			}
		}

		void create(string);

		void clear();       //����

		void print();       //��ʾ
		void sort();        //����
		void add(Poly &);   //��
		void operator+=(Poly &poly) {
			add(poly);
		}

		void sub(Poly &);   //��
		void operator-=(Poly &poly) {
			sub(poly);
		}
};

void Poly::clear() {
	this->sort();   //��������
	//��һ���ļ���
	auto index = head;
	while (index->next && index->next != nullptr) {
		if (index->exp == index->next->exp) {
			index->coef += index->next->coef;
			polyNode *tmp = index->next;
			index->next = tmp->next;
			delete tmp;
			tmp = nullptr;
		} else {
			index = index->next;
		}
	}
	//���������0��
	index = head;
	polyNode *p = nullptr;
	while (index && index != nullptr) {
		if (fabs(index->coef) <= 1e-7) {
			if (index == head) {
				head = index->next;
				delete index;
				index = head;
			} else {
				p->next = index->next;
				delete index;
				index = p->next;
			}
		} else {
			if (p == nullptr) {
				p = head;
			} else {
				p = index;
				index = index->next;
			}
		}
	}
}//Poly::clear()

void Poly::sub(Poly &poly) {
	auto p = poly.head;
	while (p && p != nullptr) {
		p->coef = -p->coef;
		p = p->next;
	}
	this->add(poly);
}//Poly::sub(Poly &poly)

void Poly::add(Poly &poly) {
	poly.sort();
	this->sort();

	polyNode *thisIndex = this->head, *thisLastIndex = nullptr, *polyIndex = poly.head;

	while (thisIndex && polyIndex && thisIndex != nullptr && polyIndex != nullptr) {
		//�������
		if (thisIndex->exp == polyIndex->exp) {
			thisIndex->coef += polyIndex->coef;
			polyNode *tmp = polyIndex;
			thisLastIndex = thisIndex;
			thisIndex = thisIndex->next;
			polyIndex = polyIndex->next;
			delete tmp;
			tmp = nullptr;
		} else if (thisIndex->exp < polyIndex->exp) {
			polyNode *tmp = polyIndex;
			polyIndex = polyIndex->next;
			if (thisLastIndex == nullptr) {
				head = tmp;
			} else {
				thisLastIndex->next = tmp;
			}
			thisLastIndex = tmp;
			tmp->next = thisIndex;
		} else {
			if (thisIndex->next == nullptr) {
				thisIndex->next = polyIndex;
				break;
			} else {
				thisLastIndex = thisIndex;
				thisIndex = thisIndex->next;
			}
		}
	}
	poly.head = nullptr;
}//Poly::add(Poly &poly)

void Poly::sort() {     //����
	polyNode *maxx, *max_last, *tmp, *index = head, *index_last = nullptr;
	//ѡ������
	while (index && index != nullptr) {
		maxx = index;
		tmp = index;
		while (tmp->next && tmp->next != nullptr) {
			if (maxx->exp < tmp->next->exp) {
				max_last = tmp;
				maxx = tmp->next;
			}
			tmp = tmp->next;
		}
		if (maxx == index) {
		} else if (index_last == nullptr) {
			max_last->next = maxx->next;
			maxx->next = head;
			head = maxx;
		} else {
			max_last->next = maxx->next;
			maxx->next = index_last->next;
			index_last->next = maxx;
		}
		index_last = maxx;
		index = maxx->next;
	}

}   // Poly::sort()

void Poly::print() {
	polyNode *s = head;
	while (s != nullptr) {
		s != head && s->coef > 0 && cout << "+";
		if(s->exp==1){
			cout << s->coef << "x";
		}else if(s->exp==0){
			cout << s->coef;
		}else{
			cout << s->coef << "x^" << s->exp;	
		}
		s = s->next;
	}
}//Poly::print()

Poly::Poly(string str) {
	this->create(str);
}//Poly(string str)

void Poly::create(string str) {
	//ȥ�����пո��"^"
	if (!str.empty()) {
		int index = 0;
		while ((index = str.find(' ', index)) != string::npos) {
			str.erase(index, 1);
		}
		index = 0;
		while ((index = str.find('^', index)) != string::npos) {
			str.erase(index, 1);
		}
	} else {
		return;
	}
	//��x��X��ת����x
	transform(str.begin(), str.end(), str.begin(), ::tolower);

	//�õ�ÿһ�� ����2x3  -6x9
	vector<string> vec_str;
	{
		vec_str.clear();
		//�õ�ÿһ��+�ָ�
		vector<string> vec_tmp;
		{
			vec_tmp.clear();
			istringstream iss(str);
			string temp;
			while (getline(iss, temp, '+')) {
				vec_tmp.push_back(temp);
			}
		}
		//�õ�ÿһ��-�ָ�
		{
			for (auto str_tmp : vec_tmp) {
				if (str_tmp.find('-') == string::npos) {
					vec_str.push_back(str_tmp);
					continue;
				}
				istringstream iss(str_tmp);
				string temp;
				bool is1 = true;
				while (getline(iss, temp, '-')) {
					if (is1) {
						vec_str.push_back(temp);
						is1 = false;
					} else {
						vec_str.push_back("-" + temp);
					}
				}
			}
		}
	}

	//׼������
	bool isFirst = true;
	for (auto str_tmp:vec_str) {
		int pos = 0;
		pos = str_tmp.find('x');
		string str1;
		string str2;
		if(pos!=-1) {
			str1= str_tmp.substr(0, pos);
			if(pos+1>=str_tmp.length()){
				str2 = "1";
			}else{
				str2= str_tmp.substr(pos + 1, str_tmp.size());	
			}
		}else{
			str1= str_tmp.substr(0, pos);
			str2= "0";
		}

		double coef = atof(str1.c_str());
		int exp = atoi(str2.c_str());
		if (isFirst) {
			head = new polyNode;
			head->coef = coef;
			head->exp = exp;
			head->next = nullptr;
			tail = head;
			isFirst = false;
		} else {
			polyNode *s = new polyNode;
			s->coef = coef;
			s->exp = exp;
			s->next = nullptr;
			tail->next = s;
			tail = s;
		}
	}

}   //Poly::create(string str)


#endif //OJ_POLY_H

