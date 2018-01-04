%% Clean up

clear all % to be sure to clean all MEX files
clc

% Check if Psychtoolbox is installed
assert( ~isempty(which('PsychtoolboxVersion')) , 'Psychtoolbox not detected' );


%% Prepare

msg = 0;

ppmex

ppmex('open')
ppmex('write',0) % set 0, just to be sure

WaitSecs(0.100); % PTB function


%% Send pulses

fprintf('Press any key to stop the loop \n')

while ~KbCheck % continue until keybind detection
    
    msg = msg + 1;
    fprintf('Sending pulse #%d \n',msg)
    
    % Send pulse/message
    ppmex('write',msg);
    WaitSecs(0.001);
    ppmex('write',0);
    
    if msg == 255
        msg = -1;
    end
    
    WaitSecs(0.020);
    
end


%% End

ppmex('close')

fprintf('End \n')
