function [] = graph()

data = dlmread('data.csv');

disp(data);

x = data(:, 1);
y = data(:, 2);

data = dlmread('koff.csv');

koff = data(:, 1);

#mnkX = linspace(min(x), x(length(x)-1) + 5);
mnkX = linspace(x(length(x)-4) - 5, x(length(x)) + 5);
mnkY = [];
i = 0;
j = 1;
for k = 1:length(mnkX)
  sum = 0;
  for i = 0:length(koff)-1
    sum = sum + koff(i+1)*mnkX(k)^i
  endfor
  mnkY(k) = sum;
endfor

coords = plot(x, y, 'rx');
set(coords, 'LineWidth', 10);
hold on;
mnk = plot(mnkX, mnkY, '-k');
set(mnk, 'LineWidth', 2);
hold off;
end