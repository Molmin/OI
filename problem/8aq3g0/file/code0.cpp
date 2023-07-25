namespace System{
    Frac calcTime(int x,int y){
        if(x>y)swap(x,y);
        if((a[x].v>0&&a[y].v>0)||(a[x].v<0&&a[y].v<0)){
            if(a[x].v>a[y].v)return makeFrac(a[y].p-a[x].p,a[x].v-a[y].v);
            else return makeFrac(l+a[x].p-a[y].p,a[y].v-a[x].v);
        }
        else{
            if(a[x].v>0)return makeFrac(a[y].p-a[x].p,a[x].v-a[y].v);
            else return makeFrac(l+a[x].p-a[y].p,a[y].v-a[x].v);
        }
    }
}