%���ȵ������ݱ��
load data.mat
%�����ʽת��double
b=table2array(data);
%��ȡx ��y ����
x=b(:,1);
y=[b(:,2),b(:,4),b(:,6)];
%ԭͼ
figure
plot([x,x,x],y)
xlabel('U_{G2K}/V')
ylabel('I_{A}/nA')
title('I_{A}-U_{G2K}����(ԭͼ)')
legend('V_{G2A}=7V','V_{G2A}=6.5V','V_{G2A}=7.5V')
%������δ��õ�yֵ��ֵ����ȡ����ƽ��ֵ
for j=1:3
    for i=1:180
        if isnan(y(i,j))==1
            y(i,j)=0.5*(y(i-1,j)+y(i+1,j));
        end
    end
end
%�����ֵ
x1=(0:0.1:90)';
y1(:,1)=interp1(x,y(:,1),x1,'spline');
y1(:,2)=interp1(x,y(:,2),x1,'spline');
y1(:,3)=interp1(x,y(:,3),x1,'spline');
%ƽ����ͼ
figure
plot([x1,x1,x1],y1)
xlabel('U_{G2K}/V')
ylabel('I_{A}/nA')
title('I_{A}-U_{G2K}����(��ֵ)')
legend('V_{G2A}=7V','V_{G2A}=6.5V','V_{G2A}=7.5V')
%��ֵ
figure
plot([x1,x1,x1],y1)
xlabel('U_{G2K}/V')
ylabel('I_{A}/nA')
title('I_{A}-U_{G2K}����(�����)')
hold on;
ans=zeros(7,3);
p=1;
for j=1:3
    for i=2:length(y1)-1
        if y1(i,j)>10&y1(i,j)>= y1(i-1,j)& y1(i,j)>= y1(i+1,j)
            plot(x1(i),y1(i,j),'R*');
            str=num2str(x1(i));
            text(x1(i),y1(i,j),str);
            if p<=7
                ans(p,j)=x1(i);
                p=p+1;
            end
        end
    end
    p=1;
end
%��С���˷�
temp=(1:7)';
Pfinal=[];
for i=1:3
    P=polyfit(temp,ans(:,i),1);
    Pfinal=[Pfinal;P];
end
average=(Pfinal(1,1)+Pfinal(2,1)+Pfinal(3,1))/3



