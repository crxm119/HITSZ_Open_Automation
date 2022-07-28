%ʵ��ʮ
close all; clear;
ds1=xlsread('data.xlsx','A1:E5');
%%
figure;hold on;box on;grid on;
x=ds1(2,:);
for i=1:3
    y=ds1(2+i,:);
    plot(x,y,'Linewidth',3.2-0.8*i);
end
xlabel('Ƶ��{\mu}/(��10^{14}HZ)');
ylabel('��ֹ��ѹU_{c}/V');
legend('2mm����','4mm����','8mm����');
title('U_{c}-{\mu}����');
%%
figure;hold on;box on;grid on;
%��С���˷�
h1=[];p=[];

%str=["2mm����","4mm����","8mm����"];
str={'2mm����','4mm����','8mm����'};
for i=1:3
    y=ds1(2+i,:);
    P=polyfit(x,y,1);
    p=[p,P(1)]
    h1=[h1,P(1)*1.602e-19*1e-14]
    plot(x,y,'*','DisplayName',char(str(i)));
    y=x*P(1)+P(2);
    plot(x,y,'Linewidth',3.2-0.8*i,'DisplayName',char(str(i)));
    %legend(str(i));
end
legend('show');
xlabel('Ƶ��{\mu}/(��10^{14}HZ)');
ylabel('��ֹ��ѹU_{c}/V');
title('U_{c}-{\mu}����');
h1=-mean(h1)
 h0=6.626e-34;
 d=abs(h1-h0)/h0
%��ͼ����ͼ��
figure;hold on;box on;grid on;
axis([5,8.5,-2,0]);
for i=1:3
    y=ds1(2+i,:);
    plot(x,y,'*','DisplayName',char(str(i)));
end
legend('show');
xlabel('Ƶ��{\mu}/(��10^{14}HZ)');
ylabel('��ֹ��ѹU_{c}/V');
title('U_{c}-{\mu}����');