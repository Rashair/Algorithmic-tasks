#include <iostream>
#include <cstring>
#include <algorithm>
#include <array>
#include <map>

using namespace std;
#include "balls.h"

const int bsize=8;
const int bsize_square=bsize*bsize;
array <char,bsize_square> board;
array < array <int,2>, bsize > moves;
array < array <int,2>, bsize > mov;
map <string,int> states;
int mov_num=bsize;
int dots;

int main(){
    ios::sync_with_stdio(false);
    for(int i=0; i<bsize_square; ++i){
        cin>>board[i];
    }
    dots=skip(0);
    possib(dots);
    cout<<mov_num+1<<"\n";
    int i=0;
    while(i<=mov_num){
        cout<<(moves[i][0]/bsize)+1<<" "<<(moves[i][0]%bsize)+1<<" "<<(moves[i][1]/bsize)+1<<" "<<(moves[i][1]%bsize)+1<<"\n";
        ++i;
    }
}

int skip(int k){
    while(k+bsize<bsize_square && board[k]=='.' && board[k+bsize]=='.')
        ++k;
    return k;
}

void possib(int k, int level){
    //optimization starts
    string str(begin(board),end(board));
    if(states[str] && states[str]<=level) return;
    else states[str]=level;
    //optimization ends
    //3 lines of code which do it 15x faster ^^^
    k=skip(k);
    while(k+1<bsize_square){
        if(k%bsize+1<bsize && board[k]!=board[k+1]){
            bool grav=false;
            array <char, bsize_square> temp;
            swap(board[k],board[k+1]);
            if(sequence(k,0)){
                grav=true;
                temp=board;
                swap(temp[k],temp[k+1]);
                activate_sequence(k,0);
                while(sequence()) activate_sequence();
                mov[level][0]=k;
                mov[level][1]=k+1;
                if(clean()){
                    moves=mov;
                    mov_num=level;
                    return;
                }
                else if(level+1<mov_num)
                    possib(dots,level+1);
            }
            if(grav)
                board=temp;
            else
                swap(board[k],board[k+1]);
        }
        if(k+bsize<bsize_square && board[k]!=board[k+bsize]){
            bool grav=false;
            array <char, bsize_square>temp;
            swap(board[k],board[k+bsize]);
            if(sequence(k,1)){
                grav=true;
                temp=board;
                swap(temp[k],temp[k+bsize]);
                activate_sequence(k,1);
                while(sequence()) activate_sequence();
                mov[level][0]=k;
                mov[level][1]=k+bsize;
                if(clean()){
                    moves=mov;
                    mov_num=level;
                    return;
                }
                else if(level+1<mov_num){
                    possib(dots,level+1);
                }
            }
            if(grav)
                board=temp;
            else
                swap(board[k],board[k+bsize]);
        }
        ++k;
    }
}

bool sequence(int k, bool swaped){
    if(swaped){
        if(board[k]!='.'){
            int p=k%bsize;
            if(p>1 && board[k-2]==board[k] && board[k-1]==board[k]){
                return true;
            }
            if(p<6 && board[k+1]==board[k] && board[k+2]==board[k]){
                return true;
            }
            if(p && p<7 && board[k-1]==board[k] && board[k+1]==board[k]){
                return true;
            }
            if(k/bsize>1 && board[k-bsize]==board[k] && board[k-2*bsize]==board[k]){
                return true;
            }
        }
        k+=bsize;
        if(board[k]!='.'){
            int p=k%bsize;
            if(p>1 && board[k-2]==board[k] && board[k-1]==board[k]){
                return true;
            }
            if(p<6 && board[k+1]==board[k] && board[k+2]==board[k]){
                return true;
            }
            if(p && p<7 && board[k-1]==board[k] && board[k+1]==board[k]){
                return true;
            }
            if(k/bsize<6 && board[k+bsize]==board[k] && board[k+2*bsize]==board[k]){
                return true;
            }
        }
    }
    else{
        if(board[k]!='.'){
            int p=k/bsize;
            if(p>1 && board[k-bsize]==board[k] && board[k-2*bsize]==board[k]){
                return true;
            }
            if(p<6 && board[k+bsize]==board[k] && board[k+2*bsize]==board[k]){
               return true;
            }
            if(p && p<7 && board[k-bsize]==board[k] && board[k+bsize]==board[k]){
                return true;
            }
            if(k%bsize>1 && board[k-2]==board[k] && board[k-1]==board[k]){
                return true;
            }
        }
        ++k;
        if(board[k]!='.'){
            int p=k/bsize;
            if(p>1 && board[k-bsize]==board[k] && board[k-2*bsize]==board[k]){
                return true;
            }
            if(p<6 && board[k+bsize]==board[k] && board[k+2*bsize]==board[k]){
                return true;
            }
            if(p && p<7 && board[k-bsize]==board[k] && board[k+bsize]==board[k]){
                return true;
            }
            if(k%bsize<6 && board[k+2]==board[k] && board[k+1]==board[k]){
                return true;
            }
        }
    }
    return false;
}


bool sequence(){
    int i=dots;
    while(board[i]=='.') ++i;
    for(; i<bsize_square; ++i){
        if(board[i]=='.')
            continue;
        if(i+2*bsize<bsize_square && board[i]==board[i+bsize] && board[i]==board[i+2*bsize])
            return true;
        if(i%bsize+2<bsize && board[i]==board[i+1] && board[i]==board[i+2])
            return true;
    }
    return false;
}

void activate_sequence(int k, bool way_of_swap){
    if(way_of_swap){ // down or right
        int mod=k%bsize;
        if(board[k]!='.'){
            if(k/bsize>1 && board[k]==board[k-bsize] && board[k]==board[k-2*bsize]){
                if(mod>1 && board[k]==board[k-1] && board[k]==board[k-2])
                    drop(k,3);
                else if(mod<6 && board[k]==board[k+1] && board[k]==board[k+2])
                    drop(k,3);
                else if(mod && mod<7 && board[k]==board[k-1] && board[k]==board[k+1])
                    drop(k,3);
                else
                    drop(k-2*bsize,2);
            }
            else{
                if(mod>1 && board[k]==board[k-1] && board[k]==board[k-2])
                    drop(k-2,1);
                else if(mod && mod<7 && board[k]==board[k-1] && board[k]==board[k+1])
                    drop(k-1,1);
                else if(mod<6 && board[k]==board[k+1] && board[k]==board[k+2])
                    drop(k,1);
            }
        }
        k+=bsize;
        if(board[k]!='.'){
            if(k/bsize<6 && board[k]==board[k+bsize] && board[k]==board[k+2*bsize]){
                if(mod>1 && board[k]==board[k-1] && board[k]==board[k-2])
                    drop(k,3);
                else if(mod<6 && board[k]==board[k+1] && board[k]==board[k+2])
                    drop(k,3);
                else if(mod && mod<7 && board[k]==board[k-1] && board[k]==board[k+1])
                    drop(k,3);
                else
                    drop(k,2);
            }
            else{
                if(mod>1 && board[k]==board[k-1] && board[k]==board[k-2])
                    drop(k-2,1);
                else if(mod && mod<7 && board[k]==board[k-1] && board[k]==board[k+1])
                    drop(k-1,1);
                else if(mod<6 && board[k]==board[k+1] && board[k]==board[k+2])
                    drop(k,1);
            }
        }
    }
    else{
        int mod=k/bsize;
        if(board[k]!='.'){
            if(k%bsize>1 && board[k]==board[k-1] && board[k]==board[k-2]){
                if(mod>1 && board[k]==board[k-bsize] && board[k]==board[k-2*bsize])
                    drop(k,3);
                else if(mod<6 && board[k]==board[k+bsize] && board[k]==board[k+2*bsize])
                    drop(k,3);
                else if(mod && mod<7 && board[k]==board[k-bsize] && board[k]==board[k+bsize])
                    drop(k,3);
                else
                    drop(k-2,1);
            }
            else{
                if(mod>1 && board[k]==board[k-bsize] && board[k]==board[k-2*bsize])
                    drop(k-2*bsize,2);
                else if(mod && mod<7 && board[k]==board[k-bsize] && board[k]==board[k+bsize])
                    drop(k-bsize,2);
                else if(mod<6 && board[k]==board[k+bsize] && board[k]==board[k+2*bsize])
                    drop(k,2);
            }
        }
        ++k;
        if(board[k]!='.'){
            if(k%bsize<6 && board[k]==board[k+1] && board[k]==board[k+2]){
                if(mod>1 && board[k]==board[k-bsize] && board[k]==board[k-2*bsize])
                    drop(k,3);
                else if(mod<6 && board[k]==board[k+bsize] && board[k]==board[k+2*bsize])
                    drop(k,3);
                else if(mod && mod<7 && board[k]==board[k-bsize] && board[k]==board[k+bsize])
                    drop(k,3);
                else
                    drop(k,1);
            }
            else{
                if(mod>1 && board[k]==board[k-bsize] && board[k]==board[k-2*bsize])
                    drop(k-2*bsize,2);
                else if(mod && mod<7 && board[k]==board[k-bsize] && board[k]==board[k+bsize])
                    drop(k-bsize,2);
                else if(mod<6 && board[k]==board[k+bsize] && board[k]==board[k+2*bsize])
                    drop(k,2);
            }
        }
    }
    go_down();
}

void activate_sequence(){
    int n1=1,n2=1, i=dots;
    while(i<bsize_square){
        while(i+1<bsize_square && board[i]=='.'){
            ++i;
        }
        n1=1;
        int k=i+bsize;
        while(k<bsize_square && board[i]==board[k]){
            k+=bsize;
            ++n1;
        }
        if(n1>=3){
            int s;
            bool dseq=false;
            int mod=i%bsize;
            for(s=i; n1>0; s+=bsize){
                if(mod+2<bsize && board[s]==board[s+1] && board[s]==board[s+2]){
                    dseq=true;
                    break;
                }
                if(mod>1 && board[s]==board[s-1] && board[s]==board[s-2]){
                    dseq=true;
                    break;
                }
                if(mod && mod<7 && board[s]==board[s-1] && board[s]==board[s+1]){
                    dseq=true;
                    break;
                }
                --n1;
            }
            if(dseq)
                complex_drop(s,1);
            else
                drop(i,2);
        }
        else{
            k=i;n2=1;
            while(k%bsize+1<bsize && board[i]==board[k+1]){
                ++k;
                ++n2;
            }
            if(n2>=3){
                int s;
                bool dseq=false;
                for(s=i+1; n2>1; ++s){
                    if(s+2*bsize<bsize_square && board[s]==board[s+bsize] && board[s]==board[s+2*bsize]){
                        dseq=true;
                        break;
                    }
                    --n2;
                }
                if(dseq)
                    complex_drop(s,2);
                else
                    drop(i,1);
            }
        }
        ++i;
    }
    go_down();
}

void drop(int j, int k){
    int m;
    if(k==3){
        m=j+bsize;
        while(m<bsize_square && board[j]==board[m]){
            board[m]='.';
            m+=bsize;
        }
        m=j-bsize;
        while(m>0 && board[j]==board[m]){
            board[m]='.';
            m-=bsize;
        }
        m=j;
        while(m%bsize+1<bsize && board[j]==board[m+1]){
            board[m+1]='.';
            ++m;
        }
        m=j;
        while(m%bsize>0 && board[j]==board[m-1]){
            board[m-1]='.';
            --m;
        }
    }
    else if(k==2){
        m=j+bsize;
        while(m<bsize_square && board[j]==board[m]){
            board[m]='.';
            m+=bsize;
        }
    }
    else{
        m=j;
        while(m%bsize+1<bsize && board[j]==board[m+1]){
            board[m+1]='.';
            ++m;
        }
    }
    board[j]='.';
}

void complex_drop(int j, int mode){
    char sign=board[j];
    int m;
    if(mode==1){
        m=j+bsize;
        while(m<bsize_square && sign==board[m]){
            int mod=m%bsize;
            if( !( (mod>1 && board[m-2]==board[m-1] && board[m-1]==sign) ||
                   (mod && mod<7 && board[m-1]==board[m+1] && board[m-1]==sign) ||
                   (mod<6 && board[m+1]==board[m+2] && board[m+1]==sign)
                 )
              ) board[m]='.';
            m+=bsize;
        }
        m=j-bsize;
        while(m>0 && board[j]==board[m]){
            board[m]='.';
            m-=bsize;
        }
        m=j;
        while(m%bsize+1<bsize && board[j]==board[m+1]){
            int mod=m/bsize;
            if( !( (mod>1 && board[m+1-bsize]==board[m+1-2*bsize] && board[m+1-bsize]==sign) ||
                   (mod && mod<7 && board[m+1-bsize]==board[m+1+bsize] && board[m+1+bsize]==sign) ||
                   (mod<6 && board[m+1+bsize]==board[m+1+2*bsize] && board[m+1]==sign)
                 )
              ) board[m+1]='.';
            ++m;
        }
        m=j;
        while(m%bsize>0 && board[j]==board[m-1]){
            int mod=m/bsize;
            if( !( (mod>1 && board[m-1-bsize]==board[m-1-2*bsize] && board[m-1-bsize]==sign) ||
                   (mod && mod<7 && board[m-1-bsize]==board[m-1+bsize] && board[m-1+bsize]==sign) ||
                   (mod<6 && board[m-1+bsize]==board[m-1+2*bsize] && board[m-1]==sign)
                 )
              ) board[m-1]='.';
            --m;
        }
    }
    else{
        m=j;
        while(m%bsize>0 && board[j]==board[m-1]){
            board[m-1]='.';
            --m;
        }
        m=j;
        while(m%bsize+1<bsize && board[j]==board[m+1]){
            if(!(m/bsize<6 && board[m+1+bsize]==board[m+1+2*bsize] && board[m+1]==sign))
                board[m+1]='.';
            ++m;
        }
        m=j+bsize;
        while(m<bsize_square && sign==board[m]){
            int mod=m%bsize;
            if( !( (mod>1 && board[m-2]==board[m-1] && board[m-1]==sign) ||
                   (mod && mod<7 && board[m-1]==board[m+1] && board[m-1]==sign) ||
                   (mod<6 && board[m+1]==board[m+2] && board[m+1]==sign)
                 )
              ) board[m]='.';
            m+=bsize;
        }
    }
    board[j]='.';
}


void go_down(){
    for(int i=bsize_square-1; i>=bsize; --i){
        if(board[i-bsize]!='.'){
            if(board[i]=='.'){
                int m=i;
                while(m<bsize_square && board[m]=='.'){
                    swap(board[m],board[m-bsize]);
                    m+=bsize;
                }
            }
        }
    }
}

bool clean(){
    for(int i=bsize_square-bsize; i<bsize_square; ++i){
        if(board[i]!='.')
            return false;
    }
    return true;
}
