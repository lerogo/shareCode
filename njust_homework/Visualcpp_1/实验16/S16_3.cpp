#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ifstream infile("cj.txt");
    ofstream outfile;
    outfile.open("cjout.txt");
    float score[300],sum=0;
    int i=0,n,n50=0,n60=0,n70=0,n80=0,n90=0;
    infile>>score[0];
    while(score[i]){
        i++;infile>>score[i];
    }
    n=i;
    for(int i=0;i<n;i++){
            int j=score[i];
        sum+=j;
        if(j<60) n50++;
        else if(j<70) n60++;
        else if(j<80) n70++;
        else if(j<90) n80++;
        else n90++;
    }
    double average;
    average = sum/n;
    outfile<<"������: "<<n<<endl;
    outfile<<"\nƽ���ɼ�: "<< average<<endl;
    outfile<<"90������: "<<n90<<" ��������: "<<(1.0*n90/n)<< endl; //�������ɼ��İٷ�
    outfile<<"80������: "<<n80<<" ��������: "<<(1.0*n80/n)<< endl;
    outfile<<"70������: "<<n70<<" ��������: "<<(1.0*n70/n)<< endl;
    outfile<<"60������: "<<n60<<" ��������: "<<(1.0*n60/n)<< endl;
    outfile<<"������: "<<n50<<" ��������: "<<(1.0*n50/n)<< endl;
    infile.close();
    outfile.close();
    return 0;
}
