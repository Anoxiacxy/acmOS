//
// Created by Wenxin Zheng on 2021/4/21.
//

#ifndef ACMOS_SPR21_ANSWER_PRINTK_H
#define ACMOS_SPR21_ANSWER_PRINTK_H

static void printk_write_string(const char *str) {
    // Homework 1: YOUR CODE HERE
    // this function print string by the const char pointer
    // I think 3 lines of codes are enough, do you think so?
    // It's easy for you, right?
    while (*str)
        uart_putc(*str), ++str;
}


static void printk_write_num(int base, unsigned long long n, int neg) {
    // Homework 1: YOUR CODE HERE
    // this function print number `n` in the base of `base` (base > 1)
    // you may need to call `printk_write_string`
    // you do not need to print prefix like "0x", "0"...
    // Remember the most significant digit is printed first.
    // It's easy for you, right?
    const int size = 100;
    char stack[size], *top = stack + size;
    *--top = '\0';
    do {
        char digit = n % base;
        if (digit < 10)
            digit += '0';
        else
            digit += 'a' - 10;
        *--top = digit;
        n /= base;
    } while (n);
    if (neg)
        *--top = '-';
    printk_write_string(top);
}

#endif  // ACMOS_SPR21_ANSWER_PRINTK_H