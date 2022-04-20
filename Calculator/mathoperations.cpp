int factorial(int num){
    int fact = 1;
    bool isNegative = num < 0;
    if (isNegative) num *= -1;
    for (int i = 1; i <= num; i++)
        fact *= i;
    return fact * ((isNegative)? -1: 1);
}
