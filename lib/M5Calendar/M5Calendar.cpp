#include "M5Calendar.h"

String getRankSuffix(int rank) {
    if (rank % 10 == 1 and rank != 11) {
        return "st";
    } else if (rank % 10 == 2 and rank != 12) {
        return "nd";
    } else if (rank % 10 == 3 and rank != 13) {
        return "rd";
    } else {
        return "th";
    }
}

String getMonth(int m) {
    String month[] = {"January",   "February", "March",    "April",
                      "May",       "June",     "July",     "August",
                      "September", "October",  "November", "December"};
    return month[m - 1];
}
