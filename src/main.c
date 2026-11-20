#include "book.h"
#include "library.h"
#include "algorithms.h"
#include "divide_conquer.h"
#include "greedy.h"
#include "dp.h"
#include "backtracking.h"
#include "flow_matching.h"
#include "string_number_theory.h"
#include "analysis.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DATA_FILE "data/books.csv"

static void input_book(Book *b){
    read_line("Title: ",b->title,TITLE_LEN);
    read_line("Author: ",b->author,AUTHOR_LEN);
    read_line("Category: ",b->category,CATEGORY_LEN);
    read_line("Keywords: ",b->keywords,KEYWORDS_LEN);
    if(!read_int("Citations: ",&b->citations))b->citations=0;
    if(!read_int("Popularity: ",&b->popularity))b->popularity=0;
}
static void add_book(Library *lib){
    Book b={0};b.id=library_next_id(lib);input_book(&b);
    if(!b.title[0]||!b.author[0]){puts("Title and author are required.");return;}
    puts(library_add(lib,&b)?"Book added.":"Could not add book.");
}
static void edit_book(Library *lib){
    int id;if(!read_int("Book ID: ",&id)){puts("Invalid ID.");return;}
    if(library_find_id(lib,id)<0){puts("Book not found.");return;}
    Book b={0};input_book(&b);
    if(!b.title[0]||!b.author[0]){puts("Title and author are required.");return;}
    puts(library_update(lib,id,&b)?"Book updated.":"Update failed.");
}
static void delete_book(Library *lib){
    int id;if(!read_int("Book ID: ",&id)){puts("Invalid ID.");return;}
    puts(library_remove(lib,id)?"Book deleted.":"Book not found.");
}
static void search_menu(Library *lib){
    int choice;char title[TITLE_LEN];
    puts("\n1. Linear Search  2. Binary Search  3. Merge Sort  0. Back");
    if(!read_int("Choice: ",&choice))return;
    if(choice==3){puts(merge_sort_books(lib->items,lib->count)?"Sorted with Merge Sort.":"Sort failed.");return;}
    if(choice!=1&&choice!=2)return;
    read_line("Exact title: ",title,sizeof title);
    if(choice==2&&!books_sorted_by_title(lib->items,lib->count)){
        puts("Sorting titles first for Binary Search.");
        if(!merge_sort_books(lib->items,lib->count))return;
    }
    int i=choice==1?linear_search_title(lib->items,lib->count,title):binary_search_title(lib->items,lib->count,title);
    if(i<0)puts("Book not found.");else print_book(&lib->items[i]);
}
static void max_subarray_menu(void){
    int n;if(!read_int("Number of values (1-100): ",&n)||n<1||n>100)return;
    long long a[100];for(int i=0;i<n;i++){int x;if(!read_int("Value: ",&x))return;a[i]=x;}
    MaxSubarrayResult r;
    if(maximum_subarray_divide_conquer(a,(size_t)n,&r))
        printf("Maximum sum: %lld (indices %zu to %zu)\n",r.sum,r.start,r.end);
}
static void greedy_menu(void){
    int choice;if(!read_int("1. Activity Selection  2. Dijkstra  0. Back: ",&choice))return;
    if(choice==1){
        int n;if(!read_int("Activities (1-50): ",&n)||n<1||n>50)return;
        Activity a[50];size_t selected[50];
        for(int i=0;i<n;i++)if(!read_int("Start time: ",&a[i].start)||!read_int("Finish time: ",&a[i].finish))return;
        size_t used=greedy_activity_selection(a,(size_t)n,selected);
        printf("Selected %zu activities:",used);
        for(size_t i=0;i<used;i++)printf(" %zu",selected[i]+1);
        putchar('\n');
    }else if(choice==2){
        int n,source;if(!read_int("Vertices (1-20): ",&n)||n<1||n>20)return;
        int g[400],parent[20];long long d[20];
        puts("Enter adjacency matrix (0 = no edge; non-negative weights):");
        for(int i=0;i<n*n;i++)if(!read_int("Weight: ",&g[i]))return;
        if(!read_int("Source vertex (0-based): ",&source)||source<0||source>=n)return;
        if(!greedy_dijkstra(g,(size_t)n,(size_t)source,d,parent)){puts("Invalid graph.");return;}
        for(int i=0;i<n;i++)if(d[i]==LLONG_MAX)printf("%d: unreachable\n",i);else printf("%d: %lld\n",i,d[i]);
    }
}
static void knapsack_menu(void){
    int n,cap;if(!read_int("Items (1-50): ",&n)||n<1||n>50||!read_int("Capacity: ",&cap)||cap<0||cap>100000)return;
    int w[50],v[50];for(int i=0;i<n;i++)if(!read_int("Weight: ",&w[i])||!read_int("Value: ",&v[i]))return;
    long long best;if(dp_knapsack(w,v,(size_t)n,cap,&best))printf("Maximum value: %lld\n",best);else puts("Invalid items.");
}
static void backtracking_menu(void){
    int choice;if(!read_int("1. N-Queens  2. Subset Sum  0. Back: ",&choice))return;
    if(choice==1){int n;if(!read_int("Board size (1-14): ",&n))return;long long count=bt_nqueens_count(n);if(count<0)puts("Invalid board size.");else printf("Solutions: %lld\n",count);}
    else if(choice==2){
        int n,target;if(!read_int("Number of values (1-30): ",&n)||n<1||n>30||!read_int("Target sum: ",&target))return;
        int a[30];for(int i=0;i<n;i++)if(!read_int("Value: ",&a[i]))return;
        puts(bt_subset_sum(a,(size_t)n,target)?"A subset exists.":"No subset found.");
    }
}
static void flow_menu(void){
    int n,s,t;if(!read_int("Vertices (2-20): ",&n)||n<2||n>20)return;
    int cap[400];long long flow;
    puts("Enter capacity matrix (0 = no edge):");
    for(int i=0;i<n*n;i++)if(!read_int("Capacity: ",&cap[i]))return;
    if(!read_int("Source (0-based): ",&s)||!read_int("Sink (0-based): ",&t))return;
    if(flow_ford_fulkerson(cap,(size_t)n,(size_t)s,(size_t)t,&flow))printf("Maximum flow: %lld\n",flow);else puts("Invalid network.");
}
static void string_menu(void){
    int choice;if(!read_int("1. KMP Search  2. Chinese Remainder Theorem  0. Back: ",&choice))return;
    if(choice==1){
        char text[500],pattern[100];read_line("Text: ",text,sizeof text);read_line("Pattern: ",pattern,sizeof pattern);
        size_t at=string_match_kmp(text,pattern);
        if(at==SIZE_MAX)puts("Pattern not found.");else printf("Pattern found at index %zu.\n",at);
    }else if(choice==2){
        int n;if(!read_int("Number of equations (1-10): ",&n)||n<1||n>10)return;
        long long r[10],m[10];
        for(int i=0;i<n;i++){
            int rem,mod;
            if(!read_int("Remainder: ",&rem)||!read_int("Positive modulus: ",&mod))return;
            r[i]=rem;m[i]=mod;
        }
        long long answer;
        if(crt_solve(r,m,(size_t)n,&answer))printf("Smallest non-negative solution: %lld\n",answer);
        else puts("Moduli must be pairwise coprime and the result must fit.");
    }
}
static void complexity_menu(void){
    int n,k;if(!read_int("Graph vertices: ",&n)||!read_int("Independent-set size k: ",&k)||n<0||k<0)return;
    size_t cover;
    if(analysis_reduce_independent_set_to_vertex_cover((size_t)n,(size_t)k,&cover))
        printf("Independent Set (G,%d) becomes Vertex Cover (G,%zu).\n",k,cover);
    else puts("Require 0 <= k <= number of vertices.");
    puts("P: solvable in polynomial time; NP: solutions verifiable in polynomial time.");
    puts("NP-complete: in NP and NP-hard. NP-hard: at least as hard as every problem in NP.");
}
int main(void){
    Library lib;library_init(&lib);
    if(!library_load_csv(&lib,DATA_FILE))puts("Starting with an empty library.");
    int choice;
    for(;;){
        puts("\n===== DIGITAL LIBRARY =====");
        puts("1 Add  2 List  3 Search text  4 Update  5 Delete  6 Save");
        puts("7 Search/Sort  8 Maximum Subarray  9 Greedy  10 0/1 Knapsack");
        puts("11 Backtracking  12 Maximum Flow  13 KMP/CRT  14 Complexity");
        puts("0 Save and Exit");
        if(!read_int("Choice: ",&choice)){puts("Enter a number.");continue;}
        switch(choice){
            case 0:library_save_csv(&lib,DATA_FILE);library_free(&lib);puts("Goodbye.");return 0;
            case 1:add_book(&lib);break;
            case 2:library_list(&lib);break;
            case 3:{char q[TITLE_LEN];read_line("Title text: ",q,sizeof q);library_search_title(&lib,q);break;}
            case 4:edit_book(&lib);break;
            case 5:delete_book(&lib);break;
            case 6:puts(library_save_csv(&lib,DATA_FILE)?"Saved.":"Save failed.");break;
            case 7:search_menu(&lib);break;
            case 8:max_subarray_menu();break;
            case 9:greedy_menu();break;
            case 10:knapsack_menu();break;
            case 11:backtracking_menu();break;
            case 12:flow_menu();break;
            case 13:string_menu();break;
            case 14:complexity_menu();break;
            default:puts("Invalid option.");
        }
    }
}
