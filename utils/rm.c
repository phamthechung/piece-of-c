#include <piece/string.h>
#include <piece/iofile.h>

int main(int argc,char **argv){
  int c=argc,r=1;
  while(--c){
    if(ifdir(argv[r]))
       removdir(argv[r]);
    else
      unlink(argv[r]);
    //puts(argv[r]);
    r++;
  }
}
