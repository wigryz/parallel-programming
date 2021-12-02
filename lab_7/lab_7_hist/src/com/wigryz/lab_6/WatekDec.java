package com.wigryz.lab_6;

public class WatekDec implements Runnable {

    Obraz obraz;
    int start;
    int end;

    public WatekDec(int start, int end, Obraz obraz_1) {
        obraz = obraz_1;
        this.start = start;
        this.end = end;
    }

    @Override
    public void run() {
        obraz.calculateHistogramBetween(start, end);
        obraz.printHistogramBetween(start, end);
    }
}
