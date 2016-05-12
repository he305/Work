function [] = graph()

data = dlmread('data.csv');

disp(data);

x = data(:, 1);
y = data(:, 2);

disp(y);
a = data(1, 4);
b = data(1, 5);

mnkX = linspace(0, max(x)*2);
mnkY = a*mnkX+b;

coords = plot(x, y, 'rx');
set(coords, 'LineWidth', 10);
hold on;
mnk = plot(mnkX, mnkY, '-k');
set(mnk, 'LineWidth', 2);
hold off;
end