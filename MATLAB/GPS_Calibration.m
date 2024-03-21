% Based on logreader.m
% Use this script to read data from your micro SD card

clear;
%clf;

filenum = '005'; % file number for the data you want to read
infofile = strcat('INF', filenum, '.TXT');
datafile = strcat('LOG', filenum, '.BIN');

%% map from datatype to length in bytes
dataSizes.('float') = 4;
dataSizes.('ulong') = 4;
dataSizes.('int') = 4;
dataSizes.('int32') = 4;
dataSizes.('uint8') = 1;
dataSizes.('uint16') = 2;
dataSizes.('char') = 1;
dataSizes.('bool') = 1;

%% read from info file to get log file structure
fileID = fopen(infofile);
items = textscan(fileID,'%s','Delimiter',',','EndOfLine','\r\n');
fclose(fileID);
[ncols,~] = size(items{1});
ncols = ncols/2;
varNames = items{1}(1:ncols)';
varTypes = items{1}(ncols+1:end)';
varLengths = zeros(size(varTypes));
colLength = 256;
for i = 1:numel(varTypes)
    varLengths(i) = dataSizes.(varTypes{i});
end
R = cell(1,numel(varNames));

%% read column-by-column from datafile
fid = fopen(datafile,'rb');
for i=1:numel(varTypes)
    %# seek to the first field of the first record
    fseek(fid, sum(varLengths(1:i-1)), 'bof');
    
    %# % read column with specified format, skipping required number of bytes
    R{i} = fread(fid, Inf, ['*' varTypes{i}], colLength-varLengths(i));
    eval(strcat(varNames{i},'=','R{',num2str(i),'};'));
end
fclose(fid);

%% Code to Plot the x,y positions overlaid on the campus map.
% Read and Display img
Campus_img = imread("C:\Users\josap\OneDrive\Documents\GitHub\E80-Final-Project\assets\img\GPS_test_2.png");
figure(1);
clf;
imshow(Campus_img);
hold on
 
% Read and Plot x,y positions
scale_factor_x = 8.7;
scale_factor_y = 7.8;
x = (x .* scale_factor_x) + 400;
y = (y .* scale_factor_y) + 350;
plot(x, y, 'b*', 'MarkerSize', 10);
title('Overlaid Plot Showing The Walk Around Parsons');
xlabel('x coordinate');
ylabel('y coordinate');
hold off