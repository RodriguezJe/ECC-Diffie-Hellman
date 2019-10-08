/*
 * ECC version of Diffie-Hellman key exchange
 * 
 */


#include <stdio.h>

//declare methods to multipy on elliptic curve 
int calculate_m(int x1, int x2, int y1, int y2);
int modInverse(int a, int b);
void ellipticPro(int X, int x1, int y1, int x2, int y2);

int main() {
	
	//verify P=(2,7) is on E 
    printf("Given y^2=x^3+11x+19(mod 167) and P=(2,7)");
    printf("\nWe can verify P is on E by plugging in the values for x and y");
    printf("\n7^2= 2^3+11(2)+19(mod 167)\n49=8+22+19 (mod 167)\n49=49");
    
    //secret values choosen by Alice and Bob
    int A = 12;
    int B = 31;


	//calculate A(2,7) by calling ellipticPro method and passing it values to multiply
    printf("\n\nUsing A=%d Alice computes A(2,7)= ", A);
    ellipticPro(A, 2, 7, 2, 7);
    printf(" and sends this to Bob");

	//calculate B(2,7) by calling ellipticPro method and passing it values to multiply
    printf("\nUsing B=%d Bob computes B(2,7)= ", B);
    ellipticPro(B, 2, 7, 2, 7);
    printf(" and sends this to Alice");

    //calculate A(103,153) by calling ellipticPro method and passing it values to multiply
    printf("\nUsing A=%d Alice computes A(103,153)= ", A);
    ellipticPro(A, 103, 153, 103, 153);
    printf(" this is the shared secret");

    //calculate B(153,36) by calling ellipticPro method and passing it values to add
    printf("\nUsing B=%d Bob computes B(153,36)= ", B);
    ellipticPro(B, 153, 36, 153, 36);
    printf(" this is the shared secret");

    return 0;
}
//method calculates m used in elliptic curve addition 
int calculate_m(int x1, int x2, int y1, int y2) {

    int m;
	//if P1=P2 use this algortihm to calculate m
    if (x1 == x2 && y1 == y2) {
        int x = modInverse((2 * y1), 167);
        m = ((((3 * (x1 * x1)) + 11) * x) % 167 + 167) % 167;


    } else {
		//if P1 != P2 use this algorithm to calculate m
        int x = modInverse((x2 - x1), 167);
        m = ((((y2 - y1) * x) % 167 + 167) % 167);

    }

    return m;

}

//method returns mod inverse 
int modInverse(int a, int mod) {

	// in a mod n find the number that we multiply by a to get 1 mod n
    a=(a%mod+mod)%mod;
	for (int x=1; x<mod; x++){
		if((((a*x)%mod+mod)%mod)==1){
			return x;
		}
		
	}
	return 1;
}


//method perform elliptic curve multiplication 
void ellipticPro(int X, int x1, int y1, int x2, int y2) {
	
	//create variable to hold m and new x and y 
	int m;
    int x3;
    int y3;
    
	//call calculate_m() method and pass it initial x and y
    m = calculate_m(x1, x2, y1, y2);

    // adds initial p+p 
    x3 = ((((m * m) - x1 - x2) % 167) + 167) % 167;

    y3 = (((m * (x1 - x3) - y1) % 167) + 167) % 167;

	//for loop runs X-2 times based on secret values choosen by Alice and Bob
    for (int i = 0; i < X - 2; i++) {

		//calculate new m since x3 and y3 are being updated 
        m = calculate_m(x2, x3, y2, y3);

        x3 = ((((m * m) - x2 - x3) % 167) + 167) % 167;

        y3 = (((m * (x2 - x3) - y2) % 167) + 167) % 167;
    
    }

	//print final result to screen 
    printf("(%d,%d)", x3, y3);


}
