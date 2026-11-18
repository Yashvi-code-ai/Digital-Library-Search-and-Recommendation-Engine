#include "book.h"
#include "library.h"
#include "algorithms.h"
#include "divide_conquer.h"
#include "greedy.h"
#include "dp.h"
#include "backtracking.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define DATA_FILE "data/books.csv"

static void input_book(Book *book) {
    read_line("Title: ", book->title, sizeof book->title);
    read_line("Author: ", book->author, sizeof book->author);
    read_line("Category: ", book->category, sizeof book->category);
    read_line("Keywords (separated by spaces): ", book->keywords, sizeof book->keywords);
    if (!read_int("Citation count (0 or more): ", &book->citations)) book->citations = 0;
    if (!read_int("Popularity score (0 or more): ", &book->popularity)) book->popularity = 0;
}

static void add_book(Library *library) {
    Book book = {0};
    book.id = library_next_id(library);
    puts("\nEnter book details:");
    input_book(&book);
    if (!book.title[0] || !book.author[0]) {
        puts("Title and author are required.");
        return;
    }
    if (library_add(library, &book)) puts("Book added successfully.");
    else puts("Could not add book (duplicate ID or insufficient memory).");
}

static void edit_book(Library *library) {
    int id;
    if (!read_int("Enter book ID to update: ", &id)) { puts("Invalid ID."); return; }
    int index = library_find_id(library, id);
    if (index < 0) { puts("Book not found."); return; }
    Book replacement = {0};
    puts("Enter replacement details:");
    input_book(&replacement);
    if (!replacement.title[0] || !replacement.author[0]) {
        puts("Title and author are required.");
        return;
    }
    if (library_update(library, id, &replacement)) puts("Book updated.");
}

static void delete_book(Library *library) {
    int id;
    if (!read_int("Enter book ID to delete: ", &id)) { puts("Invalid ID."); return; }
    puts(library_remove(library, id) ? "Book deleted." : "Book not found.");
}

static void show_search_result(const Library *library, int index) {
    if (index >= 0) print_book(&library->items[index]);
    else puts("No exact title match found.");
}

static void ensure_title_order(Library *library) {
    if (books_sorted_by_title(library->items, library->count)) return;
    puts("Binary search needs titles sorted alphabetically.");
    if (merge_sort_books(library->items, library->count))
        puts("The library has been sorted using Merge Sort.");
    else
        puts("Could not allocate memory for sorting.");
}

static void search_sort_menu(Library *library) {
    int choice;
    for (;;) {
        puts("\n========== PHASE 2: SEARCHING AND SORTING ==========");
        puts("1. Linear Search (exact title)");
        puts("2. Iterative Binary Search");
        puts("3. Recursive Binary Search");
        puts("4. Sort books using Merge Sort");
        puts("5. Sort books using Quick Sort");
        puts("6. Display current book order");
        puts("0. Return to main menu");
        if (!read_int("Choose an option: ", &choice)) {
            puts("Please enter a valid number.");
            continue;
        }
        if (choice == 0) return;
        if (choice >= 1 && choice <= 3) {
            char title[TITLE_LEN];
            int index;
            read_line("Enter the complete book title: ", title, sizeof title);
            if (!title[0]) { puts("Title cannot be empty."); continue; }
            if (choice == 1) index = linear_search_title(library->items, library->count, title);
            else {
                ensure_title_order(library);
                if (!books_sorted_by_title(library->items, library->count)) continue;
                index = choice == 2
                    ? binary_search_title_iterative(library->items, library->count, title)
                    : binary_search_title_recursive(library->items, library->count, title);
            }
            show_search_result(library, index);
        } else if (choice == 4) {
            puts(merge_sort_books(library->items, library->count)
                ? "Merge Sort completed. Books are now in alphabetical order."
                : "Merge Sort could not allocate the required temporary memory.");
        } else if (choice == 5) {
            quick_sort_books(library->items, library->count);
            puts("Quick Sort completed. Books are now in alphabetical order.");
        } else if (choice == 6) library_list(library);
        else puts("Unknown option. Try again.");
    }
}

static void maximum_subarray_menu(void) {
    int count;
    if (!read_int("How many integers (1-1000)? ", &count) || count < 1 || count > 1000) {
        puts("Please enter a count from 1 to 1000."); return;
    }
    long long *values = (long long *)malloc((size_t)count * sizeof(long long));
    if (!values) { puts("Not enough memory."); return; }
    for (int i=0;i<count;i++) {
        int value;
        char prompt[48];
        snprintf(prompt,sizeof prompt,"Value %d: ",i+1);
        if (!read_int(prompt,&value)) { puts("Invalid value."); free(values); return; }
        values[i]=value;
    }
    MaxSubarrayResult result;
    if (maximum_subarray_divide_conquer(values,(size_t)count,&result))
        printf("Maximum subarray sum: %lld\nZero-based range: %zu to %zu\n",
               result.sum,result.start,result.end);
    else puts("Could not calculate the maximum subarray.");
    free(values);
}

static void fast_power_menu(void) {
    int base, exponent;
    if (!read_int("Enter integer base: ",&base) ||
        !read_int("Enter non-negative exponent: ",&exponent) || exponent < 0) {
        puts("Invalid base or exponent."); return;
    }
    long long result;
    if (fast_power(base,(unsigned int)exponent,&result))
        printf("Result: %lld\n",result);
    else puts("The result is outside the range of long long.");
}

static void celebrity_menu(void) {
    int count;
    if (!read_int("Number of people (1-20): ",&count) || count < 1 || count > 20) {
        puts("Please enter a count from 1 to 20."); return;
    }
    int matrix[400];
    puts("Enter the 0/1 knows matrix row by row (person i knows person j):");
    for (int i=0;i<count;i++) for (int j=0;j<count;j++) {
        char prompt[48];
        int value;
        snprintf(prompt,sizeof prompt,"knows[%d][%d]: ",i,j);
        if (!read_int(prompt,&value) || (value != 0 && value != 1)) {
            puts("Every matrix entry must be 0 or 1."); return;
        }
        matrix[i*count+j]=value;
    }
    int answer=celebrity_divide_conquer(matrix,(size_t)count);
    if (answer < 0) puts("No celebrity exists.");
    else printf("Celebrity found: person %d (zero-based index).\n",answer);
}

static void matrix_menu(void) {
    int n;
    if (!read_int("Enter square matrix dimension (1-8): ",&n) || n < 1 || n > 8) {
        puts("Please enter a dimension from 1 to 8."); return;
    }
    long long a[64],b[64],classic[64],strassen[64];
    puts("Enter Matrix A row by row:");
    for (int i=0;i<n*n;i++) {
        int value;
        if (!read_int("Value: ",&value)) { puts("Invalid matrix value."); return; }
        a[i]=value;
    }
    puts("Enter Matrix B row by row:");
    for (int i=0;i<n*n;i++) {
        int value;
        if (!read_int("Value: ",&value)) { puts("Invalid matrix value."); return; }
        b[i]=value;
    }
    if (!matrix_multiply_classical(a,b,classic,(size_t)n) ||
        !matrix_multiply_strassen(a,b,strassen,(size_t)n)) {
        puts("Matrix multiplication failed."); return;
    }
    puts("\nClassical multiplication result:");
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) printf("%lld ",classic[i*n+j]);
        putchar('\n');
    }
    puts("Strassen multiplication result:");
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) printf("%lld ",strassen[i*n+j]);
        putchar('\n');
    }
    puts("Both methods should produce the same result.");
}

static void divide_conquer_menu(void) {
    int choice;
    for (;;) {
        puts("\n========== PHASE 3: DIVIDE AND CONQUER ==========");
        puts("1. Maximum Subarray");
        puts("2. Fast Powering");
        puts("3. Celebrity Problem");
        puts("4. Compare Classical and Strassen Matrix Multiplication");
        puts("0. Return to main menu");
        if (!read_int("Choose an option: ",&choice)) { puts("Enter a valid number."); continue; }
        switch (choice) {
            case 0: return;
            case 1: maximum_subarray_menu(); break;
            case 2: fast_power_menu(); break;
            case 3: celebrity_menu(); break;
            case 4: matrix_menu(); break;
            default: puts("Unknown option. Try again.");
        }
    }
}


static int read_activity_list(Activity *activities, size_t count) {
    for (size_t i=0;i<count;i++) {
        char prompt[64];
        snprintf(prompt,sizeof prompt,"Activity %zu start time: ",i+1);
        if(!read_int(prompt,&activities[i].start)) return 0;
        snprintf(prompt,sizeof prompt,"Activity %zu finish time: ",i+1);
        if(!read_int(prompt,&activities[i].finish) ||
           activities[i].finish<activities[i].start) return 0;
    }
    return 1;
}

static void activity_selection_menu(void) {
    int n;
    if(!read_int("Number of activities (1-100): ",&n)||n<1||n>100){puts("Invalid count.");return;}
    Activity a[100];size_t selected[100];
    if(!read_activity_list(a,(size_t)n)){puts("Invalid activity interval.");return;}
    size_t used=greedy_activity_selection(a,(size_t)n,selected);
    printf("Selected %zu compatible activities (original input numbers):\n",used);
    for(size_t i=0;i<used;i++)printf("Activity %zu: [%d, %d]\n",selected[i]+1,a[selected[i]].start,a[selected[i]].finish);
}

static void interval_partition_menu(void) {
    int n;
    if(!read_int("Number of activities (1-100): ",&n)||n<1||n>100){puts("Invalid count.");return;}
    Activity a[100];ScheduledActivity schedule[100];
    if(!read_activity_list(a,(size_t)n)){puts("Invalid activity interval.");return;}
    size_t rooms=greedy_interval_partition(a,(size_t)n,schedule);
    if(!rooms){puts("Could not assign rooms.");return;}
    printf("Minimum rooms required: %zu\n",rooms);
    for(int room=0;room<(int)rooms;room++){
        printf("Room %d:",room+1);
        for(int i=0;i<n;i++)if(schedule[i].room==room)
            printf(" Activity %d [%d,%d]",schedule[i].original_index+1,schedule[i].start,schedule[i].finish);
        putchar('\n');
    }
}

static void huffman_menu(void) {
    int n;
    if(!read_int("Number of distinct symbols (1-50): ",&n)||n<1||n>50){puts("Invalid count.");return;}
    HuffmanSymbol symbols[50];char codes[50][256];
    for(int i=0;i<n;i++){
        char prompt[64];int ch;int freq;
        snprintf(prompt,sizeof prompt,"Symbol %d (enter ASCII code 33-126): ",i+1);
        if(!read_int(prompt,&ch)||ch<33||ch>126){puts("Invalid symbol.");return;}
        for(int j=0;j<i;j++)if(symbols[j].symbol==(char)ch){puts("Symbols must be unique.");return;}
        snprintf(prompt,sizeof prompt,"Frequency for %c: ",ch);
        if(!read_int(prompt,&freq)||freq<=0){puts("Frequency must be positive.");return;}
        symbols[i]=(HuffmanSymbol){(char)ch,(unsigned long long)freq};
    }
    if(!greedy_huffman(symbols,(size_t)n,codes)){puts("Huffman coding failed.");return;}
    puts("Huffman codes:");
    for(int i=0;i<n;i++)printf("%c (frequency %llu): %s\n",symbols[i].symbol,symbols[i].frequency,codes[i]);
}

static int read_weighted_matrix(int *graph,int n) {
    puts("Enter adjacency matrix (0 = no edge; use positive weights):");
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        char prompt[48];int value;
        snprintf(prompt,sizeof prompt,"weight[%d][%d]: ",i,j);
        if(!read_int(prompt,&value)||value<0)return 0;
        graph[i*n+j]=value;
    }
    return 1;
}

static void dijkstra_menu(void) {
    int n,source;
    if(!read_int("Number of vertices (1-20): ",&n)||n<1||n>20){puts("Invalid count.");return;}
    int graph[400],parent[20];long long dist[20];
    if(!read_weighted_matrix(graph,n)){puts("Invalid matrix. Negative weights are not allowed.");return;}
    if(!read_int("Source vertex (zero-based): ",&source)||source<0||source>=n){puts("Invalid source.");return;}
    if(!greedy_dijkstra(graph,(size_t)n,(size_t)source,dist,parent)){puts("Dijkstra failed.");return;}
    for(int i=0;i<n;i++){
        if(dist[i]==LLONG_MAX)printf("Vertex %d: unreachable\n",i);
        else printf("Vertex %d: distance %lld, predecessor %d\n",i,dist[i],parent[i]);
    }
}

static void prim_menu(void) {
    int n;
    if(!read_int("Number of vertices (1-20): ",&n)||n<1||n>20){puts("Invalid count.");return;}
    int graph[400];WeightedEdge tree[19];long long total;
    if(!read_weighted_matrix(graph,n)){puts("Invalid matrix.");return;}
    if(!greedy_prim(graph,(size_t)n,tree,&total)){puts("Prim failed. Check that the graph is connected and undirected.");return;}
    puts("Minimum spanning tree edges:");
    for(int i=0;i<n-1;i++)printf("%d -- %d (weight %d)\n",tree[i].u,tree[i].v,tree[i].weight);
    printf("Total MST weight: %lld\n",total);
}

static void kruskal_menu(void) {
    int n,m;
    if(!read_int("Number of vertices (1-20): ",&n)||n<1||n>20||
       !read_int("Number of edges (0-100): ",&m)||m<0||m>100){puts("Invalid graph size.");return;}
    WeightedEdge edges[100],tree[19];size_t used;long long total;
    for(int i=0;i<m;i++){
        int u,v,w;char prompt[48];
        snprintf(prompt,sizeof prompt,"Edge %d first vertex: ",i+1);
        if(!read_int(prompt,&u)){puts("Invalid edge.");return;}
        snprintf(prompt,sizeof prompt,"Edge %d second vertex: ",i+1);
        if(!read_int(prompt,&v)){puts("Invalid edge.");return;}
        snprintf(prompt,sizeof prompt,"Edge %d weight: ",i+1);
        if(!read_int(prompt,&w)||u<0||v<0||u>=n||v>=n||u==v||w<0){puts("Invalid edge.");return;}
        edges[i]=(WeightedEdge){u,v,w};
    }
    if(!greedy_kruskal(edges,(size_t)m,(size_t)n,tree,&used,&total)){puts("Kruskal failed: graph may be disconnected.");return;}
    puts("Minimum spanning tree edges:");
    for(size_t i=0;i<used;i++)printf("%d -- %d (weight %d)\n",tree[i].u,tree[i].v,tree[i].weight);
    printf("Total MST weight: %lld\n",total);
}

static void fractional_knapsack_menu(void) {
    int n,capacity;
    if(!read_int("Number of items (1-100): ",&n)||n<1||n>100||
       !read_int("Knapsack capacity: ",&capacity)||capacity<0){puts("Invalid input.");return;}
    KnapsackItem items[100];double fractions[100],value;
    for(int i=0;i<n;i++){
        int weight,item_value;char prompt[48];
        snprintf(prompt,sizeof prompt,"Item %d weight: ",i+1);
        if(!read_int(prompt,&weight)||weight<=0){puts("Weight must be positive.");return;}
        snprintf(prompt,sizeof prompt,"Item %d value: ",i+1);
        if(!read_int(prompt,&item_value)||item_value<0){puts("Value cannot be negative.");return;}
        items[i]=(KnapsackItem){weight,(double)item_value};
    }
    if(!greedy_fractional_knapsack(items,(size_t)n,capacity,fractions,&value)){puts("Knapsack calculation failed.");return;}
    for(int i=0;i<n;i++)printf("Item %d: take %.2f%%\n",i+1,fractions[i]*100.0);
    printf("Maximum fractional value: %.2f\n",value);
}

static void greedy_menu(void) {
    int choice;
    for(;;){
        puts("\n========== PHASE 4: GREEDY ALGORITHMS ==========");
        puts("1. Activity Selection");
        puts("2. Interval Partitioning");
        puts("3. Huffman Coding");
        puts("4. Dijkstra Shortest Paths");
        puts("5. Prim Minimum Spanning Tree");
        puts("6. Kruskal Minimum Spanning Tree");
        puts("7. Fractional Knapsack");
        puts("0. Return to main menu");
        if(!read_int("Choose an option: ",&choice)){puts("Enter a valid number.");continue;}
        switch(choice){
            case 0:return;
            case 1:activity_selection_menu();break;
            case 2:interval_partition_menu();break;
            case 3:huffman_menu();break;
            case 4:dijkstra_menu();break;
            case 5:prim_menu();break;
            case 6:kruskal_menu();break;
            case 7:fractional_knapsack_menu();break;
            default:puts("Unknown option. Try again.");
        }
    }
}


static void dynamic_programming_menu(void){
 int choice;
 for(;;){
  puts("\\n========== PHASE 5: DYNAMIC PROGRAMMING ==========");
  puts("1. 0/1 Knapsack");puts("2. Matrix Chain Multiplication");puts("3. Longest Common Subsequence");
  puts("4. Optimal BST");puts("5. Bellman-Ford");puts("6. Floyd-Warshall");puts("7. Bounded TSP");puts("0. Return");
  if(!read_int("Choose: ",&choice))continue;
  if(choice==0)return;
  long long result=0;
  if(choice==1){int n,cap,w[80],v[80];if(!read_int("Items (1-80): ",&n)||n<1||n>80||!read_int("Capacity: ",&cap)||cap<0||cap>100000){puts("Invalid.");continue;}for(int i=0;i<n;i++)if(!read_int("Weight: ",&w[i])||!read_int("Value: ",&v[i]))return;if(dp_knapsack(w,v,n,cap,&result))printf("Best value: %lld\\n",result);else puts("Invalid items.");}
  else if(choice==2){int n,d[31];if(!read_int("Number of matrices (1-30): ",&n)||n<1||n>30)continue;for(int i=0;i<=n;i++)if(!read_int("Dimension: ",&d[i]))return;if(dp_chain(d,n,&result))printf("Minimum scalar multiplications: %lld\\n",result);else puts("Calculation failed.");}
  else if(choice==3){char a[256],b[256];size_t len;read_line("First string: ",a,sizeof a);read_line("Second string: ",b,sizeof b);if(dp_lcs(a,b,&len))printf("LCS length: %zu\\n",len);}
  else if(choice==4){int n,f[80];if(!read_int("Number of ordered keys (1-80): ",&n)||n<1||n>80)continue;for(int i=0;i<n;i++)if(!read_int("Frequency: ",&f[i]))return;if(dp_obst(f,n,&result))printf("Optimal BST weighted cost: %lld\\n",result);}
  else if(choice==5){int n,m,src,e[300];long long dist[30];if(!read_int("Vertices (1-30): ",&n)||n<1||n>30||!read_int("Edges (0-100): ",&m)||m<0||m>100||!read_int("Source (zero-based): ",&src))continue;for(int i=0;i<m;i++)for(int j=0;j<3;j++)if(!read_int("Edge from/to/weight: ",&e[3*i+j]))return;int r=dp_bellman(e,m,n,src,dist);if(r==-1)puts("Reachable negative-weight cycle detected.");else if(r){for(int i=0;i<n;i++)if(dist[i]==LLONG_MAX)printf("%d: unreachable\\n",i);else printf("%d: %lld\\n",i,dist[i]);}else puts("Invalid graph input.");}
  else if(choice==6){int n;if(!read_int("Vertices (1-20): ",&n)||n<1||n>20)continue;long long a[400];puts("Enter matrix row-wise; use 999999999 for no edge.");for(int i=0;i<n*n;i++){int x;if(!read_int("Entry: ",&x))return;a[i]=x==999999999?LLONG_MAX:x;}for(int i=0;i<n;i++)a[i*n+i]=0;int r=dp_floyd(a,n);if(r<0)puts("Negative cycle detected.");else if(r){for(int i=0;i<n;i++){for(int j=0;j<n;j++)if(a[i*n+j]==LLONG_MAX)printf("INF ");else printf("%lld ",a[i*n+j]);putchar('\\n');}}}
  else if(choice==7){int n,g[256];if(!read_int("Vertices (2-16): ",&n)||n<2||n>16)continue;puts("Enter matrix (0 means no edge):");for(int i=0;i<n*n;i++)if(!read_int("Weight: ",&g[i]))return;if(dp_tsp(g,n,&result))printf("Minimum tour cost: %lld\\n",result);else puts("No tour or calculation unavailable.");}
  else puts("Unknown option.");
 }
}
\n
static void backtracking_menu(void) {
 int choice;
 for (;;) {
  puts("\n========== PHASE 6: BACKTRACKING AND BRANCH-AND-BOUND ==========");
  puts("1. N-Queens"); puts("2. Subset Sum"); puts("3. 0/1 Knapsack Backtracking");
  puts("4. Knapsack Branch-and-Bound"); puts("0. Return");
  if (!read_int("Choose: ", &choice)) continue;
  if (choice == 0) return;
  if (choice == 1) { int n; if (!read_int("Board size (1-14): ", &n)) continue; long long x=bt_nqueens_count(n); if(x<0) puts("Invalid size or allocation failure."); else printf("Number of solutions: %lld\n",x); }
  else if (choice == 2) { int n,target,a[40]; if(!read_int("Number of values (1-40): ",&n)||n<1||n>40||!read_int("Target sum: ",&target)) continue; for(int i=0;i<n;i++) if(!read_int("Value: ",&a[i])) return; int r=bt_subset_sum(a,n,target); puts(r?"A subset with the target sum exists.":"No subset found (or invalid input)."); }
  else if (choice == 3 || choice == 4) { int n,cap,w[40],v[40]; long long best; if(!read_int("Items (1-20): ",&n)||n<1||n>20||!read_int("Capacity: ",&cap)||cap<0)continue; for(int i=0;i<n;i++){if(!read_int("Weight: ",&w[i])||!read_int("Value: ",&v[i]))return;} if(choice==3){if(bt_knapsack(w,v,n,cap,&best))printf("Maximum value: %lld\n",best);else puts("Invalid input.");} else {int strategy;puts("0. LIFO (depth-first)  1. FIFO (breadth-first)  2. Least-cost/best-bound");if(!read_int("Strategy: ",&strategy))continue;if(bt_knapsack_bnb(w,v,n,cap,strategy,&best))printf("Maximum value: %lld\n",best);else puts("Invalid input or unsupported size.");} }
  else puts("Unknown option.");
 }
}
\n
int main(void) {
    Library library;
    int choice;
    library_init(&library);
    if (!library_load_csv(&library, DATA_FILE))
        puts("Note: starting with an empty library (CSV could not be loaded).");

    for (;;) {
        puts("\n========== DIGITAL LIBRARY: PHASES 1, 2, 3, 4 AND 5 ==========");
        puts("1. Add a book");
        puts("2. List all books");
        puts("3. Search books by title (contains text)");
        puts("4. Update a book");
        puts("5. Delete a book");
        puts("6. Save library");
        puts("7. Phase 2: Searching and Sorting Algorithms");
        puts("8. Phase 3: Divide-and-Conquer Algorithms");
        puts("9. Phase 4: Greedy Algorithms");\n        puts("10. Phase 5: Dynamic Programming");
        puts("11. Phase 6: Backtracking and Branch-and-Bound");
        puts("0. Save and exit");
        if (!read_int("Choose an option: ", &choice)) {
            puts("Please enter a valid number."); continue;
        }
        if (choice == 0) {
            if (!library_save_csv(&library, DATA_FILE)) puts("Warning: could not save data.");
            else puts("Data saved. Goodbye!");
            break;
        }
        switch (choice) {
            case 1: add_book(&library); break;
            case 2: library_list(&library); break;
            case 3: {
                char query[TITLE_LEN];
                read_line("Enter title text to search: ", query, sizeof query);
                library_search_title(&library, query);
                break;
            }
            case 4: edit_book(&library); break;
            case 5: delete_book(&library); break;
            case 6: puts(library_save_csv(&library, DATA_FILE) ? "Library saved." : "Save failed."); break;
            case 7: search_sort_menu(&library); break;
            case 8: divide_conquer_menu(); break;
            case 9: greedy_menu(); break;\n            case 10: dynamic_programming_menu(); break;
            case 11: backtracking_menu(); break;
            default: puts("Unknown option. Try again.");
        }
    }
    library_free(&library);
    return 0;
}
