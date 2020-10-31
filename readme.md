Problem:
Let there be n points in a plane.Find the minimum distance between any two points.

Formula:
The distance between two points can be fiund using Distance Formula:-
dist=sqrt((x2-x1)^2+(y2-y1)^2);

Approach:
Lets divide the plane into two halves. The following three cases are possible after the division :-

1. The two points can be in the left of the line of division.
2. The two points can be in the right of the line of division.
3. One point is on left and other is on the right of the line of division.

Steps:
Sort the vector according to the x-coordinate.
Recursively divide the vector into 2 halves (mid=n/2) and find the minimum distance points on each division.
Also Sort the vector according to the y-coordinate.
Recursively find the minimum distance pair such that both are on opposite side of the division line.
