cars_data = readtable('cars_clustered.csv');
cars_data = sortrows(cars_data,'cluster','ascend');

centroidX = [29.1805 14.9178 20.2966];
centroidY = [3.99219 8 6.0339];
centroidZ = [107.336 352.096 214.424];

scatter3(cars_data.mpg(1:128),cars_data.cylinders(1:128),cars_data.cubicinches(1:128),'r')
hold on
scatter3(cars_data.mpg(129:201),cars_data.cylinders(129:201),cars_data.cubicinches(129:201),'b')
scatter3(cars_data.mpg(202:end),cars_data.cylinders(202:end),cars_data.cubicinches(202:end),'g')
scatter3(centroidX, centroidY, centroidZ, 500, 'k', 'X');
xlabel('mpg');
ylabel('cylinders');
zlabel('cubicinches');
hold off