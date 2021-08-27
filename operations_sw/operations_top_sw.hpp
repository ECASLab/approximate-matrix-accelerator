#pragma once

#define kCols 3
#define kRows 3

void operations_top(int selection, const float a[kRows][kCols],
                    const float b[kRows][kCols], const float c[kRows][kCols],
                    float res[kRows][kCols]);