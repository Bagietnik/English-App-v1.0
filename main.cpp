#include <iostream>
#include <DB.h>

int main()
{
    DB database("192.168.1.21", "piotrek", "pswrd");
    database.showWords();

    
    return 0;
}
