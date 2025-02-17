long rsum(long* start, long count){
    if(count <= 0){
        return 0;
    }
    return *start + rsum(start+1, count-1);
}

// int main(){
//     long a[5] = {0,1,2,3,4};
//     rsum(a,5);
//     return 0;
// }