//����������0��ʾ
LL monthdays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};//ƽ��ʱÿ�����ж�����
LL daysOfMonth(LL y,LL m){//�ж�y��m���м���
   if((y%400==0||y%4==0&&y%100!=0)&&m==2)//y���������Ҳ�ѯ2���м���
       return 29;//����2����29��
   return monthdays[m];//ֱ�ӷ���monthdays����Ӧλ�õ�����
}
LL determineWeek(LL y,LL m,LL d,LL week=2){//����1850��1��1�����ܶ�������y��m��d�����ܼ�
   for(LL i=1850;i<y;++i){//���1850�굽y�꾭�������
       LL temp=(i%400==0||i%4==0&&i%100!=0)?366:365;//ƽ����365�죬������366��
       week=(week+temp)%7;//����week
   }
   for(LL i=1;i<m;++i)//���1�µ�m�µ��·�
       week=(week+daysOfMonth(y,i))%7;//��������м��죬������week
   return (week+d-1)%7;//�����ܼ���ע��������0��ʾ
}
LL determineDayOfNumberWeek(LL y,LL m,LL b,LL c){//�ж�y��m�µ�b������c�Ǽ���
   LL week=determineWeek(y,m,1);//ȷ��y��m��1�����ܼ�
   return 1+(c+7-week)%7+7*(b-1);
}
