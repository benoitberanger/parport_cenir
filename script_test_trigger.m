%% Clean up

close all
clear all
clc

% Check if Psychtoolbox is installed
assert( ~isempty(which('PsychtoolboxVersion')) , 'Psychtoolbox not detected' );

%% Send pulses

msg = 255;

WaitSecs(0.500);

pulse = 0;

while ~KbCheck
    
    pulse = pulse + 1;
    
    fprintf('Sending pulse #%d \n',pulse)
    
    parport_dev(msg);
%     parport_adr(msg);

    WaitSecs(0.001);
    
    parport_dev(0);
%     parport_adr(0);
    
    WaitSecs(0.500);
    
end

fprintf('End \n')
