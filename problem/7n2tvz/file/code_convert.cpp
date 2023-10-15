bool flipped; int rotated;
void convert(int &x){
    if(flipped)x=rotated+2-x;
    else x-=rotated;
    x=(x+n+n-1)%n+1;
}