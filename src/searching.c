#include "algorithms.h"
#include <ctype.h>

int compare_title_text(const char *a,const char *b){
    while(*a&&*b){
        int x=tolower((unsigned char)*a),y=tolower((unsigned char)*b);
        if(x!=y)return x<y?-1:1;
        a++;b++;
    }
    return (*a!=0)-(*b!=0);
}
int linear_search_title(const Book *books,size_t n,const char *title){
    if(!books||!title)return -1;
    for(size_t i=0;i<n;i++)if(!compare_title_text(books[i].title,title))return (int)i;
    return -1;
}
int binary_search_title(const Book *books,size_t n,const char *title){
    if(!books||!title)return -1;
    size_t low=0,high=n;
    while(low<high){
        size_t mid=low+(high-low)/2;
        int c=compare_title_text(books[mid].title,title);
        if(!c)return (int)mid;
        if(c<0)low=mid+1;else high=mid;
    }
    return -1;
}
int books_sorted_by_title(const Book *books,size_t n){
    if(!books)return n==0;
    for(size_t i=1;i<n;i++)if(compare_title_text(books[i-1].title,books[i].title)>0)return 0;
    return 1;
}
