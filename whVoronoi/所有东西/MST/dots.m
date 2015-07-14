clc
mex myVoronoi.cpp
axis([0,500,0,500]);

hold on;box on;
title('鼠标左键输入,右键结束输入')

%gtext('用鼠标左键键入城市坐标点,右键结束输入');
x=[];
y=[];

count=0;
%grid                                        % 加入格栅

xlabel('x轴')
ylabel('y轴')

%存放输入点
coox=zeros(200);
cooy=zeros(200);

while(1)
    [x1,y1,button]=ginput(1);
    if(button~=1)
        break;
    end
    plot(x1,y1,'o');
    x=[x,x1];y=[y,y1];
    count=count+1;
    coox(count)=x1;
    cooy(count)=y1;
    text(x1,y1,num2str([x1,y1,count]));
end

%inarray是输入矩阵
inarray=zeros(count,2);
for i=1:1:count                    %for i = nBegin:nStep:nEnd
    inarray(i)=coox(i);
    inarray(i+count)=cooy(i);
end



[answer,outTriCnt,Center,edgeCnt]=myVoronoi(count,inarray);
%Center
%edgeCnt


for i=1:1:outTriCnt
   line([coox(answer((i-1)*6+1)) coox(answer((i-1)*6+2))],[cooy(answer((i-1)*6+1)) cooy(answer((i-1)*6+2))]);
   line([coox(answer((i-1)*6+3)) coox(answer((i-1)*6+4))],[cooy(answer((i-1)*6+3)) cooy(answer((i-1)*6+4))]);
   line([coox(answer((i-1)*6+5)) coox(answer((i-1)*6+6))],[cooy(answer((i-1)*6+5)) cooy(answer((i-1)*6+6))]);
   %line([coox(1) coox(2)],[cooy(1) cooy(2)]);
   %line([coox(answer(1)) coox(answer(2))],[cooy(answer(1)) cooy(answer(2))]);
end


for i=1:4:edgeCnt*2*2
    line([Center(i) Center(i+2)],[Center(i+1) Center(i+3)],'color','r');
end


hold off