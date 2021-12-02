package com.wigryz.lab_7;

import com.wigryz.lab_7.calka.Calka_callable;
import com.wigryz.lab_7.calka.Counter;
import com.wigryz.lab_7.calka.CounterPlus;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Simple_executor_test {

    private static final int NTHREADS = 10;
    private static final int NUMBER_OF_TASKS = 50;
    private static final double ACCURACY = 0.001;

    public static void main(String[] args) {

//        Calka_callable calka_callable = new Calka_callable(0, Math.PI, 0.001);
//
//        double result = calka_callable.compute();
//
//        System.out.println("Wynik: " + result);
//
//
//        System.out.println("------KONIEC PIERWSZEGO----------");

        ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

        List<Future<Double>> results = new ArrayList<>(NUMBER_OF_TASKS);
        double begin = 0.0;
        double end = Math.PI;
        double length = end - begin;
        double step = length/NUMBER_OF_TASKS;

        for (int i = 0; i < NUMBER_OF_TASKS; i++) {
            Calka_callable calka =
                new Calka_callable(step * (double)i, step * (double)(i+1), ACCURACY);

            Future<Double> future = executor.submit(calka);
            results.add(future);
        }

        Double result = 0.0;
        for(var future : results) {
            try {
                result += future.get();
            } catch (ExecutionException | InterruptedException e) {
                e.printStackTrace();
            }
        }

        // This will make the executor accept no new threads
        // and finish all existing threads in the queue
        executor.shutdown();

        System.out.println("Wynik: " + result);

//        // Wait until all threads finish
//        while (!executor.isTerminated()) {
//        }
//
//        System.out.println("Finished all threads");
//        System.out.format("\nCounter_1: %d, Counter_2 %d\n\n",
//            counter.get_c1(), counter.get_c2());
    }
} 
