package com.wigryz.lab_7_fork;

import com.wigryz.lab_7_fork.sorting.DivideTask;

import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;


public class MergeSort {

    public static void main(String[] args) {

        int[] numbers = {2, 4, 1, 2, -2, 9, -10};
        DivideTask task = new DivideTask(numbers);
        ForkJoinPool forkJoinPool = new ForkJoinPool();

        forkJoinPool.execute(task);

        System.out.println(Arrays.toString(task.join()));
    }
} 
