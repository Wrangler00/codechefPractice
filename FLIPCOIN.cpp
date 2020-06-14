#include<bits/stdc++.h>
using namespace std;

#define LL int
#define left(n) 2*n
#define right(n) 2*n+1

const LL LIM = 1e5+100;

LL sgtree[4*LIM] = {0};
LL lazy[4*LIM] = {0};

void updateTree(LL l,LL r,LL start,LL end,LL node){
    if (lazy[node]){
        sgtree[node] = (end-start+1) - sgtree[node];
  
        if (start != end){ 
            lazy[left(node)] ^= 1; 
            lazy[right(node)] ^= 1;
        }
  
        lazy[node] = 0;
    }
    
    if(start > end || r<start || l>end){
        return;
    }
    
    if (start>=l && end<=r) {
        sgtree[node] = (end-start+1) - sgtree[node];
        if(start!=end){
            lazy[left(node)] ^= 1; 
            lazy[right(node)] ^= 1;
        }
        return; 
    }
    
    LL mid = (start+end)>>1;
    updateTree(l,r,start,mid,left(node));
    updateTree(l,r,mid+1,end,right(node));
    
    sgtree[node] = sgtree[left(node)] + sgtree[right(node)];
    return;
}

LL getFlips(LL l,LL r,LL start,LL end,LL node){
    if (lazy[node]) { 
        sgtree[node] = (end-start+1) - sgtree[node];
  
        if (start != end) 
        { 
            lazy[left(node)] ^= 1; 
            lazy[right(node)] ^= 1; 
        } 
  
        lazy[node] = 0; 
    }
    
    if(start > end || r<start || l>end){
        return 0;
    }
    
    if (start>=l && end<=r){
        return sgtree[node]; 
    }
    
    LL mid = (start+end)>>1;
    return getFlips(l,r,start,mid,left(node))+getFlips(l,r,mid+1,end,right(node));
}

int main() {
	LL n,q,i;
// 	cin>>n>>q;
	scanf("%d %d",&n,&q);
	
	for(i=0;i<q;i++){
	    LL a,l,r;
	   // cin>>a>>l>>r;
	    
	    scanf("%d %d %d",&a,&l,&r);
	    
	    switch(a){
	        case 0:
	            updateTree(l,r,0,n-1,1);
	            break;
	        case 1:
	            cout<<getFlips(l,r,0,n-1,1)<<endl;
	            break;
	    }
	}
	return 0;
}
