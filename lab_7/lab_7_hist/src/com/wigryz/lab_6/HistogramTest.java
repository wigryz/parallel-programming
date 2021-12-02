package com.wigryz.lab_6;

import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


class HistogramTest {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Set number of chars: ");
        int NUMBER_OF_CHARS = scanner.nextInt();

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m, NUMBER_OF_CHARS);

        obraz_1.calculate_histogram();
        obraz_1.print_histogram();

//
//        Watek[] NewThr = new Watek[num_threads];
//
//        for (int i = 0; i < num_threads; i++) {
//            (NewThr[i] = new Watek(i, obraz_1)).start();
//        }
//
//        for (int i = 0; i < num_threads; i++) {
//            try {
//                NewThr[i].join();
//            } catch (InterruptedException e) {
//            }
//        }
//
//        System.out.println("Czy oba histogramy sie zgadzaja? " + obraz_1.checkBothHistograms());
//
//
//        System.out.println("\n------------------------------------------\n");
//        System.out.println("DEKOMPOZYCJA HISTOGRAM\n");
        int num_threads = Runtime.getRuntime().availableProcessors();
        ExecutorService executor = Executors.newFixedThreadPool(num_threads);
        int charsForThread = (int) Math.ceil((double)NUMBER_OF_CHARS/num_threads);
        for (int i = 0; i < num_threads; i++) {
            int start = i * charsForThread;
            int end = Math.min(((i + 1) * charsForThread), NUMBER_OF_CHARS);
            executor.submit(new WatekDec(start, end, obraz_1));
        }

        executor.shutdown();
        while(!executor.isTerminated()) {}

        System.out.println("Czy oba histogramy sie zgadzaja? " + obraz_1.checkBothHistogramsDec());

    }

}

