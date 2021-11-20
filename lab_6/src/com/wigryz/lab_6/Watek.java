package com.wigryz.lab_6;

public class Watek extends Thread {

    Obraz obraz;
    int numOfChar = -1;

    public Watek(int numOfChar, Obraz obraz_1) {
        obraz = obraz_1;
        this.numOfChar = numOfChar;
    }

    @Override
    public void run() {
        obraz.calculateHistogramOf(numOfChar);
        obraz.printHistogramOf(numOfChar);
    }
}
