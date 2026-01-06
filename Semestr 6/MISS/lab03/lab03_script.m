clear all
close all
clc

out = sim('wahadlo');
fi = out.fi;
L = str2num(get_param('wahadlo/Subsystem', 'L'));
m = str2num(get_param('wahadlo/Subsystem', 'm'));

for i = 1:length(fi)
    plot([0 -L*sin(fi(i))],[0 -L*cos(fi(i))],'Color','r','LineWidth',2);
    hold on
    plot(-L*sin(fi(i)), -L*cos(fi(i)), 'b.','MarkerSize',5*m);
    hold off
    axis([-1.1*L 1.1*L -1.1*L 1.1*L])
    pause(0.01)
end