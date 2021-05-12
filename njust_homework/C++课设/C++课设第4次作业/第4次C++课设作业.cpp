#include<iostream>
#include<string>
#include<Windows.h>
#include"File.h"
using namespace std;

class MediaFile:public File{
	string mold;
	int width,height;
	int playtime;
public:
	void show();//show()����
	
	void setType(string);
	void setMold(string);
	void setPicInfo(int ,int);
	void setPlayerInfo(int);
	
	string getMold();
	int getPicWidth();
	int getPicHeight();
	int getPlayTime();
	
	MediaFile(string name="",string type="",double _size=0.0,string mold=""):File(name,type,_size){
		if(mold==""){
			this->setType(type);
		}else{
			if(mold=="��Ƶ"||mold=="��Ƶ"||mold=="ͼƬ")
				this->mold=mold;						
			else
				this->mold="δ֪����";					
		}
		width=-1;
		height=-1;
		playtime=-1;
	}
	
};

void MediaFile::show(){
	File::show();
	
	cout<<"�ļ�����: "<<mold<<endl;
	if(mold=="��Ƶ"||mold=="ͼƬ"){
		if(width==-1){
			cout<<"�޷���ȡ���ſ�ȣ�";
		}else{
			cout<<"���ſ��: "<<width; 	
		}
		cout<<"    ";
		if(height==-1){
			cout<<"�޷���ȡ���Ÿ߶ȣ�";
		}else{
			cout<<"    ���Ÿ߶�: "<<height; 
		}
		cout<<endl;
	}
	if(mold=="��Ƶ"||mold=="��Ƶ"){
		if(playtime==-1){
			cout<<"�޷���ȡ����ʱ��";
		}else{
			cout<<"����ʱ��: ";
			if(playtime/60){
				if(playtime/3600){
					cout<<playtime/3600<<"Сʱ";
					playtime%=3600;
					cout<<playtime/60<<"����"<<playtime%60<<"����";
				}else{
					cout<<playtime/60<<"����"<<playtime%60<<"����";
				}
			}else{
				cout<<playtime<<"����";
			}
		}
		cout<<endl;
	}
}
void MediaFile::setType(string type){
	File::SetType(type);
    transform(type.begin(),type.end(),type.begin(),::tolower);
    if(type=="mp3"||type=="wav"||type=="flac"||type=="cda"||type=="aac"||type=="midi"){
		this->mold="��Ƶ";
	}else if(type=="avi"||type=="wma"||type=="rmvb"||type=="rm"||type=="flash"
				||type=="mp4"||type=="mid"||type=="3gp"){
		this->mold="��Ƶ";					
	}else if(type=="bmp"||type=="jpg"||type=="png"||type=="tif"||type=="gif"||type=="tga"
				||type=="svg"||type=="psd"||type=="ai"||type=="wmf"||type=="webp"){
		this->mold="ͼƬ";
	}else{
		this->mold="δ֪����";
							
	}
}

void MediaFile::setMold(string mold){
	if(mold=="��Ƶ"||mold=="��Ƶ"||mold=="ͼƬ")
		this->mold=mold;						
	else
		this->mold="δ֪����";
	modify.UpdataTime();	
}

void MediaFile::setPicInfo(int width,int height){
	if(mold!="ͼƬ"&&mold!="��Ƶ"){
		cout<<"�ⲻ��ͼƬ����Ƶ���޷����������ԣ�"<<endl;
		return;
	}else{
		this->width=width;
		this->height=height;
		modify.UpdataTime();
	} 
}
void MediaFile::setPlayerInfo(int playtime){
	if(mold!="��Ƶ"&&mold!="��Ƶ"){
		cout<<"�ⲻ�����ֻ���Ƶ���޷����������ԣ�"<<endl;
		return;
	}else{
		this->playtime=playtime;
		modify.UpdataTime();
	} 
}

string MediaFile::getMold(){
	return mold;
}
int  MediaFile::getPicWidth(){
	return width;
}
int  MediaFile::getPicHeight(){
	return height;
}
int  MediaFile::getPlayTime(){
	return playtime;
}


int main(){
	cout<<"now create file"<<endl;
	MediaFile file("test","mp4",2.2);
	file.show();
	
	cout<<endl<<"now  sleep 3s"<<endl;
	Sleep(3000);
	
	cout<<endl<<"now updata file"<<endl;
	file.setPicInfo(1200,1080); 
	file.setPlayerInfo(22);
	file.show();
	
	cout<<endl<<"now get file type"<<endl;
	cout<<file.getMold()<<endl;
	return 0;
}
