close all
clear all
clc

%%

msg = 255;

WaitSecs(0.500);

while ~KbCheck
    
    parport_dev(msg);
%     parport_adr(msg);
    WaitSecs(0.001);
    parport_dev(0);
%     parport_adr(0);
    
    WaitSecs(0.500);
    
end