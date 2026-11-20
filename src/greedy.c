#include "greedy.h"
#include <limits.h>
#include <stdlib.h>

size_t greedy_activity_selection(const Activity *activities, size_t count, size_t *selected) {
    if ((count && !activities) || (count && !selected)) return 0;

    Activity *copy = malloc(count * sizeof(*copy));
    size_t *ids = malloc(count * sizeof(*ids));
    if (count && (!copy || !ids)) {
        free(copy);
        free(ids);
        return 0;
    }

    for (size_t i = 0; i < count; i++) {
        if (activities[i].finish < activities[i].start) {
            free(copy);
            free(ids);
            return 0;
        }
        copy[i] = activities[i];
        ids[i] = i;
    }

    /* Sort by finishing time so the earliest finishing activity is considered first. */
    for (size_t i = 1; i < count; i++) {
        Activity key = copy[i];
        size_t id = ids[i], j = i;
        while (j && copy[j - 1].finish > key.finish) {
            copy[j] = copy[j - 1];
            ids[j] = ids[j - 1];
            j--;
        }
        copy[j] = key;
        ids[j] = id;
    }

    size_t used = 0;
    int finish = INT_MIN;
    for (size_t i = 0; i < count; i++) {
        if (copy[i].start >= finish) {
            selected[used++] = ids[i];
            finish = copy[i].finish;
        }
    }

    free(copy);
    free(ids);
    return used;
}
