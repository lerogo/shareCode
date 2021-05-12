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
	void show();//show()函数
	
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
			if(mold=="视频"||mold=="音频"||mold=="图片")
				this->mold=mold;						
			else
				this->mold="未知类型";					
		}
		width=-1;
		height=-1;
		playtime=-1;
	}
	
};

void MediaFile::show(){
	File::show();
	
	cout<<"文件类型: "<<mold<<endl;
	if(mold=="视频"||mold=="图片"){
		if(width==-1){
			cout<<"无法获取播放宽度！";
		}else{
			cout<<"播放宽度: "<<width; 	
		}
		cout<<"    ";
		if(height==-1){
			cout<<"无法获取播放高度！";
		}else{
			cout<<"    播放高度: "<<height; 
		}
		cout<<endl;
	}
	if(mold=="音频"||mold=="视频"){
		if(playtime==-1){
			cout<<"无法获取播放时间";
		}else{
			cout<<"播放时间: ";
			if(playtime/60){
				if(playtime/3600){
					cout<<playtime/3600<<"小时";
					playtime%=3600;
					cout<<playtime/60<<"分钟"<<playtime%60<<"秒钟";
				}else{
					cout<<playtime/60<<"分钟"<<playtime%60<<"秒钟";
				}
			}else{
				cout<<playtime<<"秒钟";
			}
		}
		cout<<endl;
	}
}
void MediaFile::setType(string type){
	File::SetType(type);
    transform(type.begin(),type.end(),type.begin(),::tolower);
    if(type=="mp3"||type=="wav"||type=="flac"||type=="cda"||type=="aac"||type=="midi"){
		this->mold="音频";
	}else if(type=="avi"||type=="wma"||type=="rmvb"||type=="rm"||type=="flash"
				||type=="mp4"||type=="mid"||type=="3gp"){
		this->mold="视频";					
	}else if(type=="bmp"||type=="jpg"||type=="png"||type=="tif"||type=="gif"||type=="tga"
				||type=="svg"||type=="psd"||type=="ai"||type=="wmf"||type=="webp"){
		this->mold="图片";
	}else{
		this->mold="未知类型";
							
	}
}

void MediaFile::setMold(string mold){
	if(mold=="视频"||mold=="音频"||mold=="图片")
		this->mold=mold;						
	else
		this->mold="未知类型";
	modify.UpdataTime();	
}

void MediaFile::setPicInfo(int width,int height){
	if(mold!="图片"&&mold!="视频"){
		cout<<"这不是图片或视频，无法设置其属性！"<<endl;
		return;
	}else{
		this->width=width;
		this->height=height;
		modify.UpdataTime();
	} 
}
void MediaFile::setPlayerInfo(int playtime){
	if(mold!="音频"&&mold!="视频"){
		cout<<"这不是音乐或视频，无法设置其属性！"<<endl;
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
