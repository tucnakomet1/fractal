#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    // vzorec:
    // r^2 = (x-m)^2 + (y-m)^2
    // ------------------------
    
    // r      = polomer
    // d      = prumer  = 2r
    // [r, r] = stred   = S[m, n]
    
    int r = 50;
    int d = 2*r;

    for (int y = 0; y <= d; y++) {
        for (int x = 0; x <= d; x++) {
            
            double a = x-r;                         // (x-m)
            double b = y-r;                         // (y-m)
            
            double pow_bod = pow(a, 2) + pow(b, 2); // r^2 = a^2 + b^2
            double bod = sqrt(pow_bod);             // r = sqrt(r^2)
            
            if ((bod > r - 0.5) &&  (bod < r + 0.5)) {
                printf("##");
            } else {
                printf("  ");
            }
        }
        printf("\r\n");
    }

    return 0;
}


// output
/* 
              ##############              
          ####              ####          
        ##                      ##        
      ##                          ##      
    ##                              ##    
  ##                                  ##  
  ##                                  ##  
##                                      ##
##                                      ##
##                                      ##
##                                      ##
##                                      ##
##                                      ##
##                                      ##
  ##                                  ##  
  ##                                  ##  
    ##                              ##    
      ##                          ##      
        ##                      ##        
          ####              ####          
              ##############              
*/
