#include <iostream>
#include <math.h>
#define LOWEST_PRIME 2
using namespace std;

void singleLine();
bool isPrimeNumber(int k);
int generatePrimeNumbers(int k, int*& primeNumbers);
void generateOutput(int k, int* primeNumbers, int actualPrime, int sum, int howManyLowerPrimes, int*& output, int position);

int main()
{
    int linesNumber;
    cin >> linesNumber;
    for (int i = 0; i < linesNumber; i++) {
        singleLine();
    }
}

bool isPrimeNumber(int k) {
    for (int i = LOWEST_PRIME; i <= (int)sqrt(k);i++) {
        if (k % i == 0) {
            return false;
        }
    }
    return true;
}

int generatePrimeNumbers(int k, int*& primeNumbers) {
    if (k < LOWEST_PRIME) {
        return 0;
    }
    int a = 0;
    primeNumbers[a] = LOWEST_PRIME;
    for (int i = LOWEST_PRIME + 1; i <= k;i++) {
        if (isPrimeNumber(i)) {
            a++;
            primeNumbers[a] = i;
        }
    }
    return a + 1;
}

void generateOutput(int k, int* primeNumbers, int actualPrime, int sum, int howManyLowerPrimes, int*& output, int position) {
    if (sum == 0) {
        output[0] = k;
        for (int i = 0; i < position; i++) {
            if (i == position - 1) {
                cout << output[i] << endl;
            }
            else {
                cout << output[i] << "+";
            }
        }
        return;
    }
    if (sum - actualPrime < 0) {
        return;
    }
    output[position] = actualPrime;
    sum -= actualPrime;
    for (int i = 0; i < howManyLowerPrimes; i++) {
        generateOutput(k, primeNumbers, primeNumbers[i], sum, i + 1, output, position + 1);
        if (sum == 0) {
            return;
        }
    }

}

void singleLine() {
    int n;int k;
    cin >> n;cin >> k;
    if (!isPrimeNumber(k)) {
        return;
    }
    int maxElementsQuantity = (n - k) / LOWEST_PRIME + 1;
    int* primeNumbers = (int*)malloc(n * sizeof(int));
    int howManyDiffPrimes = generatePrimeNumbers(k, primeNumbers);
    int* output = (int*)malloc(maxElementsQuantity * sizeof(int));

    for (int i = 0; i < howManyDiffPrimes; i++) {
        if (n - k == 0) {
            generateOutput(k, primeNumbers, primeNumbers[i], n - k, i + 1, output, 1);
            break;
        }
        else {
            generateOutput(k, primeNumbers, primeNumbers[i], n - k, i + 1, output, 1);

        }
    }
    free(primeNumbers);
    free(output);

}