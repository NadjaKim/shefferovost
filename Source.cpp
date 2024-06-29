#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int* read_file(int* k, int* size, const char* filein) {
    int* arr = NULL;
    FILE* fin = fopen(filein, "r");
    if (fin) {
        char symb;
        int n;
        fscanf(fin, "%d %d ", k, &n);
        // *size = (*k) * (*k);
        *size = pow((*k), 2);
        arr = (int*)malloc(sizeof(int) * (*size));
        if (arr) {
            for (int i = 0; i < *size; i++) {
                fscanf(fin, "%c", &symb);
                arr[i] = (int)symb - '0';
            }
        }
        fclose(fin);
    }
    return arr;
}


int superposition(int k, int a, int b, int* arr) {
    int new_func = 0;
    for (int j = 0; j < k; j++) {
        int krutoye_nazvanie = 1;
        int i = a % k + (b % k) * k;
        for (int l = 0; l < j; l++)
            krutoye_nazvanie = krutoye_nazvanie * k;
        new_func = new_func + (arr[i]) * krutoye_nazvanie;
        a = a / k;
        b = b / k;
    }
    return new_func;
}

bool proverka(int* chek, int a) {
    if (chek[a] == 0) {
        chek[a] = 1;
        return false;
    }
    return true;
}

int solution(int k, int size, int* arr) {
    int* all_func = NULL;
    int all_size = pow(k, k);
    all_func = (int*)malloc(sizeof(int) * all_size);
    int* chek = (int*)calloc(all_size, sizeof(int));
    if (all_func && chek) {
        int new_func = 0;
        for (int i = 0; i < k; i++) {
            new_func = new_func + i * pow(k, i);
        }
        all_func[0] = new_func;
        chek[new_func] = 1;
        int stepen = 0;
        new_func = 0;
        for (int i = 0; i < size; i = i + k) {
            new_func = new_func + arr[i] * pow(k, stepen);
            stepen++;
        }
        all_func[1] = new_func;
        chek[new_func] = 1;
        int i = 0, j = 1; //i - ‎עמ ןנוג, א j - ‎עמ ך‏ננ
        int count_born = 2;
        while (j < count_born) {
            i = 0;
            while (i < j + 1) {
                new_func = superposition(k, all_func[i], all_func[j], arr);
                bool answer = proverka(chek, new_func);
                if (!answer) {
                    all_func[count_born] = new_func;
                    count_born++;
                }
                i++;
            }
            j++;
        }
        free(chek);
        if (count_born == all_size)
            return 1;
    }
    return 0;
}

void record_file(int answer, const char* fileout) {
    FILE* fout = fopen(fileout, "w");
    if (fout) {
        fprintf(fout, "%d", answer);
        fclose(fout);
    }
}


int main(int argc, char* argv[]) {
    int k, size;
    int answer = 0;
    //if (argc == 3) {
        int* arr = read_file(&k, &size, "input.txt");
        if (arr) {
            answer = solution(k, size, arr);
            record_file(answer, "output.txt");
            free(arr);
        }
    //}
    return 1;
}