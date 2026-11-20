# Greedy algorithm: Activity Selection

A greedy algorithm makes the best available local choice according to a rule. Activity Selection chooses the largest set of activities that do not overlap.

## Workflow

1. Enter each activity's start and finish times.
2. The program sorts activities by finishing time.
3. It selects the first activity, then selects the next activity whose start time is at or after the finish time of the last selected activity.
4. It displays the selected activity numbers.

The implementation uses insertion sort to order the activities, so its overall time complexity is O(n²). The selection scan itself is O(n).

Activities that finish at time t can be followed by an activity that starts at time t.
