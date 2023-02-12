unitsize(0.8cm);

path poly = (0, 0)--(2, 4)--(4, 0)--(5, 5)--(1, 6)--(1, 4)--(-1, 3)--cycle;
path line = (-2, 4)--(6, 1);
pair x = (3, 8);

path l1 = shift(x * 0.070224) * line;
path l2 = shift(x * -0.070224) * line;

fill(l1 -- reverse(l2) -- cycle, grey + opacity(0.4));
draw(line);
draw(l1, dotted);
draw(l2, dotted);

draw(poly, linewidth(.8));
