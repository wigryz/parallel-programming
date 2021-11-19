package com.wigryz.lab_6;

import java.util.Random;


class Obraz {

    private int LICZBA_ZNAKOW;

    private int size_n;
    private int size_m;
    private char[][] tab;
    private char[] tab_symb;
    private int[] histogram;
    private int[] parallel_histogram;
    private int[] dec_histogram;

    public Obraz(int n, int m, int numOfChars) {
        LICZBA_ZNAKOW = numOfChars;
        this.size_n = n;
        this.size_m = m;
        tab = new char[n][m];
        tab_symb = new char[LICZBA_ZNAKOW];

        final Random random = new Random();

        // for general case where symbols could be not just integers
        for (int k = 0; k < LICZBA_ZNAKOW; k++) {
            tab_symb[k] = (char) (k + 33); // substitute symbols
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tab[i][j] = tab_symb[random.nextInt(LICZBA_ZNAKOW)];  // ascii 33-127
                //tab[i][j] = (char)(random.nextInt(94)+33);  // ascii 33-127
                System.out.print(tab[i][j] + " ");
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");

        histogram = new int[LICZBA_ZNAKOW];
        parallel_histogram = new int[LICZBA_ZNAKOW];
        dec_histogram = new int[LICZBA_ZNAKOW];
        clear_histogram();
    }

    public void clear_histogram() {

        for (int i = 0; i < LICZBA_ZNAKOW; i++) histogram[i] = 0;
        for (int i = 0; i < LICZBA_ZNAKOW; i++) histogram[i] = 0;
        for (int i = 0; i < LICZBA_ZNAKOW; i++) histogram[i] = 0;

    }

    public void calculate_histogram() {

        for (int i = 0; i < size_n; i++) {
            for (int j = 0; j < size_m; j++) {

                // optymalna wersja obliczania histogramu, wykorzystująca fakt, że symbole w tablicy
                // można przekształcić w indeksy tablicy histogramu
                // histogram[(int)tab[i][j]-33]++;

                // wersja bardziej ogólna dla tablicy symboli nie utożsamianych z indeksami
                // tylko dla tej wersji sensowne jest zrównoleglenie w dziedzinie zbioru znaków ASCII
                for (int k = 0; k < LICZBA_ZNAKOW; k++) {
                    if (tab[i][j] == tab_symb[k]) histogram[k]++;
                    //if(tab[i][j] == (char)(k+33)) histogram[k]++;
                }

            }
        }

    }

    public void calculateHistogramOf(int numOfChar) {
        for (int i = 0; i < size_n; i++) {
            for (int j = 0; j < size_m; j++) {
                if (tab[i][j] == tab_symb[numOfChar]) parallel_histogram[numOfChar]++;
            }
        }
    }

    public synchronized void printHistogramOf(int numOfChar) {
        System.out.print("Watek [" + numOfChar + "]: " + tab_symb[numOfChar] + " " + parallel_histogram[numOfChar] + " ");
        for (int i = 0; i < parallel_histogram[numOfChar]; i++) {
            System.out.print("=");
        }
        System.out.println();
    }

    public void print_histogram() {

        for (int i = 0; i < LICZBA_ZNAKOW; i++) {
            System.out.print(tab_symb[i] + " " + histogram[i] + "\n");
            //System.out.print((char)(i+33)+" "+histogram[i]+"\n");
        }

    }

    public boolean checkBothHistograms() {
        for (int i = 0; i < histogram.length; i++) {
            if (histogram[i] != parallel_histogram[i])
                return false;
        }
        return true;
    }

    public boolean checkBothHistogramsDec() {
        for (int i = 0; i < histogram.length; i++) {
            if (histogram[i] != dec_histogram[i])
                return false;
        }
        return true;
    }

    public void calculateHistogramBetween(int start, int end) {
        int localHistogram[] = new int[end - start];

        if(start == 4)
            System.out.println("x");

        for (int i = 0; i < size_n; i++) {
            for (int j = 0; j < size_m; j++) {
                for (int k = start; k < end; k++) {
//                    if (tab[i][j] == tab_symb[k]) localHistogram[k - start]++;
                    if (tab[i][j] == tab_symb[k]) dec_histogram[k]++;
                }
            }
        }
    }

    public synchronized void printHistogramBetween(int start, int end) {
        for(int k=start ; k < end ; k++) {
            System.out.print("Watek [" + Thread.currentThread().getName() + "]: " + tab_symb[k] + " " + dec_histogram[k] + " ");
            for (int i = 0; i < dec_histogram[k]; i++) {
                System.out.print("=");
            }
            System.out.println();
        }
    }
}
