#include "algorithms.h"
#include <stdlib.h>
static void merge(Book *a,Book *tmp,size_t l,size_t m,size_t r){
    size_t i=l,j=m,k=l;
    while(i<m&&j<r)tmp[k++]=compare_title_text(a[i].title,a[j].title)<=0?a[i++]:a[j++];
    while(i<m)tmp[k++]=a[i++];while(j<r)tmp[k++]=a[j++];
    for(i=l;i<r;i++)a[i]=tmp[i];
}
static void sort_range(Book *a,Book *tmp,size_t l,size_t r){
    if(r-l<2)return;size_t m=l+(r-l)/2;
    sort_range(a,tmp,l,m);sort_range(a,tmp,m,r);merge(a,tmp,l,m,r);
}
int merge_sort_books(Book *a,size_t n){
    if(!a&&n)return 0;if(n<2)return 1;
    if(n>(size_t)-1/sizeof(Book))return 0;
    Book *tmp=malloc(n*sizeof(Book));if(!tmp)return 0;
    sort_range(a,tmp,0,n);free(tmp);return 1;
}
