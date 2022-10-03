#include <stdio.h>

enum { INPUT_ERROR = 125 };

int 
main(void)
{
    double x, y;
    if (scanf("%lf%lf", &x, &y) != 2) {
        fprintf(stderr, "Input error\n");
        return INPUT_ERROR;
    }
    const double UPPER_BORDER = 7.0, LEFT_BORDER = 2.0, RIGHT_BORDER = 5.0, LOWER_BORDER = 1.0, DIAG_BORDER = x - 2.0;
    printf("%d\n", x >= LEFT_BORDER && x <= RIGHT_BORDER && y <= UPPER_BORDER && y >= LOWER_BORDER && y >= DIAG_BORDER);
    return 0;
}